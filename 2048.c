// Name: Benjamin Knott
// Date: 11/10/25
// Class: EGNR 265
// Assignment: Project 2
// Purpose: To create a game, SlideSquare, that moves tiles around a grid
// a given direction, and merges adjacent tiles while doubling their value.
// Compiled on: Code::Blocks

#define TERM_PC
#include "slidesq_support.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ROW 4 // # of rows
#define COL 4 // # of columns

char Char_Input(char valid[], int j, int y);
int Int_in_Range(int low, int high);
void Disp_Grid(int grid[][COL]);
void New_Value(int grid[][COL]);
void Move_Right(int grid[][COL], int *score1);
void Move_Left(int grid[][COL], int *score1);
void Move_Up(int grid[][COL], int *score1);
void Move_Down(int grid[][COL], int *score1);
void Copy_Grid(int grid[][COL], int gridCpy[][COL]);
int Compare_Grid(int grid[][COL], int gridCpy[][COL]);
void Color_Grid(int val);
int Game_Over(int grid[][COL]);
void Clear_Grid(int grid[][COL]);

int main()
{
    char up = 'w', down = 's', left = 'a', right = 'd', move;
    char valid[4] = {'\0', '\0', '\0', '\0'};
    int i, menu = -1, grdCpy[ROW][COL], grd[ROW][COL] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int validMove, score = 0, highScore = 0, newHighScore = 0, turn = -1, gameOver;
    srand(time(0));

    do
    {
        //Displays menu to user
        Clear_Screen();
        Generate_Border(0,1,75,20,0x9E,0xB0);
        Movetoxy(5,3);
        Set_Color(11);
        printf("2048");
        Movetoxy(9,5);
        Set_Color(0xD);
        printf("MAIN MENU");
        Movetoxy(5,7);
        Set_Color(11);
        printf("Please select an option below");
        Movetoxy(4,9);
        Set_Color(3);
        printf("1 Instructions");
        Movetoxy(4,10);
        printf("2 Select keys for movement");
        Movetoxy(4,11);
        printf("3 Play 2048");
        Movetoxy(4,12);
        printf("0 Exit");

        // Displays keys used for controls
        Movetoxy(49,8);
        Set_Color(0x9E);
        printf("Controls: ");
        Movetoxy(49,9);
        printf("Up:    %c  ", up);
        Movetoxy(49,10);
        printf("Down:  %c  ", down);
        Movetoxy(49,11);
        printf("Left:  %c  ", left);
        Movetoxy(49,12);
        printf("Right: %c  ", right);

        // Prints current high score
        Set_Color(11);
        Movetoxy(44,14);
        printf("Current High Score: %d", highScore);

        // Allows user to select an option from the menu
        Movetoxy(2,14);
        printf("   Select a choice: ");
        menu = Int_in_Range(0,3);

      Clear_Screen();

      // Create menu to accept unit of input from user
      if (menu == 1)
      {
          // Display instructions to user on how to play SlideSquare
          Generate_Border(0,1,77,19,0x9E,0xB0);
          Movetoxy(2,2);
          Set_Color(0x97);
          printf("                            How to play 2048                              ");
          Movetoxy(2,4);
          Set_Color(7);
          printf("To play 2048, you will need to press the given keys (that you can change),");
          Movetoxy(2,5);
          printf("%c, %c, %c, and %c, to move the tiles around. Tiles will move in the", up, down, left, right);
          Movetoxy(2,6);
          printf("direction you enter, and if they hit another tile of the same value, the");
          Movetoxy(2,7);
          printf("tiles will merge together and their value will double.");
          Movetoxy(2,9);
          printf("For every move that is made, an additional value, either 2 or 4, will");
          Movetoxy(2,10);
          printf("be added to a random location.");
          Movetoxy(2,12);
          printf("Score is kept by adding the value of tiles that are created from merges.");
          Movetoxy(2,14);
          printf("The game will end if no more moves can be made, or 0 is entered at any");
          Movetoxy(2,15);
          printf("time.");
          Movetoxy(2,17);
          Wait_For_Enter();
      }

      // Let user enter keys for movement
      else if (menu == 2)
      {
          for (i=0; i<4; i++) // Resets valid char array to null in preparation for comparison
              valid[i] = '\0';
          Generate_Border(0,1,60,13,0x9E,0xB0);

          Set_Color(3);
          Movetoxy(2,2);
          printf("Select key for moving up: ");
          up = Char_Input(valid, 0, 2); // Pass the char function, index, and y coordinate
          printf("%c", up);             // to position error message in correct location
          Set_Color(3);
          Movetoxy(2,4);
          printf("Select key for moving down: ");
          down = Char_Input(valid, 1, 4);
          printf("%c", down);
          Set_Color(3);
          Movetoxy(2,6);
          printf("Select key for moving left: ");
          left = Char_Input(valid, 2, 6);
          printf("%c", left);
          Set_Color(3);
          Movetoxy(2,8);
          printf("Select key for moving right: ");
          right = Char_Input(valid, 3, 8);
          printf("%c", right);
          Set_Color(11);
          Movetoxy(2,10);
          Wait_For_Enter();
      }

      // Game is played here
      else if (menu == 3)
      {
          score = 0;
          turn = -1;
          validMove = 1;
          New_Value(grd); // Initializes a value into grid
          Generate_Border(0,1,75,23,0x9E,0xB0);
          do
          {
              if (validMove == 1)
              {
                  New_Value(grd); // Inserts a new value for every move, or a second one for the initial start
                  turn++;
              }
              Copy_Grid(grd, grdCpy); // Creates a copy of grid for comparison
              Disp_Grid(grd); // Displays grid to user

              // Displays score information
              Set_Color(0x0D);
              if (score > highScore && score > newHighScore) // Updates high score
                  newHighScore = score;
              if (newHighScore != 0) // Prints high score
              {
                  Movetoxy(36,3);
                  printf("High Score: %d", newHighScore);
              }
              Movetoxy(36,4);
              printf("Score: %d", score); // Prints score
              Set_Color(0x0C);
              Movetoxy(36,6);
              printf("Turns: %d", turn); // Prints # of turns completed

              // Prints current controls to screen
              Set_Color(3);
              Movetoxy(36,8);
              printf("Up:    %c", up);
              Movetoxy(36,9);
              printf("Down:  %c", down);
              Movetoxy(36,10);
              printf("Left:  %c", left);
              Movetoxy(36,11);
              printf("Right: %c", right);
              Movetoxy(76,23); // Move cursor to the corner
              Set_Color(7);

              gameOver = Game_Over(grd); // Checks if any valid moves are available,
              if (gameOver == 1)               // and if not, game is over
              {
                  Delay10ms(125);
                  Wait_For_Enter();
                  break;
              }

              move = getch(); // Obtain movement input from user and call corresponding function
              if (move == right)
                  Move_Right(grd, &score);
              else if (move == left)
                  Move_Left(grd, &score);
              else if (move == up)
                  Move_Up(grd, &score);
              else if (move == down)
                  Move_Down(grd, &score);

              Movetoxy(36,15);
              printf("                "); // Clears the "Move is invalid" message
              if (move != '0')
                  validMove = Compare_Grid(grd, grdCpy); // Ensure inputted movement is valid by
                                                         //comparing to previously copied grid
          } while(move != '0');

          // Displays new high score, if any, and returns to main menu
          Movetoxy(4,20);
          if (newHighScore > highScore)
          {
              Set_Color(0xB4);
              printf("NEW HIGH SCORE!! - %d ", newHighScore);
              Movetoxy(4,21);
              Set_Color(7);
          }

          printf("Exiting game...    ");
          Delay10ms(300);
          highScore = newHighScore;
          Clear_Grid(grd);
      }
   }while (menu != 0);
}

// Accepts character input from user, validates it, and ensures character hasn't already been used
char Char_Input(char valid[], int j, int y)
{
    int i;
    char input;

    do
    {
       input = getch(); // Gets character input
       if ((input < ' ') || (input > '~')) // Validates character input
       {
           Movetoxy(2,y+1);
           Set_Color(12);
           printf("Input not a valid character.. try again.");
           Movetoxy(31,y);
       }
       for (i=0; i<4; i++) // Ensures character hasn't already been used
       {
           if (input == valid[i])
           {
               Movetoxy(2,y+1);
               Set_Color(12);
               printf("Character already used.. try again.");
               Movetoxy(31,y);
               break;
           }
       }
    } while ((input < ' ') || (input > '~') || input == valid[i]);
    valid[j] = input;
    Set_Color(7);

    return input;
}

// Accepts an integer input in a specified range.
int Int_in_Range(int low, int high)
{
   int value = 0;

   do
   {
       Set_Color(7);
       scanf("%d",&value); // Obtains integer input from user
       if ((value < low) || (value > high)) // Validates integer input
       {
           Set_Color(12);
           printf("Input out of range.. try again.\n");
       }
   } while ((value < low) || (value > high));

   return value;
}

// Displays the grid to the screen
void Disp_Grid(int grid[][COL])
{
    int i, k, j=2, l=4;
    Movetoxy(l,j);
    for (i=0; i<ROW; i++)
    {
        Movetoxy(l, j);
        for (k=0; k<29; k++) // Prints horizontal line
        {
            printf("%c", 196);
        }

        Movetoxy(l,j+1);
        printf("%c", 179);
        for(k=0; k<COL; k++) // Prints top part of colored tile, as well as grid lines
        {
            Color_Grid(grid[i][k]);
            printf("      ");
            Set_Color(7);
            printf("%c", 179);
            if (k == (COL-1))
                Movetoxy(l,j+2);
        }

        printf("%c", 179);
        for(k=0; k<COL; k++) // Prints middle part of colored tile with value, as well as grid lines
        {
            Color_Grid(grid[i][k]);
            if (grid[i][k] != 0)
                printf("%5d ", grid[i][k]);
            else
                printf("      ", grid[i][k]);
            Set_Color(7);
            printf("%c", 179);
            if (k == (COL-1))
                Movetoxy(l,j+3);
        }

        printf("%c", 179);
        for(k=0; k<COL; k++) // Prints bottom part of colored tile, as well as grid lines
        {
            Color_Grid(grid[i][k]);
            printf("      ");
            Set_Color(7);
            printf("%c", 179);
            if (k == (COL-1))
                Movetoxy(l,j+4);
        }
        j+=4;
    }

    Movetoxy(l, j);
    for (k=0; k<29; k++) // Prints bottom line in grid
    {
        printf("%c", 196);
    }
    Movetoxy(4,20);
    printf("Press 0 to end game");
}

// Checks for an empty location in the grid, and if there is, inserts 1 or 2 there
void New_Value(int grid[][COL])
{
    // Checks to see if there is an empty location and therefore game is not done
    int r, c, i, k, num, valid = 0;
    for (i=0; i<ROW; i++)
    {
        for(k=0; k<COL; k++)
        {
            if (grid[i][k] == 0)
            {
                valid = 1;
                break;
            }
        }
        if (valid == 1)
            break;
    }
    // Inserts 2 or 4 into random location in grid
    if (valid == 1)
    {
        do
        {
            r = Random_Int(0,ROW);
            c = Random_Int(0,COL);
            if (grid[r][c] == 0)
            {
                // Makes 2 appear 90% of the time, and 4 appear 10% of the time
                num = Random_Int(1,11);
                if (num >= 1 && num <= 9)
                    grid[r][c] = 2;
                else if (num == 10)
                    grid[r][c] = 4;
                break;
            }
        }while (grid[r][c] != 0);
    }
}

// Moves all values in grid to the right, and merges adjacent values
void Move_Right(int grid[][COL], int *score1)
{
    int i, k, j, n, total;
    for (i=0; i<ROW; i++)
    {
        for(k=(COL-1); k>0; k--) // Shifts all non-zero values to the right
        {
            total=0;
            for (j=k; j>=0; j--)
                total+=grid[i][j];
            if (total == 0)
                break;
            while (grid[i][k] == 0)
            {
                j = k;
                while(j > 0)
                {
                    grid[i][j] = grid[i][j-1];
                    grid[i][j-1] = 0;
                    j--;
                }
            }
        }

        for (k=(COL-1); k>0; k--) // Merges same values if they are adjacent in the direction movement is made
        {
            if (grid[i][k] == grid[i][k-1])
            {
                grid[i][k] = grid[i][k] * 2;
                grid[i][k-1] = 0;
                *score1 += grid[i][k];
                for(n=k-1; n>0; n--) // Shifts all non-zero values to the right after merge
                {
                    total=0;
                    for (j=n; j>=0; j--)
                        total+=grid[i][j];
                    if (total == 0)
                        break;
                    while (grid[i][n] == 0)
                    {
                        j = n;
                        while(j > 0)
                        {
                            grid[i][j] = grid[i][j-1];
                            grid[i][j-1] = 0;
                            j--;
                        }
                    }
                }
            }
        }
    }
}

// Moves all values in grid to the left, and merges adjacent values
void Move_Left(int grid[][COL], int *score1)
{
    int i, k, j, n, total;
    for (i=0; i<ROW; i++)
    {
        for(k=0; k<(COL-1); k++) // Shifts all non-zero values to the left
        {
            total=0;
            for (j=k; j<=(COL-1); j++)
                total+=grid[i][j];
            if (total == 0)
                break;
            while(grid[i][k] == 0)
            {
                j=k;
                while(j < (COL-1))
                 {
                    grid[i][j] = grid[i][j+1];
                    grid[i][j+1] = 0;
                    j++;
                 }
            }
        }

        for(k=0; k<(COL-1); k++) // Merges same values if they are adjacent in the direction movement is made
        {
            if (grid[i][k] == grid[i][k+1])
            {
                grid[i][k] = grid[i][k] * 2;
                grid[i][k+1] = 0;
                *score1 += grid[i][k];
                for(n=(k+1); n<(COL-1); n++) // Shifts all non-zero values to the left after merge
                {
                    total=0;
                    for (j=n; j<=(COL-1); j++)
                        total+=grid[i][j];
                    if (total == 0)
                        break;
                    while(grid[i][n] == 0)
                    {
                        j=n;
                        while(j < (COL-1))
                         {
                            grid[i][j] = grid[i][j+1];
                            grid[i][j+1] = 0;
                            j++;
                         }
                    }
                }
            }
        }
    }
}

// Moves all values in grid upward, and merges adjacent values
void Move_Up(int grid[][COL], int *score1)
{
    int i, k, j, n, total;
    for (k=0; k<COL; k++)
    {
        for(i=0; i<(ROW-1); i++) // Shifts all non-zero values upwards
        {
            total=0;
            for (j=i; j<=(ROW-1); j++)
                total+=grid[j][k];
            if (total == 0)
                break;
            while(grid[i][k] == 0)
            {
                j=i;
                while(j < (ROW-1))
                 {
                    grid[j][k] = grid[j+1][k];
                    grid[j+1][k] = 0;
                    j++;
                 }
            }
        }

        for(i=0; i<(ROW-1); i++) // Merges same values if they are adjacent in the direction movement is made
        {
            if (grid[i][k] == grid[i+1][k])
            {
                grid[i][k] = grid[i][k] * 2;
                grid[i+1][k] = 0;
                *score1 += grid[i][k];
                for(n=(i+1); n<(ROW-1); n++) // Shifts all non-zero values upwards after merge
                {
                    total=0;
                    for (j=n; j<=(ROW-1); j++)
                        total+=grid[j][k];
                    if (total == 0)
                        break;
                    while(grid[n][k] == 0)
                    {
                        j=n;
                        while(j < (ROW-1))
                         {
                            grid[j][k] = grid[j+1][k];
                            grid[j+1][k] = 0;
                            j++;
                         }
                    }
                }
            }
        }
    }
}

// Moves all values in grid downward, and merges adjacent values
void Move_Down(int grid[][COL], int *score1)
{
    int i, k, j, n, total;
    for (k=0; k<COL; k++) // Shifts all non-zero values upwards
    {
        for(i=(ROW-1); i>0; i--)
        {
            total=0;
            for (j=i; j>=0; j--)
                total+=grid[j][k];
            if (total == 0)
                break;
            while (grid[i][k] == 0)
            {
                j = i;
                while(j > 0)
                {
                    grid[j][k] = grid[j-1][k];
                    grid[j-1][k] = 0;
                    j--;
                }
            }
        }

        for (i=(ROW-1); i>0; i--) // Merges same values if they are adjacent in the direction movement is made
        {
            if (grid[i][k] == grid[i-1][k])
            {
                grid[i][k] = grid[i][k] * 2;
                grid[i-1][k] = 0;
                *score1 += grid[i][k];
                for(n=i-1; n>0; n--) // Shifts all non-zero values upwards after merge
                {
                    total=0;
                    for (j=n; j>=0; j--)
                        total+=grid[j][k];
                    if (total == 0)
                        break;
                    while (grid[n][k] == 0)
                    {
                        j = n;
                        while(j > 0)
                        {
                            grid[j][k] = grid[j-1][k];
                            grid[j-1][k] = 0;
                            j--;
                        }
                    }
                }
            }
        }
    }
}

// Creates a copy of grid before a move is made to prepare for comparing it
void Copy_Grid(int grid[][COL], int gridCpy[][COL])
{
    int i, k;
    for (i=0; i<ROW; i++) // Goes through array, and assigns each value to another array
    {
        for(k=(COL-1); k>=0; k--)
        {
            gridCpy[i][k] = grid[i][k];
        }
    }
}

// Compares grid before and after a move is made to see if it is valid
int Compare_Grid(int grid[][COL], int gridCpy[][COL])
{
    int i, k, valid=0;

    for (i=0; i<ROW; i++) // Goes through arrays and checks if they aren't equal, and returns 1 if true
    {
        for(k=(COL-1); k>=0; k--)
        {
            if (gridCpy[i][k] != grid[i][k])
                valid = 1;
        }
    }

    if (valid == 0) // Prints error message if both arrays are identical
    {
        Movetoxy(36,15);
        Set_Color(4);
        printf("Move is invalid!");
        Set_Color(7);
    }

    return(valid);
}

// Sets color of grid based on its value
void Color_Grid(int val)
{
    if (val == 2)        // Sets a color depending on the value that is passed to the function through
        Set_Color(0x10); // a series of 'if' statements
    else if (val == 4)
        Set_Color(0x20);
    else if (val == 8)
        Set_Color(0x30);
    else if (val == 16)
        Set_Color(0x60);
    else if (val == 32)
        Set_Color(0xC0);
    else if (val == 64)
        Set_Color(0x40);
    else if (val == 128)
        Set_Color(0xE0);
    else if (val == 256)
        Set_Color(0xD0);
    else if (val == 512)
        Set_Color(0xB0);
    else if (val == 1024)
        Set_Color(0xA0);
    else if (val == 2048)
        Set_Color(0xF0);
    else if (val == 4096)
        Set_Color(0xE4);
    else if (val == 8192)
        Set_Color(0xEC);
    else if (val > 8192)
        Set_Color(0xF4);
}

// Detects if there are no more valid moves, and thus the game is over
int Game_Over(int grid[][COL])
{
    int i, k;

    // Tests for an empty spot in grid, meaning game is not over, and returns 0 if there is one
    for (i=0; i<ROW; i++)
    {
        for (k=0; k<COL; k++)
        {
            if (grid[i][k] == 0)
                return(0);
        }
    }

    for (i=0; i<ROW; i++) // Looks for adjacent values in grid in the horizontal direction,
    {                     // meaning game is not over, and returns 0 if found
        for (k=0; k<(COL-1); k++)
        {
            if (grid[i][k] == grid[i][k+1])
                return(0);
        }
    }

    for (i=0; i<(ROW-1); i++) // Looks for adjacent values in grid in the vertical direction,
    {                         // meaning game is not over, and returns 0 if found
        for (k=0; k<COL; k++)
        {
            if (grid[i][k] == grid[i+1][k])
                return(0);
        }
    }

    // Prints error message if grid is full and no adjacent values exist.
    Movetoxy(36,15);
    Set_Color(4);
    printf("No more valid moves. Game is over.");

    Movetoxy(4,20);
    printf("                    "); // Covers "Press 0 if done" text
    Movetoxy(36,17);
    Set_Color(7);

    return(1);
}

// Clears the contents of the grid
void Clear_Grid(int grid[][COL])
{
    int i, k;

    for (i=0; i<ROW; i++) // Goes through each element in array, and resets them back to 0.
    {
        for (k=0; k<COL; k++)
        {
            grid[i][k] = 0;
        }
    }
}
