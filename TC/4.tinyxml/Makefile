.PHONY: default clean

CC := g++
TARGET := test1 test2
INCS := ./tinyxml

COMMONSRCS=$(wildcard ./tinyxml/*.cpp)
COMMONOBJS=$(patsubst %.cpp,%.o,$(COMMONSRCS))

OBJS := test1.o test2.o

default : $(TARGET)


define libs_rules
$(1): $(COMMONOBJS) $(OBJS)
	$(CC) -o $$@ $(COMMONOBJS) $(filter $(1).o,$(OBJS))
endef
$(foreach n, $(TARGET), $(eval $(call libs_rules, $(n))))

%.o:%.cpp
	$(CC) -c $< -o $@ $(addprefix -I, $(INC))

clean:
	rm $(TARGET) $(COMMONOBJS) $(OBJS) -f
