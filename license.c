#include "config.h"

// Initialize object
int initlicense() {
	shm->block = 0;

	printf("number of licenses available: %d\n", shm->availLicenses);

	return shm->childProc;
}

int getlicense() {
	if((shm->processes >= shm->availLicenses) || shm->availLicenses == 1) {
		shm->block = 1;  // Block until one becomes available
	} else {
		shm->block = 0;
	}

	return shm->block;
}

// Increment licenses available
int returnlicense() {
	shm->childProc--;
	return shm->childProc;
}

// Add n licenses to the number available
void addtolicenses(int n) {
	shm->childProc - n;
	shm->processes--;
}

// Decrements the number of licenses by n
void removelicenses(int n) {
	
	shm->childProc + n;
}

// Log the messages to output file
void logmsg(char *pid, char *c, char *repeat) {
	FILE *ofptr;

	// Open outfile
	if((ofptr = fopen("logfile.data", "a")) == NULL) {
		perror("runsim: Error: ");
		exit(1);
	}
	
	// Append time
	addTime(ofptr);
	
	// Print msg to file
	fprintf(ofptr, "%s %s of %s\n", pid, c, repeat);

	// Close outfile
	fclose(ofptr);
}

// Add current time
void addTime(FILE *ofptr) {
	time_t tm;
	time(&tm);
	struct tm *tp = localtime(&tm);

	fprintf(ofptr, "%.2d:%.2d:%.2d ", tp->tm_hour, tp->tm_min, tp->tm_sec);
}
