#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"
#include <ctime>

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
   terminal_open();
  	terminal_set(SETUP_MESSAGE);

	srand((unsigned) time(NULL));
        
	/*
	    The code below provides a skeleton of the game play.  You will need to
	    write code for setting up the game board, and playing the game itself.
	    You can modify the code given as needed.
	    
	    Call the functions that you have written in the game play file, and that
	    you have added to the Actor class.
	*/
 	
 	//Create and initialise game board
	const int CONSOLE_WIDTH = 80, CONSOLE_HEIGHT = 25, COORD_BUFFER = 5;
   int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT] = {0};
 	
	/*
	    Initiallize locations in the game board to have game features.  What if you
	    have man things to add to the game board?  Should you use a loop?  Does it
	    make sense to store this information in a file?  Should this code be a
	    function as well?
	*/
	const int WALL_X = 40, WALL_WIDTH = 13, WALL_Y = 10;
	//This loop set a wall in the middle of the board
	for (int index = 0; index < WALL_WIDTH; index++)
	{
		gameBoard[WALL_X + index][WALL_Y] = SHALL_NOT_PASS;
		gameBoard[WALL_X + index][WALL_Y + 1] = SHALL_NOT_PASS;	
	}
	
	// These two for loops set a border of walls around the board
	for (int index = 0; index < CONSOLE_WIDTH; index++)
	{
		gameBoard[index][0] = SHALL_NOT_PASS;
		gameBoard[index][CONSOLE_HEIGHT - 2] = SHALL_NOT_PASS;
	}
	
	for (int index = 0; index < CONSOLE_HEIGHT - 1; index++)
	{
		gameBoard[0][index] = SHALL_NOT_PASS;
		gameBoard[CONSOLE_WIDTH - 1][index] = SHALL_NOT_PASS;
	}
    
   // Set the safe zone
   const int WIN_X = 45, WIN_Y = 7;
   gameBoard[WIN_X][WIN_Y] = WINNER;
   gameBoard[WIN_X+1][WIN_Y] = WINNER;
   gameBoard[WIN_X][WIN_Y+1] = WINNER;
	gameBoard[WIN_X+1][WIN_Y+1] = WINNER;
	 
	// Set speed boost
   const int SPEED_X = 20, SPEED_Y = 30;
   gameBoard[SPEED_X][SPEED_Y] = SPEED;

	
	// Printing the instructions
	int keyEntered = TK_A;  

   out.writeLine("Welcome to Goose Escape!");
   out.writeLine("This is you (@)");
   out.writeLine
	("Use the arrow keys to avoid the goose (G) and reach the safe zone (%)");
   out.writeLine("Grab the powerup (S) for a speed boost!");
   out.writeLine("Press B to begin");
    
   //Wait for player to initiate game from start menu
   while(keyEntered != TK_B)
    	keyEntered = terminal_read();
    	
	terminal_clear_area(MIN_SCREEN_X, MIN_SCREEN_Y, NUM_SCREEN_X, NUM_SCREEN_Y);
	
	//Initial speed
	const int SPEED = 1;
	
	//make the player
	int playX = COORD_BUFFER, playY = COORD_BUFFER;
	do
	{
  		playX = randomNumber(CONSOLE_WIDTH - COORD_BUFFER); 
   	playY = randomNumber(CONSOLE_HEIGHT - COORD_BUFFER); 
	}
	while (gameBoard[playX][playY] != EMPTY);
	Actor player(PLAYER_CHAR, playX, playY, SPEED);
	
	//make the monster
	int monX = CONSOLE_WIDTH - COORD_BUFFER;
	int monY = CONSOLE_HEIGHT - COORD_BUFFER;
	const int MIN_SEPARATION = 5;
	do
	{
		monX = randomNumber(CONSOLE_WIDTH - COORD_BUFFER); 
   	monY = randomNumber(CONSOLE_HEIGHT - COORD_BUFFER); 
	}
	while(fabs(monX - playX) <= MIN_SEPARATION &&
		fabs(monY - playY) <= MIN_SEPARATION && gameBoard[monX][monY] != EMPTY);
	Actor monster(MONSTER_CHAR, monX, monY, SPEED);

	/*
	    This is the main game loop.  It continues to let the player give input
	    as long as they do not press escape or close, they are not captured by
	    the goose, and they didn't reach the win tile
	*/
	/*
	    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
	    key being pressed.
	*/
    
   while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
      && !captured(player,monster) && !won(player, gameBoard))
	{
		drawBoard(gameBoard);
	   // get player key press
	   keyEntered = terminal_read();

      if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
      {
        	// move the player, you can modify this function
    	  	movePlayer(keyEntered, player, gameBoard);
    	  	// move the goose
    	  	movePlayer(gooseDirection(player, monster), monster, gameBoard);	    
      }
  	}

   if (keyEntered != TK_CLOSE)
   {
    	//print win/loss statement
      if (checkWin(gameBoard, player.get_x(), player.get_y()))
        	terminal_print(2, 24, "You won!");
      else 
        	terminal_print(2, 24, "You lose :(");
    	terminal_refresh();
	
    	// Wait until user closes the window
      while (terminal_read() != TK_CLOSE);
   }

	//game is done, close it  
   terminal_close();
}
