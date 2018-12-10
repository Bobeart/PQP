#include <stdio.h>
#include <curses.h>
#include "macros.h"
#include <signal.h>

void cleanup(int sig);

int main(void) {
	WINDOW *main_window
	int headx, int heady;
	initscr();
	main_window = newwin(0,0,0,0);
	leaveok(main_window, TRUE); // turn off cursor
	keypad(stdscr, TRUE); 		// get arrow keys
	nonl(); 					// no Newline->carriage return/newline on output
	cbreak();					// don't wait for \n
	noecho();					// don't echo keys pressed

	// set up interrupts
	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);
	signal(SIGQUIT, cleanup);


	printf("%c\n", 'b');
	print_board();
	return 0;
}

// draw the starting border
void drawborder(WINDOW *win){
	int i;

	
}

// close curses and exit the application
void cleanup(int sig){
	endwin();
	exit(0);
}
