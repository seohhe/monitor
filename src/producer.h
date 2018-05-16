#pragma once

#include "monitor.h"
#include "conditional.h"

class Producer : public Monitor {
public:
	Producer();

	static Conditional prod;

	void produce();

	~Producer();
};