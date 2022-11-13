output: ssoo.o ping.o
	g++ ssoo.o ping.o -o output

ssoo.o: SSOO.cpp
	g++ -c SSOO.cpp

ping.o: ping.cpp
	g++ -c ping.cpp

clean: 
	rm *.o output
