#pragma once

#include <stdlib.h>
#include <mpi.h>
#include "buffer.h"

#include <boost/mpi.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/serialization/string.hpp> 
#include <boost/archive/text_oarchive.hpp> 
#include <boost/archive/text_iarchive.hpp> 

namespace mpi = boost::mpi;

class Monitor{

protected:
  struct Buff buff; 
  int id;
  int size;
  int max;
  mpi::communicator world;

public:
  Monitor();
  
  int active;
  static void loop();
  void enterCritical();
  void leaveCritical();
  void lock();
  void unlock();

  ~Monitor();
};