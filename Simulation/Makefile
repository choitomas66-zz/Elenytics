CC = g++
CFLAGS = -g -Wall

default: simulation

simulation:  wifiAP.o Room.o AP.o utilities.o
	$(CC) $(CFLAGS) -o simulation wifiAP.o Room.o AP.o utilities.o

wifiAP.o:  wifiAP.cpp utilities.h Room.h AP.h
	$(CC) $(CFLAGS) -c wifiAP.cpp

Room.o:  room.cpp Room.h 
	$(CC) $(CFLAGS) -c room.cpp

APP.o:  AP.cpp AP.h
	$(CC) $(CFLAGS) -c AP.cpp

utilities.o:  utilities.cpp utilities.h 
	$(CC) $(CFLAGS) -c utilities.cpp

clean: 
	$(RM) simulation *.o *~