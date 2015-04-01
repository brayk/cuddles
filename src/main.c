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
#include<unistd.h>
#include<time.h>

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
int first = 1;

// ANSI Escape Color Codes
const char *const green		= "\033[00;32;40m"; 	// Computer
const char *const normal 	= "\033[0m";		// Normal
const char *const red		= "\033[01;31;40m";	// Red Pattern
const char *const teal 		= "\033[01;36;40m"; 	// Player

// File names
const char *const history 	= "./his/history1.txt";
const char *const intro		= "./res/intro.txt";
const char *const iWin		= "./res/iWin.txt";
const char *const uWin		= "./res/uWin.txt";


// Initialize Methods
void  initBoard();
void  prinBoard(int turn);
void  prinInfo(const char* fileName);
int   count_lines_of_file(const char* filename);
void  clearScreen();
int   whoIsFirst();
void  gameLoop(int first);
int   requestMove();
int   aToInt(char alpha);
int   validate(int i, char* lastMove, char* nextMove);
int   gameOver();

// Game States
char* lastPMove;
char* lastCMove;

int main()
{
  initBoard();
  clearScreen();
 // prinInfo(intro);
  first = 1;//whoIsFirst(); // 0 is cuddles 1 is input
  gameLoop(first);
  return 0;
}

void gameLoop(int first)
{
  int game = 1;
  if(first)
  {
    printf("\nPlayer Input has entered the battle.\n");
    prinBoard(1);
    while(!requestMove());
    prinBoard(0);            // prompt -> accept -> check -> reprompt? -> update and print
    
  }
  else
  {
    printf("\nCuddles has entered the battle.\n");
    first = 1;
  }

  while(game)
  {
   if(gameOver()){break;}
   while(!requestMove());
   // makeMove(
   prinBoard(1);
   // if(gameOver){break};
  }

  printf("\nGame Over!\n");
}

int gameOver()
{
    int cpuK = 0;
    int playerK = 0;
    int r, c;
    for(r = 0; r < R; r++)
    {
        for(c = 0; c < C; c++)
        {
            if(b[0][r][c] == 'K')
            {
                cpuK = 1;
            }
            if(b[0][r][c] == 'k')
            {
                playerK = 1;
            }
        }
    }
    
    if(cpuK == 0 || playerK == 0)
    {
        return 1;
    }

    return 0;

}

int requestMove()
{
  char* input = calloc(4, 1);
  char piece[2];
  printf("Move: ");
  scanf("%s", input);
  lastPMove = input;
  printf("You entered: %s, let me think.", input);
    
  int lastPieceC = aToInt(lastPMove[0]);
  int lastPieceR = abs((lastPMove[1] - '0') -7);
  int newPieceC = aToInt(lastPMove[2]);
  int newPieceR = abs((lastPMove[3] - '0') - 7);

  // save current piece and gas, place in the new position with gas -1
  piece[0] = b[0][lastPieceR][lastPieceC];
  piece[1] = b[1][lastPieceR][lastPieceC];
  

  if(!validate( (int) 1, piece, piece))
  {
    return 0;
  }


  
  b[0][lastPieceR][lastPieceC] = '%';
  b[1][lastPieceR][lastPieceC] = '%';
    
  b[0][newPieceR][newPieceC] = piece[0];
  // sprtinf(b[1][newPieceR][newPieceC] = 
  b[1][newPieceR][newPieceC] = ((piece[1] - '0') - 1) + '0';

  return 1; // RETURN 1 IF VALID MOVE
 //
}


int validate(int turn, char* lastMove, char* nextMove)
{

  // DOES THERE EXIST A PIECE: TODO IS IT THEIR PIECE?
  if(lastMove[0] > 'z' || lastMove[0] < 'A')
  {
        printf("\nNot a valid move\n");
        return 0;
  }
  if(lastMove[1] == '0')
  {
       printf("\nNot a valid move\n");
       return 0;

  }
  // IS THE NEXT SPOT IN BOUNDS
  
  
  // IS THE NEXT SPOT A VALID PLACEMENT,
  // NIGHT -> UP 2 OVER 1, UP 1 OVER 2...
  //






  return 1;
}
int aToInt(char alpha)
{
    if(alpha == 'A')
    {
        return 0;
    }
    if(alpha == 'B')
    {
        return 1;
    }
    if(alpha == 'C')
    {
        return 2;
    }
    if(alpha == 'D')
    {
        return 3;
    }
    if(alpha == 'E')
    {
        return 4;
    }
    if(alpha == 'F')
    {
        return 5;
    }
    if(alpha == 'G')
    {
        return 6;
    }
    if(alpha == 'H')
    {
        return 7;
    }

    return 0;
}
int whoIsFirst()
{
  char input;
  scanf("%s", &input);
  if(input == 'I' || input == 'i' )
  {
  	return 1;
  }
  return 0;
}
void prinInfo(const char* fileName)
{
  // read amount of lines
  int lineCount =  count_lines_of_file(fileName);
  // 27 up from the botttom start printing characters bottom up
  // move another lineCount up then start printing line by line
  clearScreen(27+lineCount);
  FILE *fp = fopen(fileName, "r");
  char line[256];
  while(fgets(line, sizeof(line), fp))
  {
    printf("%s", line);
   // nanosleep((struct timespec[]){{0,200000000}}, NULL);
  }
  fclose(fp);
}

int count_lines_of_file(const char *file_path) 
{
  FILE *fp = fopen(file_path, "r");
  int line_count = 0;
  size_t buffer_s = 80;
  char *buffer = malloc(buffer_s * sizeof(char));
  if(fp == NULL)
  {
    fclose(fp);
    return 0;
  }
  while (-1 != getline(&buffer, &buffer_s,fp))
  {
    line_count++;
  }
  fclose(fp);
  return line_count;
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
          if(c_t == 0 && c_r == 1 && (c_c == 3 || c_c == 5))	 // init kNights
          {
            b[c_t][c_r][c_c] = 'N';
          }
          else 
          if(c_t == 0 && c_r == 5 && (c_c == 3 || c_c == 5))
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
          if(c_t == 1 && (c_r == 1 || c_r == 5) && (c_c == 3 || c_c == 5))
          {
            b[c_t][c_r][c_c] = '3';
          }

          if(c_t == 1 && (c_r == 0 || c_r == 6) && (c_c >= 2 && c_c <= 5))
          {

            b[c_t][c_r][c_c] = '3';
          }
        }
      }
  }
}


void clearScreen()
{
  // clear the screen and position cursor
  printf("\e[1;1H\e[2J"); 	// clear screen 
 // printf("\e[999B"); 		// move to bottom
 // printf("\e[%dA", i);  	// move up board information height
}


void prinBoard(int turn) // int 0 is computer, 1 is player
{

  
  

  // addToHistoryFile(fileName); TODO
 
 
  // print turn info
  if(turn == 0)
  {
    printf("\nYour last move was: %12s; \nComputer last move was: %8s; \nThe next turn is %sComputer's%s\n", lastPMove, lastCMove, green, normal); 	// TODO INDENT/ALIGN MOVE
  }
  else
  {
    printf("\nYour last move was: %12s; \nComputer last move was: %8s; \nThe next turn is %sYours%s\n", lastPMove, lastCMove, teal, normal);	// TODO ALIGN
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
