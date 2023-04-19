assign7.o:assign7.c 
	gcc -c assign7.c 

a7:assign7.o
	gcc assign7.o -o a7

clean:
	rm *.o a7
