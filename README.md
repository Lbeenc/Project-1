# Project-1
This project consists of a parent and a child process , oss and user. 
oss creates user 
uuser executes a loop that prints the users pid , pidd and the iteration number , it also sleeps for 1 second between iterations

How to compile:
to compile type and run "make"
this creates the oss and the user processes

and to clean type and run "make clean"

How to Run:
run the oss file with this format
./oss -n (number of processes) -s (max simultaneous processes) -t (iterations per child process)
example: 
./oss -n 1 -s 2 -t 3

./oss -h : displays help info
