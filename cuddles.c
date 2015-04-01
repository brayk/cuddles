 /*	
  *	Kameron Bray
  *	CSC180 - Assignment 2
  *	TWO PLAYER GAMES - GASTANK CHESS
  *	Project: CUDDLES
  *	c: gcc -Wall cuddles.c -o cuddles 
  *	r: ./cuddles
  *	i: CRCR		// start_column, start_row, end_column, end_row
  *			// ex: B1C3  (kNight to C3)
  *	Heuristics
  *	- Piece values: 
  *	- Having Gas > 1:
  *	- Don't lose:
 */
/*
	Piece Mechanics:
	Knight: Up 2 Over 1 || Over 1 Up 2
	Bishop: Diagnal any amount, can only take first piece.. any piece
	Queen:  Any direction, any amount, can only take first piece.. any piece
	King:   One space, any direction, can land and take a piece any piece
*/
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>


#define R 7 // row count
#define C 8 // col count
#define T 2 // tab count

// Table 1:		Table 2
/*

7 - N B Q K B N -	7 - 3 3 3 3 3 3 -
6 - - - - - - - -	6 - - - - - - - -
5 - - - - - - - -	5 - - - - - - - -
4 - - - - - - - - 	4 - - - - - - - -
3 - - - - - - - -	3 - - - - - - - -
2 - - - - - - - -	2 - - - - - - - -
1 - n b q k b n - 	1 - 3 3 3 3 3 3 -
  A B C D E F G H	  A B C D E F G H
// Lower case is human
// Upper case is compu


*/

// Initialize Variables
char b[T][R][C]; // board

// History file name
const char *const fileName = "history1.txt";

// ANSI Escape Color Codes
const char *const green		= "\033[00;32;40m"; 	// Computer
const char *const normal 	= "\033[0m";		// Normal
const char *const red		= "\033[01;31;40m";	// Red Pattern
const char *const teal 		= "\033[01;36;40m"; 	// Player

// Initialize Methods
void initBoard();
void prinBoard();
void clearScreen(int i);

int main()
{
  initBoard();
  prinBoard("23", "23", 0);
  // loop
  clearScreen(10);
  prinBoard("A2B4", "B8C2", 0); // with your move
  prinBoard("A2B4", "B8C2", 1); // with your computer move
  return 0;
}

void initBoard()
{
  int c_t, c_r, c_c; // current table, row, column
  for(c_t = 0; c_t < T; c_t++)  //loop table
  {
      for(c_r = 0; c_r < R; c_r++) // loop rows
      {
        for(c_c = 0; c_c < C; c_c++) // loop col
        {
          // insert pieces
          if(c_t == 0 && c_r == 0 && (c_c == 1 || c_c == 6))	 // init kNights
          {
            b[c_t][c_r][c_c] = 'N';
          }
          else 
          if(c_t == 0 && c_r == 6 && (c_c == 1 || c_c == 6))
          {
            b[c_t][c_r][c_c] = 'n';
          }
          else 
          if(c_t == 0 && c_r == 0 && (c_c == 2 || c_c == 5))	 // init Bishop
          {
            b[c_t][c_r][c_c] = 'B';
          }
          else 
          if(c_t == 0 && c_r == 6 && (c_c == 2 || c_c == 5))
          {
            b[c_t][c_r][c_c] = 'b';
          }
          else 
          if(c_t == 0 && c_r == 0 && (c_c == 3))		 // init Queen
          {
            b[c_t][c_r][c_c] = 'Q';
          }
          else 
          if(c_t == 0 && c_r == 6 && (c_c == 3))
          {
            b[c_t][c_r][c_c] = 'q';
          }
          else 
          if(c_t == 0 && c_r == 0 && (c_c == 4)) 		// init King
          {
            b[c_t][c_r][c_c] = 'K';
          }
          else 
          if(c_t == 0 && c_r == 6 && (c_c == 4))
          {
            b[c_t][c_r][c_c] = 'k';
          }

          // fill every other space with dot
          else
          {
            b[c_t][c_r][c_c] = '%';
          }

          // Initiate Gas = 3
          if(c_t == 1 && (c_r == 0 || c_r == 6) && (c_c > 0 && c_c < C-1))
          {
            b[c_t][c_r][c_c] = '3';
          }

        }
      }
  }
}


void clearScreen(int i)
{
  // clear the screen and position cursor
  printf("\e[1;1H\e[2J"); 	// clear screen 
  printf("\e[100B"); 		// move to bottom
  printf("\e[%dA", i);  	// move up board information height
}


void prinBoard(char* playerMove, char* computerMove, int turn) // int 0 is computer, 1 is player
{

  
  

  // addToHistoryFile(fileName); TODO
 
 
  // print turn info
  if(turn == 0)
  {
    printf("\nYour last move was: %12s; \nComputer last move was: %8s; \nThe next turn is %sComputer's%s\n", playerMove, computerMove, green, normal); 	// TODO INDENT/ALIGN MOVE
  }
  else
  {
    printf("\nYour last move was: %12s; \nComputer last move was: %8s; \nThe next turn is %sYours%s\n", playerMove, computerMove, teal, normal);	// TODO ALIGN
  }

  int c_r, c_c;
  for(c_r = 0; c_r < R; c_r++) // Loop Rows
  {
    printf("%d  ", (R - c_r));
    for(c_c = 0; c_c < C; c_c++) // Loop Col
    {
    	if(isupper((unsigned char)b[0][c_r][c_c]))
    	{
    	  printf("%s", green);
    	}
    	else
    	if(islower((unsigned char)b[0][c_r][c_c]))
    	{
    	  printf("%s", teal);
    	}
    	else 
    	if(c_r - 6 == c_c || c_r - 4 == c_c || c_r - 2 == c_c || c_r == c_c || c_r + 2 == c_c || c_r + 4 == c_c || c_r + 6 == c_c)
    	{
    	  printf("%s", red);
    	}
        printf("%c",  b[0][c_r][c_c]);
        
        // always color counts as the tyle they are on
        if(c_r - 6 == c_c || c_r - 4 == c_c || c_r - 2 == c_c || c_r == c_c || c_r + 2 == c_c || c_r + 4 == c_c || c_r + 6 == c_c)
    	{
    	  printf("%s", red);
    	}
    	else
    	{
    	  printf("%s", normal);
    	}
    	printf("%c ", b[1][c_r][c_c]);
    	printf("%s", normal); // make sure it returns text to normal color
     
    }
    printf("\n");
  }
  printf("   -----------------------\n   A  B  C  D  E  F  G  H \n");
}
