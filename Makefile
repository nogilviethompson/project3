#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:

USER= xuy

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: chatServer chatTest chatAjax PutCGI PutHTML
#all: chatServer chatTest 

chatTest.o: chatTest.cpp fifo.h
	$(CC) -c $(CFLAGS) chatTest.cpp

chatServer.o: chatServer.cpp fifo.h chatroom.h
	$(CC) -c $(CFLAGS) chatServer.cpp

chatAjax.o: chatAjax.cpp fifo.h
	$(CC) -c $(CFLAGS) chatAjax.cpp

chatTest: chatTest.o fifo.o
	$(CC) chatTest.o fifo.o -o chatTest

chatServer: chatServer.o fifo.o chatroom.o
	$(CC) chatServer.o  fifo.o chatroom.o -o chatServer

chatroom.o: chatroom.cpp chatroom.h
		g++ -c chatroom.cpp
	
fifo.o:		fifo.cpp fifo.h
		g++ -c fifo.cpp

chatAjax: chatAjax.o  fifo.h
	$(CC) chatAjax.o  fifo.o -o chatAjax -L/usr/local/lib -lcgicc

PutCGI: chatAjax
	chmod 757 chatAjax
	cp chatAjax /usr/lib/cgi-bin/$(USER)_chatAjax.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp chat.html /var/www/html/class/softdev/$(USER)
	cp chat.js /var/www/html/class/softdev/$(USER)
	cp chat.css /var/www/html/class/softdev/$(USER)

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)

clean:
	rm -f *.o chatAjax chatServer chatTest