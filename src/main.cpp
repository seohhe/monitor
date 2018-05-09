#include "main.h"

using namespace std;

int main(int argc, char **argv) {
  MPI::Init(argc,argv);
  int size = MPI::COMM_WORLD.Get_size();
  int rank = MPI::COMM_WORLD.Get_rank();

  if(rank%2==0){
    Producer* p = new Producer(rank);
    for(int i=0; i<10; i++){
      p->produce();
    }
  } else {
    Consumer* c = new Consumer(rank);
    for(int i=0; i<10; i++){
      c->consume();
    }
  }
  // cout <<"Hello world: " << rank <<" of " << size << endl;
  MPI::Finalize();
}