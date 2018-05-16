#pragma once

#include <stdlib.h>
#include <string>
#include <mpi.h>
#include <unistd.h>
#include "buffer.h"
#include "conditional.h"

class Monitor{

protected:
  struct Buff buff; 
  int id;
  int size;
  MPI_Request* requests;
  struct Buff* responses;
  int notify;

public:
  static Conditional criticalSection;

  int active;

  Monitor();

  void enterCritical();
  void sendBuff(struct Buff* buff, int type, int target);
  void recvBuff(struct Buff* buff);
  void loop();
  void leaveCritical(bool f = false);
  void wait(Conditional* cond);
  void signal(Conditional* cond);
  void log(std::string action);
};