# The compiler to use is for C++
CC=g++
# The compiler options are (all warnings)
CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 –c -I/usr/local/include/ -c
# The linker options are (all warnings)
LDFLAGS=-Wall `pkg-config --libs opencv` -std=c++11 -lpigpio -lrt -lpthread -lraspicam -lraspicam_cv -lopencv_core -lopencv_highgui


all: AutoCar

#SortServer: 4618_Template.o server.o ControlPi.o
	#$(CC) $(LDFLAGS) 4618_Template.o server.o ControlPi.o -o SortServer
	
#AutoCar: main.o CCar.o CMotor.o CGuidance.o server.o
#	$(CC) $(LDFLAGS) main.o CCar.o CMotor.o CGuidance.o server.o -o AutoCar

AutoCar: main.o CCar.o CMotor.o CGuidance.o server.o CCommunication.o CSensor.o
	$(CC) $(LDFLAGS) main.o CCar.o CMotor.o CGuidance.o server.o CCommunication.o CSensor.o -o AutoCar

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

CCar.o: CCar.cpp CCar.h
	$(CC) $(CFLAGS) CCar.cpp

CMotor.o: CMotor.cpp CMotor.h
	$(CC) $(CFLAGS) CMotor.cpp
	
CGuidance.o: CGuidance.cpp CGuidance.h
	$(CC) $(CFLAGS) CGuidance.cpp
	
CCommunication.o: CCommunication.cpp CCommunication.h
	$(CC) $(CFLAGS) CCommunication.cpp

server.o: server.cpp server.h
	$(CC) $(CFLAGS) server.cpp

CSensor.o: CSensor.cpp CSensor.h
	$(CC) $(CFLAGS) CSensor.cpp

clean:
	rm *o output
