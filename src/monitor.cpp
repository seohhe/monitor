#include "monitor.h"
#include <iostream>
#include <cstdlib>
#include <pthread.h>

Conditional Monitor::criticalSection;

using namespace std;

Monitor::Monitor(){
	size = MPI::COMM_WORLD.Get_size();
	id = MPI::COMM_WORLD.Get_rank();
	active = 0;
	if(id==0) {
		active = 1;
		for(int i = 0; i < size; i++) {
			buff.queue.x[i] = 0;
		}
	}
}

void Monitor::enterCritical(){
	if(!active) {
		wait(&criticalSection);
	}

	notify = criticalSection.id;
	log("entering");

	requests = (MPI_Request*) malloc(sizeof(MPI_Request) * size);
	responses = (struct Buff*) malloc(sizeof(struct Buff) * size);
	
	for(int i = 0; i < size; i++) {
		if(i==id) continue;
		MPI_Datatype datatype;
		MPI_Type_contiguous(sizeof(struct Buff), MPI_BYTE, &datatype);
		MPI_Type_commit(&datatype);
		MPI_Irecv(&responses[i], sizeof(struct Buff), datatype, i, MPI_ANY_TAG, MPI_COMM_WORLD, &requests[i]);
	}
}

void Monitor::sendBuff(struct Buff* buff, int type, int target){
			buff->type = type;
			MPI_Datatype datatype;
			MPI_Type_contiguous(sizeof(struct Buff), MPI_BYTE, &datatype);
			MPI_Type_commit(&datatype);
			MPI_Send( buff, 1, datatype, target, 1, MPI_COMM_WORLD);
}

void Monitor::recvBuff(struct Buff* buff){
	MPI_Status status;
  MPI_Datatype datatype;
	MPI_Type_contiguous(sizeof(struct Buff), MPI_BYTE, &datatype);
	MPI_Type_commit(&datatype);
	MPI_Recv(buff, sizeof(struct Buff), datatype, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);	
}

void Monitor::loop() {
	while(1) {
		struct Buff b;
		recvBuff(&b);
		if(b.type == -this->buff.queue.x[id]) {
			memcpy(&buff, &b, sizeof(struct Buff));
			this->buff.queue.x[id] = 0;
			break;
		}
	}
	//log("recived");
notify = criticalSection.id;
	this->active = 1;
}

void Monitor::leaveCritical(bool f){
	//log("leaving");
	for(int i = 0; i < size; i++) {
		if(i==id) continue;
		MPI_Status b;
		int t;
		MPI_Test(&requests[i], &t, &b);
		if(t) {
			if(responses[i].type >	 0) {
				// for(int j = 0; j < sizeof(responses[i].queue.x); j++) {
				// 	this->buff.queue.x[j] = responses[i].queue.x[j];
				// }
				this->buff.queue.x[i] = responses[i].type;
				//log("add to queue");
			}
		} else {
			MPI_Cancel(&requests[i]);
			MPI_Request_free(&requests[i]);
		}
	}
	// log("new queue");
   
	for(int i = id+1;; i++) {
		i = i % size;
		if(!f && i == id) break;
		if(buff.queue.x[i]==notify){
			this->active = 0;
			// log("sending");
			sendBuff(&buff, -criticalSection.id, i);
			break;
		}
	}
}

void Monitor::wait(Conditional* cond){
	//log("Waiting");
	struct Buff b;
	buff.queue.x[id] = cond->id;

	if(cond->id != criticalSection.id) {
		leaveCritical(true);
	} else
	for(int i = 0; i < size; i++) {
		if(i==id) continue;
		sendBuff(&b, cond->id, i);
	}	
	loop();
}

void Monitor::signal(Conditional* cond){
	notify = cond->id;
}

void Monitor::log(string action) {
	cout << this->id << ") " << action << " n=" << this->buff.n << " ";
	cout << "active=" << active << " ";
	cout << "type=" << buff.type << " ";
	cout << "queue=[" << buff.queue.x[0] << ","
							<< buff.queue.x[1] << ","
							<< buff.queue.x[2] << ","
							<< buff.queue.x[3] << ","
							<< buff.queue.x[4] << ","
							<< buff.queue.x[5] << "]";
	cout << endl;
}