// Jake Miller
// John T
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <signal.h>
#include <time.h>
#include <thread>
#include <pthread.h>
#include <mutex>

using namespace std;

void sigListener(int sigNum);
void handleThread(string arg);

#define NUM_THREADS 25
#define FILE_NAME_SIZE 1024
int running = 1;
int status[NUM_THREADS];
int totalFiles = 0;
int totalReq = 0;
mutex _mutex;

int main() {
	// Listen for ctrl-c to break from loop and exit gracefully
	signal(SIGINT, sigListener);

	// Arguments to send to pthread when created.
	char fileName[FILE_NAME_SIZE];

	while (running){
		// Get the file name
		std::cout << "Enter a file name to search: ";
		scanf("%s", fileName);
		
		// Create thread
		thread thr(handleThread, fileName);
		thr.detach();

		totalReq ++;
	}
	
	std::cout << "\nReceived Requests: " << totalReq << "\tFiles Found: " << totalFiles;
	return 0;
}

void handleThread(string arg) {
	srand((unsigned) time(0)); 
	int num = 1 + rand() % (10); // 1 - 10

	// 20% chance long sleep 80% chance short sleep
	if (num == 1 || num == 2) {
		int restNum = 7 + rand() % (10 - 7  + 1); //random 7-10 second sleep
		sleep(restNum);
	}
	else
	{
		sleep(1);
	}
	
	// Thread-lock critical section
	unique_lock<mutex> lock(_mutex);
	
	cout << "\nFile Found:\t" << arg << "\n";
	totalFiles ++;

	// Unlock mutex exiting critical section
	lock.unlock();
	
	// Exit detached thread
	pthread_exit(NULL);
}

// Listens for signals and handles them
void sigListener(int sigNum)
{
	if (sigNum == SIGINT) {
		// Close stdin (scanf) & exit loop
		running = 0;
		fclose(stdin);
	}
}

