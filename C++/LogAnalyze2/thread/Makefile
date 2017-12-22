
SRC=main.cpp thread.cpp

DST=thread

LIB=-lpthread

CC=g++

$(DST):main.o thread.o
	$(CC) -o $@ $^  $(LIB) -g

%.o:%.cpp
	$(CC) -c $<


.PHONY:clean
clean:
	rm *.o $(DST)
