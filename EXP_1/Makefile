root = Lab1-2

$(root):$(root).o
	g++ -o $(root) $(root).o
$(root).o:$(root).cpp
	g++ -c $(root).cpp

clean:
	del /Q /F *.o *.exe