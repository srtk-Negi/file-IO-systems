assign7.o:assign7.c 
	gcc -c assign7.c 

assign7:assign7.o
	gcc assign7.o -o assign7

clean:
	rm *.o assign7
