/*  2048_support.h
 *     DO NOT modify this file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>   // or other WinApi header   (for color)
#include <time.h>      // for time (used in srand()
#include <conio.h>     // getch()

/* other provided constants */
#define C_GRAY   0x07   // define "standard" character color


/* provided functions (prototypes) */
void Clear_Screen(void);      // clear the terminal/console screen
void Wait_For_Enter(void);    // prompt and wait for user (to press enter)
int Movetoxy(int x, int y );  // move cursor to position X,Y on console screen
void Set_Color(int color);    // change color of cursor
int Random_Int(int low, int high); // return an random integer between high/low
void Delay10ms(int duration); // wait for 10 milliseconds
  // create bounding box of an ASCII character and color
void Generate_Border(int x1, int y1, int x2, int y2, unsigned char color, unsigned char what);

/*--------------------------------------------------------------*/
/* The following functions are provided.  Do not modify them!!  */
/*--------------------------------------------------------------*/

//***************************************************************
// CLEAR_SCREEN()
//  clear console window
//  Accepts nothing
//  Returns nothing
void Clear_Screen(void)
{
#ifdef TERM_PC
//previous versions:
//  system("cls");
//  clrscr();
//  printf("\e[1;1H\e[2J");

  HANDLE  hConsole;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  SMALL_RECT scrollRect;
  COORD scrollTarget;
  CHAR_INFO fill;

  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Get the number of character cells in the current buffer.
  if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    return;

  // Scroll the rectangle of the entire buffer.
  scrollRect.Left = 0;
  scrollRect.Top = 0;
  scrollRect.Right = csbi.dwSize.X;
  scrollRect.Bottom = csbi.dwSize.Y;

  // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
  scrollTarget.X = 0;
  scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

  // Fill with empty spaces with the buffer's default text attribute.
  fill.Char.UnicodeChar = TEXT(' ');
  fill.Attributes = csbi.wAttributes;

  // Do the scroll
  ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

  // Move the cursor to the top left corner too.
  csbi.dwCursorPosition.X = 0;
  csbi.dwCursorPosition.Y = 0;

  SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
#endif // TERM_PC

#ifdef TERM_LINUX
  clrscr();
#endif // TERM_LINUX

#ifdef TERM_UNKNOWN
  printf("\033[2J");   // clear screen (ncurses)
  printf("\033[1;1H"); // move cursor to 1,1
#endif // TERM_LINUX
}  // Clear_Screen()


//***************************************************************
// WAIT_FOR_ENTER()
//  prompts and then wait for user to press <enter> key
//  Accepts nothing
//  Returns nothing
void Wait_For_Enter(void)
{
  fflush(stdin);        // clear out input buffer
#ifdef TERM_PC
//previous version:
//  system("pause");
  printf("Press any key to continue . . .");
  getch();
#endif // TERM_PC

#ifdef TERM_LINUX
  printf("Press <enter> to continue . . . ");
  getchar();
#endif // TERM_LINUX
} // Wait_For_Enter()


//***************************************************************
// MOVETOXY()
//  Move cursor to X,Y coordinate on console window
//  Accepts X,Y coordinate to move the cursor to
//  Returns TRUE if it successfully moved the cursor, FALSE otherwise
//     DO NOT modify
int Movetoxy(int x, int y )
{
   COORD xy;
   int value;

   xy.X = x;
   xy.Y = y;
   value = SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), xy );
   if (!value)
     printf("movetoxy failed! (%d,%d) out of bounds.\n", x, y);

   return value;
} // movetoxy()


//***************************************************************
// SET_COLOR()
//  change color for cursor to display next character
//  Accepts integer of selected color (text, background, etc.)
//  Returns nothing
//     REQUIRES: <windows.h>
void Set_Color(int color)
{
  SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color);
} // set_color()


//***************************************************************
// DELAY10MS()
//  wait for specified amount of time (# of 1/100th of a second)
//  Accepts integer of number of 1/100th of a second to delay
//  Returns nothing
//     REQUIRES: <time.h>
void Delay10ms(int duration)
{
   long int stop;
   if (duration <= 0)  // make sure positive duration
	   return;   // do nothing if bad argument

   stop = clock()+(duration*CLOCKS_PER_SEC/100);
   while (clock() < stop);        // wait for 1/100th of a second
} // delay()


//***************************************************************
// RANDOM_INT()
// Return a random integer value between min and max
// Accepts min,max values
//   Note: the generator must be seeded first by srand()
//      e.g.  invoke the function by the following:
//          srand(time(0));
//  place the call somewhere early in your main program
int Random_Int(int low, int high)
{
  int range;

  range = high - low;
  if (high > low)
    return (rand()%range + low);
  if (range == 0)
    return low;
  printf("Bad values for random_int()\n");
    return(-1);
} // random_int()


//***************************************************************
// GENERATE_BORDER()
// Create a box in console screen (x1,y1 to x2,y2) consisting of
//   specified color and ASCII character
// Accepts x1, y1, x2, y2, color, what _character values
//   Note: coordinates specified must be within screen dimensions
// REQUIRES: <windows.h>, Movetoxy(), Set_Color()
void Generate_Border(int x1, int y1, int x2, int y2, unsigned char color, unsigned char what)
{
  int r, c;

  Set_Color(color);
  Movetoxy(x1,y1-1);
  for (c=x1;c<=x2;c++)
    putchar(what);
  for (r=y1;r<y2;r++)
  {
    Movetoxy(x1,r);
    putchar(what);
    Movetoxy(x2,r);
    putchar(what);
  }
  Movetoxy(x1,y2);
  for (c=x1;c<=x2;c++)
    putchar(what);
  Set_Color(C_GRAY);
}


/*  2048_support.h
 *     DO NOT modify this file.
 */



