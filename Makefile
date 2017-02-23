#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= ogilviethompsonh

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: chatServer chatTest
#all: chatServer chatTest

chatTest.o: chatTest.cpp fifo.h
	$(CC) -c $(CFLAGS) chatTest.cpp

chatServer.o: chatServer.cpp fifo.h
	$(CC) -c $(CFLAGS) chatServer.cpp

chatTest: chatTest.o fifo.o
	$(CC) chatTest.o fifo.o -o chatTest

chatServer: chatServer.o fifo.o
	$(CC) chatServer.o  fifo.o -o chatServer

fifo.o:		fifo.cpp fifo.h
		g++ -c fifo.cpp
clean:
	rm -f *.o chatServer chatTest
