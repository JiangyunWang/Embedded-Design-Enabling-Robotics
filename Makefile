myGPIO: main.o ZedBoard.o GPIO.o
	g++ -std=c++0x main.o ZedBoard.o GPIO.o -o myGPIO -lpthread

main.o: main.cpp ZedBoard.o GPIO.o
	g++ -std=c++0x -g -Wall -c main.cpp -lpthread

ZedBoard.o: ZedBoard.cpp ZedBoard.h
	g++ -std=c++0x -g -Wall -c ZedBoard.cpp -lpthread

GPIO.o: GPIO.cpp GPIO.h
	g++ -std=c++0x -g -Wall -c GPIO.cpp -lpthread

clean:
	rm myGPIO main.o ZedBoard.o GPIO.o
