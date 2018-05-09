#include "monitor.h"

class Consumer : Monitor
{
private:

public:
	Consumer(int id);

	void consume();

	~Consumer();
	
};