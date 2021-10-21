--------------------------------------------------------
To compile program:
make

To clean:
make clean
--------------------------------------------------------
Method of invocation:
	./runsim n < testing.data // Where n is an integer greater than or equal to 1. This will be used as the number of available licenses.
				  // Note: The parent process takes away 1 license, so if n = 1, only one license will be available and no children will be able to be 
				  // forked so program will wait for 20 seconds and then terminate without printing anything to logfile.data.  
--------------------------------------------------------
