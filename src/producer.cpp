#include "producer.h"
#include <iostream>

using namespace std;

Producer::Producer(int id){
	this->id = id;
	active = 0;
	if(id==0){
			buff.n = 0;
			active = 1;

		}
}


void Producer::produce(){
	// enter critical section
	enterCritical();
// while(buff.n>=3){
// 	//cout << "Płaczący producent numer " << this->id <<" chciałby ale nie może :( \n" << endl;
// 	}

	buff.n++;

	// cout << "Płaczący producent numer " << this->id <<" strumieniuje: " << buff.n << "\n" << endl;
leaveCritical();


	// leave critical section

}