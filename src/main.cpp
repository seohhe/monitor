#include "main.h"

using namespace std;

int main(int argc, char **argv) {
  MPI::Init(argc,argv);
  int size = MPI::COMM_WORLD.Get_size();
  int rank = MPI::COMM_WORLD.Get_rank();

  if(rank%2==0){
    Producer* p = new Producer();
    for(int i=0; i<2; i++){
      p->produce();
    }
    while(p->active) { p->enterCritical(); sleep(1); p->leaveCritical(); }
  } else {
    Consumer* c = new Consumer();
    for(int i=0; i<2; i++){
      c->consume();
    }
    while(c->active) { c->enterCritical(); sleep(1); c->leaveCritical(); }
  }
  cout <<"Hello world: " << rank <<" of " << size << endl;
  MPI::Finalize();
}