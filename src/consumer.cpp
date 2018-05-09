#include "consumer.h"
#include <iostream>

using namespace std;

Consumer::Consumer(int id){
	this->id = id;
	active = 0;
}


void Consumer::consume(){
	// enter critical section
	enterCritical();
// while(buff.n==0){
// 	//cout << "Śmiejący się consumer numer " << this->id <<" chciałby coś zjeść ale nie może :( \n" << endl;
// 	}

	buff.n--;

	// cout << "Śmiejący się consumer numer " << this->id <<" zjada: " << buff.n << "\n" << endl;
leaveCritical();


	// leave critical section

}