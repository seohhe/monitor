#include "producer.h"
#include "consumer.h"
#include <iostream>

Conditional Producer::prod;

using namespace std;

Producer::Producer(){
	if(id==0){
		buff.n = 0;
	}

	//cout << "<" << prod.id  << "<" << criticalSection.id << endl;
}

void Producer::produce(){
	enterCritical();
	while(buff.n>=3){
		wait(&prod);
	}
	buff.n++;
	log("!!! Producing !!!");
	leaveCritical();
	usleep(10000);
}