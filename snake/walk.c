/* show a person walking using curses */

#include <stdio.h>
#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

void drawBox(WINDOW *win);
void drawScreen(WINDOW *win, int personyold, int personxold, 
		int persony, int personx);
void cleanUp(int sig);
void getMove(int *movex, int *movey);
void movePerson(int *personxold, int *personyold, int *personx, int *persony, 
	      int movex, int movey);

#define MIN_X		21
#define MAX_X		59
#define MIN_Y		7
#define MAX_Y 		17
#define DELAY		100

int main(int argc, char *argv[]) {
  WINDOW *main_window;
  int personxold, personyold;
  int personx, persony;
  int movex, movey;
  
  /* initialize curses stuff */  
  initscr();
  main_window = newwin(0,0,0,0);
  leaveok(main_window,TRUE);	/* turn off cursor? */
  keypad(stdscr, TRUE);		/* get arrow keys */
  nonl();			/* no NL->CR/NL on output  */
  cbreak();			/* don't wait for \n */
  noecho();			/* don't echo keys pressed */
  
  /* set up interrupt handlers */
  signal(SIGINT, cleanUp);
  signal(SIGTERM, cleanUp);
  signal(SIGQUIT, cleanUp);
  
  /* initialize person */
  personx = (MAX_X - MIN_X) / 2 + MIN_X;
  persony = (MAX_Y - MIN_Y) / 2 + MIN_Y;
  movex = 0;
  movey = 0;
  
  /* draw starting positions */
  drawBox(main_window);
  drawScreen(main_window, personxold, personyold, personx, persony);
  
  /* loop until exit on Ctrl-C */
  while (1) { 
    getMove(&movex, &movey);
    movePerson(&personxold, &personyold, &personx, &persony, movex, movey);
    drawScreen(main_window, personxold, personyold, personx, persony);
  }
}

/* get keyboard move */
void getMove(int *movex, int *movey) {
  int c;
  *movex = 0;
  *movey = 0;

  c = getch();			/* block here until keypressed */
  if (c == 'j')
    *movex = -1;
  if (c == 'k')
    *movex = +1;
  if (c == 'i')
    *movey = -1;
  if (c == 'm')
    *movey = +1;
}

/* move the person based on x,y velocity and walls */
void movePerson(int *personxold, int *personyold, int *personx, int *persony, 
	      int movex, int movey) {

  /* move the person */
  *personxold = *personx;
  *personyold = *persony;
  *personx = *personx + movex;
  *persony = *persony + movey; 

  /* hit walls? */
  if (*personx < MIN_X)
    *personx = MIN_X;
  if (*personx > MAX_X)
    *personx = MAX_X;
  if (*persony < MIN_Y)
    *persony = MIN_Y;
  if (*persony > MAX_Y)
    *persony = MAX_Y;
}

/* draw the screen */
void drawScreen(WINDOW *win, int personxold, int personyold, 
		int personx, int persony){
  mvwaddch(win, personyold, personxold, ' ');
  mvwaddch(win, persony, personx, 'O');
  drawBox(win);
  wrefresh(win);
}

/* draw the starting box */
void drawBox(WINDOW *win) {
  int i;

  /* horizontal bars */
  for (i=0; i<39; i++) {
    mvwaddch(win, 6, i+21, '-');
    mvwaddch(win, 18, i+21, '-');
  }

  /* vertical bars */
  for (i=0; i<11; i++) {
    mvwaddch(win, i+7, 20, '|');
    mvwaddch(win, i+7, 60, '|');
  }    

  wrefresh(win);
}

/* close curses and exit */
void cleanUp(int sig) {
  endwin();
  exit(0);
}