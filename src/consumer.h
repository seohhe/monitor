#pragma once

#include "monitor.h"
#include "conditional.h"

class Consumer : public Monitor {
public:
	Consumer();

	static Conditional cons;

	void consume();

	~Consumer();
	
};