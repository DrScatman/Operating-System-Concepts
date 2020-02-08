#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <signal.h>
#include <time.h>

void sigListener();

int running = 1;

int main() 
{
	pid_t child, parent;
	parent = getpid();
	// Set up signal listeners
	signal(SIGUSR1, sigListener);
	signal(SIGUSR2, sigListener);
	signal(SIGINT, sigListener);

	if ((child = fork()) < 0) {
		perror("Fork failed");
		exit(1);
	}
	else if (child == 0) {
		// Child listens for kill signal from parent
		signal(SIGINT, sigListener);
		int randInt; //delay time
		
		while (running) {
			//generates a number between 1 and 5 and sleeps
			srand((unsigned) time(0)); 
			randInt = 1 + rand() % (5);
			sleep(randInt);
	
			randInt = 1 + rand() % 2; 
			if (randInt == 1)
				kill(parent, SIGUSR1);
			else
				kill(parent, SIGUSR2);
		}
		
		//printf("Child process ending grafefully\n");
	}
	else {
		// Parent process
		printf("Spawned a child child, PID# %d\n", child);

		// Uses pause() to block itself until signal received from the child
		while (running) {
			printf("waiting...");
			// Flush the display since no \n was sent
			fflush(stdout);
			pause();
		}

		kill(child, SIGINT);
		wait(NULL);
		printf("Program ending gracefully\n");
	}

	return 0;
}

// Listens for signals and handles them
void sigListener(int sigNum)
{
	char* signal;
	switch (sigNum)
	{
		case SIGUSR1:
			signal = "SIGUSR1";
			break;
		case SIGUSR2:
			signal = "SIGUSR2";
			break;
		case SIGINT:
			signal = "SIGINT";
			break;
	}

	printf("Received %s\n", signal);
	if (sigNum == SIGINT) {
		running = 0;
	}
}