output: ssoo.o execute.o

ssoo.o: SSOO.cpp
	g++ -c SSOO.cpp

execute.o: SSOO.cpp archivo_listado_ips.txt
	./SSOO archivo_listado_ips.txt

clean: 
	rm *.o output
