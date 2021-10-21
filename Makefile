output: hw1.o
	g++ hw1.o output

hw1.o: hw1.c
	g++ -c hw1.c

clean:
	rm *.o output
