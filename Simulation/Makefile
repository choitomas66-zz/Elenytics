CC = g++
CFLAGS = -g -Wall

default: simulation

simulation:  wifiAPv2.o Room.o AP.o utilities.o
	$(CC) $(CFLAGS) -o simulation wifiAPv2.o Room.o AP.o utilities.o

wifiAPv2.o:  wifiAPv2.cpp utilities.h Room.h AP.h
	$(CC) $(CFLAGS) -c wifiAPv2.cpp

Room.o:  room.cpp Room.h 
	$(CC) $(CFLAGS) -c room.cpp

APP.o:  AP.cpp AP.h
	$(CC) $(CFLAGS) -c AP.cpp

utilities.o:  utilities.cpp utilities.h 
	$(CC) $(CFLAGS) -c utilities.cpp

clean: 
	$(RM) simulation *.o *~