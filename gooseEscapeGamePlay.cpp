#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"
#include <ctime>

extern Console out;
	
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/

/*
	This function draws the game board
	(walls, safe zone, empty map)
*/
void drawBoard(int const gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT])
{
	for (int index1 = 0; index1 < CONSOLE_WIDTH; index1++)
	{
		for (int index2 = 0; index2 < CONSOLE_HEIGHT; index2++)
		{
			if (gameBoard[index1][index2] == SHALL_NOT_PASS)
				terminal_put(index1, index2, WALL_CHAR);
			else if (gameBoard[index1][index2] == WINNER)
				terminal_put(index1, index2, WIN_CHAR);
			else if (gameBoard[index1][index2] == SPEED)
				terminal_put(index1, index2, SPEED_CHAR);
		}
	}	
	terminal_refresh();
}

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool captured(Actor const & player, Actor const & monster)
{
   return (player.get_x() == monster.get_x() 
      && player.get_y() == monster.get_y());
}

/*
	check if the player has reached the safe zone
*/
bool won(Actor const & player, int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT])
{
	return (WINNER == gameBoard[player.get_x()][player.get_y()]);
}

/*
	Determine which direction the goose should move. The function sees whether
	the goose is farther away in the horizontal or vertical direction, then
	determines whether it should move left/right or up/down.
*/
int gooseDirection(Actor const & player, Actor const & monster)
{
	int xDiff = 0, yDiff = 0;
	xDiff = player.get_x() - monster.get_x();
	yDiff = player.get_y() - monster.get_y();
	if (fabs(xDiff) > fabs(yDiff))
	{
		if (xDiff < 0)
			return TK_LEFT;
		else
			return TK_RIGHT;
	}
	else if (fabs(yDiff) >= fabs(xDiff) && (xDiff != 0 && yDiff != 0))
	{
		if (yDiff < 0)
			return TK_UP;
		else
			return TK_DOWN;
	}
}

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/
void movePlayer(int key, Actor & player,
	int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT])
{
      int yMove = 0, xMove = 0;
      if (key == TK_UP)
         yMove = -1;
      else if (key == TK_DOWN)
         yMove = 1;
      else if (key == TK_LEFT)
         xMove = -1;
      else if (key == TK_RIGHT)
         xMove = 1;
        
      xMove *= player.getSpeed();
      yMove *= player.getSpeed();
      // change these moves according to the speed  
        
		changeSpeed(player, gameBoard, 2, xMove, yMove);
        
      if (player.can_move(xMove, yMove) 
      	&& gameBoard[player.get_x() + xMove][player.get_y() + yMove] 
			!= SHALL_NOT_PASS)
		{
			// make sure goose does not go to the safe zone
			if(gameBoard[player.get_x() + xMove][player.get_y() + yMove] 
			== WINNER && player.get_char() != MONSTER_CHAR)
				player.update_location(xMove, yMove);
			else if(gameBoard[player.get_x() + xMove][player.get_y() + yMove] 
			!= WINNER)
				// goose and player can move
				player.update_location(xMove, yMove);
		}
    
}

/*
	This function generates a pseudorandom number. It is used to randomize
	the starting locations of the player and goose.
*/
int randomNumber(int maxValue)
{
	int num = rand() % (maxValue); 
	return ++num;
}

/*
	This function uses the x and y coordinates of the player to check if
	they are in a safe zone.
*/
bool checkWin(int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT],
	int xCoord, int yCoord)
{
	if (gameBoard[xCoord][yCoord] == WINNER)
		return true;
	else
		return false;
}

/*
	Checks if player is in the speed boost('S')
	If true, changes player speed from 1 to 2
*/
void changeSpeed(Actor & player, int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT],
	int newSpeed, int xMove, int yMove)
{
	if(gameBoard[player.get_x() + xMove][player.get_y() + yMove] == SPEED)
	{
		player.change_speed(newSpeed);
		gameBoard[player.get_x() + xMove][player.get_y() + yMove] = 0;
	}
}

