# Source: https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
CC = mpic++

TARGET ?= a.out
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(shell mpicc --showme:compile) $(shell mpicc --showme:link)

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(TARGET): $(OBJS)
		$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) -lpthread -lboost_mpi -lboost_serialization $(LDLIBS)

.PHONY: clean
clean:
		$(RM) $(TARGET) $(OBJS) $(DEPS)

#-include $(DEPS)