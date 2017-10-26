/* Ian Winter                               */
/* New Beginnings                           */
/* Homework #5                              */
/*                                          */
/* Kingdom of Frupal                        */
/* Player can move around a map and collect */
/* treasure. If you run out of energy,      */
/* you die.                                 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAPLEN 10
#define MAXSTRLEN 100
#define MAXENERGY 10

/* Funciton prototypes */
void menu(void);
int getpos(int x, int y, int ncols);
void printmap(void);
void init(void);
void checkpos(void);
void printstatus(void);
void printhelp(void);
void move(int x, int y);
void populatemap(void);
void checkenergy(void);

/* Global variables */
int xpos = MAPLEN / 2;
int ypos = MAPLEN / 2;
int treasure = 0;
int energy = MAXENERGY;
int *map = NULL;		/* points to map array */

/* Function implementations */

/* Initialization */
void init(void)
{
    srand(time(NULL));
    map = calloc(MAPLEN * MAPLEN, sizeof(int));
    populatemap();
}

/* Populates the map with treasure. */
void populatemap(void)
{
    int i;

    for (i = 0; i < (MAPLEN * MAPLEN); ++i)
	if (rand() < RAND_MAX / 20)
	    *(map + i) = 1;
}

/* Uses string entry to navigate menu. */
void menu(void)
{
    char command[MAXSTRLEN];
    int noupdate;		/* If TRUE, skips player update checks. */

    while (TRUE) {
	noupdate = FALSE;
	printf("Enter command: ");
	scanf("%s", command);
	if (!strcmp(command, "n") || !strcmp(command, "k")) {
	    move(0, 1);
	} else if (!strcmp(command, "s") || !strcmp(command, "j")) {
	    move(0, -1);
	} else if (!strcmp(command, "e") || !strcmp(command, "l")) {
	    move(1, 0);
	} else if (!strcmp(command, "w") || !strcmp(command, "h")) {
	    move(-1, 0);
	} else if (!strcmp(command, "help")) {
	    printhelp();
	    noupdate = TRUE;
	} else if (!strcmp(command, "status")) {
	    printstatus();
	    noupdate = TRUE;
	} else if (!strcmp(command, "map")) {
	    printmap();
	    noupdate = TRUE;
	} else if (!strcmp(command, "quit")) {
	    exit(0);
	} else {
	    printf("Invalid entry.\n");
	    noupdate = TRUE;
	}
	if (noupdate == FALSE) {
	    printstatus();
	    checkpos();
	    checkenergy();
	}
    }
}

/* Print a list of commands. */
void printhelp(void)
{
    printf("List of commands:\n"
	   "n, e, s, w - Move north, south, east or west.\n"
	   "      help - Print this menu.\n"
	   "    status - Print current status.\n"
	   "       map - Print data map.\n"
	   "      quit - Quit the game.\n");
}

/* Returns an array index from coordinates and number of columns. */
int getpos(int x, int y, int ncols)
{
    return ncols * y + x;
}

/* Prints data map with numbers  */
/* representing grovik status.   */
/*  Code:                        */
/*  0 - Nothing    @ - Player    */
/*  1 - Treasure                 */
void printmap(void)
{
    int x, y;

    for (y = MAPLEN - 1; y >= 0; --y) {
	for (x = 0; x < MAPLEN; ++x) {
	    if (x == xpos && y == ypos)
		printf("%c", '@');
	    else
		printf("%d", *(map + getpos(x, y, MAPLEN)));
	}
	printf("\n");
    }
}

/* Prints status and map in **beautiful** ascii. */
void printstatus(void)
{
    int x, y;

    for (y = MAPLEN - 1; y >= 0; --y) {
	for (x = 0; x < MAPLEN; ++x) {
	    if (x == xpos && y == ypos)
		printf("%c", '@');
	    else if (*(map + getpos(x, y, MAPLEN)) == 1)
		printf("%c", '$');
	    else
		printf("%c", '.');
	}
	printf("\n");
    }
    printf("Pos:(%d,%d) Energy: %d/%d Treasure: %d\n", xpos, ypos,
	   energy, MAXENERGY, treasure);
}

/* Checks if you die from having 0 energy */
void checkenergy(void)
{
    if (energy == 0) {
	printf("You lay down for a nap.\nA grue eats you.\nYou die.\n");
	printf("Final score: %d\n", treasure);
	exit(0);
    }
}

/* Checks for anything interesting at player's current position. */
void checkpos(void)
{
    int loc = getpos(xpos, ypos, MAPLEN);

    if (*(map + loc) == 1) {	/* there is treasure! */
	printf("You found treasure!\nYou are not so tired.\n");
	++treasure;
	energy = MAXENERGY;
	*(map + loc) = 0;
    }

}

/* Moves player in an x, y coordinate. */
void move(int x, int y)
{
    if (x != 0 && xpos + x >= 0 && xpos + x < MAPLEN) {
	xpos += x;
	--energy;
    } else if (y != 0 && ypos + y >= 0 && ypos + y < MAPLEN) {
	ypos += y;
	--energy;
    } else {
	printf("You ran into a wall! Ouch!\n");
    }
}

int main(void)
{
    init();
    printf("HOT TIP: Type 'help' for list of commands.\n");
    menu();
    return 0;
}
