SRC=main.c LogAnalyze.cpp
PROG=LogAnalyze
CC=g++
LIB=-lpthread  -lmysqlclient

LIB_PATH=-L ./Mysql/lib
HEAD= -I ./Mysql/include


$(PROG):main.o LogAnalyze.o
	$(CC) -o  $@ $^  $(LIB) -std=c++11 $(LIB_PATH) -g

%.o:%.cpp
	$(CC) -c $< $(HEAD)


.PHONY:clean
clean:
	rm -rf *.o  $(PROG)
