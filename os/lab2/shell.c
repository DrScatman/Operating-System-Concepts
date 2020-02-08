// Jake Miller
// John Taube
// Date: 1/18/2020
// Class CIS 452-20
// Description: A simple shell/terminal
  
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	while(1) {
		printf("Enter command: ");			

		// Take user input
		char input[256];
		if(!fgets(input, 256, stdin)) {
			perror("Error");
			break;
		}
		if(!strcmp(input, "quit\n"))
			break;

		// Replace newline character with string termination character
		size_t length = strlen(input);
			if (input[length - 1] == '\n')
				input[length - 1] = '\0';

		// Parse user input
		char* word = strtok(input, " ");
		char* arr[128] = {};
		int count = 0;
		while(word) {
			arr[count++] = word;
			word = strtok(NULL, " ");
		}

		pid_t who = fork();

		if (who < 0) {
			perror("Failed to fork()");
		} else if (who > 0) {
			struct rusage buf;

			// Parent waits for child to terminate
			int sts;
			who = wait(&sts);

			// Retrieve resource stats for child
			getrusage(RUSAGE_CHILDREN, &buf);

			// Print the resource statistics
			printf("\nResource usage:\n");
			printf("User CPU time: %lld.%lld sec\n", (long long)buf.ru_utime.tv_sec,(long long)buf.ru_utime.tv_usec);
			printf("Involuntary context switches: %ld\n", buf.ru_nivcsw);
		} else {
			// Child executes command
			execvp(arr[0], &arr[0]);
			perror("Error");
			exit(63);
		}
	}
	return 0;
}