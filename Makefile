#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
USER= ogilviethompsonh
=======
USER= grigullb
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
USER= grigullb
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
USER= grigullb
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
USER= grigullb
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba

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

chatServer.o: chatServer.cpp fifo.h
	$(CC) -c $(CFLAGS) chatServer.cpp

chatAjax.o: chatAjax.cpp fifo.h
	$(CC) -c $(CFLAGS) chatAjax.cpp

chatTest: chatTest.o fifo.o
	$(CC) chatTest.o fifo.o -o chatTest

chatServer: chatServer.o fifo.o
	$(CC) chatServer.o  fifo.o -o chatServer

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

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)

clean:
	rm -f *.o chatAjax chatServer chatTest
