//Jake Miller

#include<string.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main(){
	setupterm((char *)0, 1, (int *)0);

	// output the # of rows of the terminal
	printf("Total Rows: %d\n",tigetnum("lines"));
	// output the # of colummns of the terminal
	printf("Total Columns: %d\n",tigetnum("cols"));
	
	// execute unix command to sleep for 5 sec
	system("sleep 5"); // Or sleep(5) w/ unistd.h

	// clear the terminal
	putp(tigetstr("clear"));
	
	while (1) {
		// get user input for (row, column)
		putp("Enter: (row,column)");
		char input[10];
		scanf("%s", input);

		// parse user input
		int r = atoi(strtok(input, ","));
		int c = atoi(strtok(NULL, ","));

		// quit if user entered row or column is less than 0
		if (r < 0 || c < 0)
			break;
	
		// move cursor to that location
		putp(tparm(tigetstr("cup"), r, c));
	}
}
