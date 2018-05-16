#pragma once

#include <mpi.h>

typedef struct ConditionalArray { int x[20]; } ConditionalArray;

struct Buff {
	int n;

	ConditionalArray queue;

	int type;
};