objects = Lab1-1.o

Lab1-1:$(objects)
	g++ -o Lab1-1 $(objects)

Lab1-1.o:Lab1-1.cpp
	g++ -c Lab1-1.cpp

clean:
	del /Q /F *.o Lab1-1.exe