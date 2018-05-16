#include "consumer.h"
#include "producer.h"
#include <iostream>

Conditional Consumer::cons;

using namespace std;

Consumer::Consumer(){
	//cout << ">" << cons.id  << "<" << criticalSection.id << endl;
}

void Consumer::consume(){
	enterCritical();
	while(buff.n<=0){
		wait(&cons);
	}

	buff.n--;
	log("!!! Consuming !!!");
	leaveCritical();

}