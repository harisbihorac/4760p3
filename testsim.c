#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int shmid;
struct nLicenses *shm;

int main(int argc, char* argv[]) {
	signal(SIGINT, signalHandler);
	
	int sleepT = atoi(argv[1]);
	int repeatF = atoi(argv[2]);
	int i = atoi(argv[3]);
	key_t key = 5678;

	
	// Get shared memory id from parent
	if((shmid = shmget(key, sizeof(struct nLicenses) * 2, 0666)) < 0) {
		perror("testsim: Error: shmget ");
		exit(1);
	}

	// Attach shared memory to child
	if((shm = (struct nLicenses *)shmat(shmid, NULL, 0)) == (struct nLicenses *) -1) {
		perror("testsim: Error: shmat ");
		exit(1);
	}

	int c, j, k, n = shm->childProc;
	int max = 0;
	shm->choosing[(n-1)] = 1;

	for(c = 0 ; c < repeatF ; c++) {
		if((shm->turnNum[c]) > max) {
			max = (shm->turnNum[c]);
		}
		shm->turnNum[(n-1)] = 1 + max;

		shm->choosing[(n-1)] = 0;
		for(j = 0 ; j < n ; j++) {
			while(shm->choosing[j] == 1) {}
				while((shm->turnNum[j] != 0) && (shm->turnNum[j] < shm->turnNum[(n-1)])) {}
		}

		// Critical section
		pid_t id = getpid();
		char pid[50];
		char num[50];
	
		sprintf(pid, "%d", id);
		sprintf(num, "%d", (c + 1));

		printf("Printing msg to file: %s %s of %s\n", pid, num, argv[2]);

		// Print to output fie using logmsg
		logmsg(pid, num, argv[2]);

		// Sleep before looping again
		sleep(sleepT);
		
		// Exit critical section
		shm->turnNum[(n-1)] = 0;

	}

	//shm->processes--;
	addtolicenses(1);
	killProcesses();
	return 0;
}

void signalHandler() {
	pid_t id = getpid();
	killProcesses();
	killpg(id, SIGINT);
	exit(1);
}

void killProcesses() {
	shmdt(shm);
}
