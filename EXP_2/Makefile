root = Lab2-1

$(root):$(root).o
	g++ -o $(root) $(root).o
$(root).o:$(root).cpp
	g++ -c $(root).cpp

clean:
	del /Q /F *.o *.exe