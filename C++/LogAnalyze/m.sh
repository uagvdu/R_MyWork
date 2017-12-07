#! /bin/bash


make clean
make

#echo 带色输出： echo -e 
#print  直接输出  ；  带色格式都是一样的
echo -e  "\033[40;34;1m ************************* \033[0m"
echo 
./test
echo 
echo -e  "\033[40;34;1m ************************* \033[0m"

