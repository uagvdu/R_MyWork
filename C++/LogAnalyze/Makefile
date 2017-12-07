DST=test
cc=g++

all: $(DST)

$(DST):test.o main.o
	$(cc) -o   $@ $^ -g
%.o:%.cpp 
	$(cc) -c $<

.PHONY:clean
clean:
	rm -rf $(DST) *.o
