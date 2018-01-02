
ROOT_PATH=$(shell pwd)

SRC=main.cpp
DST=mysql
LIB_PATH=-L ./lib
LIB=-lmysqlclient
HEAD= -I ./include


$(DST):$(SRC)
	g++ -o $@ $^  $(HEAD) $(LIB)  $(LIB_PATH)

.PHONY:
clean:
	rm mysql

