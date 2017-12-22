SRC=main.c LogAnalyze.cpp
PROG=LogAnalyze
CC=g++
LIB=-lpthread


$(PROG):main.o LogAnalyze.o
	$(CC) -o  $@ $^  $(LIB) -std=c++11 -g

%.o:%.cpp
	$(CC) -c $<


.PHONY:clean
clean:
	rm -rf *.o  $(PROG)
