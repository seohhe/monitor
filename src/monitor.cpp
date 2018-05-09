#include "monitor.h"
#include <iostream>
#include <pthread.h>

using namespace std;

Monitor::Monitor(){
	//mpi::environment env(argc, argv); 
	size=MPI::COMM_WORLD.Get_size();
	id=MPI::COMM_WORLD.Get_rank();
	active = 0;
	if(id==0) active = 1;

	pthread_t listener;
  if (pthread_create(&listener, NULL, Monitor::loop, 0)) {
     cout << "Error:unable to create thread," << rc << endl;
     exit(-1);
  }
}

void Monitor::loop() {
	// cout << "Loop" << id << endl;   
	MPI_Status status;
	// MPI_Recv( &max, sizeof(int), MPI_INT, size-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  std::string s;

  MPI_Datatype datatype;
	MPI_Type_contiguous(sizeof(struct Buff), MPI_BYTE, &datatype);
	MPI_Type_commit(&datatype);

	// MPI_Isend(&buff, 1, datatype, (id+1)%size, 0, MPI_COMM_WORLD, 0); 
	MPI_Recv( &buff, sizeof(struct Buff), datatype, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);


	// world.recv(boost::mpi::any_source, 01, s);

	// unsigned char b_data[sizeof(struct Buff)];
	// const char *temp = s.c_str();
 //  // memcpy(temp, (unsigned char *) &b_data, sizeof(struct Buff));
	// memcpy(&buff, &b_data, sizeof(struct Buff));


	// cout << id << ") dostalem: " << s[0] + s[1] + s[2] + s[3] << endl;
	// cout << id << ") odebrano: " << s << endl;
	cout << id << ") recieve | n = " << buff.n << endl; 
	fflush(stdin);  
	active = 1;
}

void Monitor::enterCritical(){
	while(!active) loop();
}

void Monitor::leaveCritical(){
	active = 0;
// cout << id << ")" << buff.n << endl; 
	// char* temp = (char*) malloc(sizeof(struct Buff) + 1);
	// memcpy(&temp, &buff, sizeof(struct Buff));
	// temp[sizeof(struct Buff)] = 0;
	// std::string buffer(temp);
buff.n = id;
	cout << id << ") send | n = " << buff.n << endl;
	fflush(stdin);   
	MPI_Datatype datatype;
	MPI_Type_contiguous(sizeof(struct Buff), MPI_BYTE, &datatype);
	MPI_Type_commit(&datatype);

	// MPI_Isend(&buff, 1, datatype, (id+1)%size, 0, MPI_COMM_WORLD, 0); 
	MPI_Send( &buff, 1, datatype, (id+1)%size, 1, MPI_COMM_WORLD);
return;
	unsigned char b_data[sizeof(struct Buff)];
  memcpy(b_data, (unsigned char *) &buff, sizeof(struct Buff));

  //save_bytes(b_data, sizeof(struct Buff));

	std::string buffer((char*)b_data);
	// cout << buffer << endl;
	cout << id << ") wyslalem: " << buffer[0] + buffer[1] + buffer[2] + buffer[3] << endl;
  cout << id << ") WYSLAONO " << buffer << endl;
  cout << id << ") n = " << buff.n << endl;      
	world.send((id+1)%size, 0, buffer);
	// MPI_Send( &max, 1, MPI_INT, id+1, 1, MPI_COMM_WORLD);
}

void Monitor::lock(){
	active = 1;
}

void Monitor::unlock(){
	active = 0;
}