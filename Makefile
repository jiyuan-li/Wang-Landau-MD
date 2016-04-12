FLAGS = -std=c++11 -Wall -O3
CC = g++
H = $(wildcard $(MD)*.h)
SRCS = $(wildcard $(MD)*.cpp) 

OBJS = $(SRCS:.cpp=.cpp.o)
$(info Serial result = $(OBJS))
$(info Serial result = $(H))

main: $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o a.out

%.cpp.o: %.cpp
	$(CC) $(FLAGS) $(DEBUG) -c -o $@ $< 
clean:
	rm *.cpp.o
