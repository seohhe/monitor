#include "monitor.h"

class Producer : Monitor {
private:

public:
	Producer(int id);

	void produce();

	~Producer();
};