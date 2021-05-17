#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

/*This file is all about the game world.  You will modify this to add
    constants and function prototypes.  Modify gooseGamePlay.cpp to
	actually add functionality.
*/

/*
    Declare constants to indicate various game world features in the board
    array.  Modify them to fit what you would like to do in the game.  You can
    change the type if you choose to store your game board as something other
    than intengers.
*/	
// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int SPEED = 3;
const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 25;

/*
    A few examples of characters both for actors and for the game board
    itself are shown.
*/	
//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%'); //% sign, a special character used in the ancient
const int SPEED_CHAR = int('S');
																					// game "Rogue"

/*
    Game play function prototypes are given below.
*/

/*
	Draw the elements of the game board (map, walls, safe zone)
*/
void drawBoard(int const gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT]);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool captured(Actor const & player, Actor const & monster);

/*
	check if the player has reached the safe zone
*/
bool won(Actor const & player, int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT]);

/*
	Determine which direction the goose should move. The function sees whether
	the goose is farther away in the horizontal or vertical direction, then
	determines whether it should move left/right or up/down.
*/
int gooseDirection(Actor const & player, Actor const & monster);

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/
void movePlayer(int key, Actor & player, 
	int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT]);

/*
	This function generates a pseudorandom number. It is used to randomize
	the starting locations of the player and goose.
*/
int randomNumber(int maxValue);

/*
	This function uses the x and y coordinates of the player to check if
	they are in a safe zone.
*/
bool checkWin(int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT],
	int xCoord, int yCoord);

/*
	Checks if player is in the speed boost('S')
	If true, changes player speed from 1 to 2
*/
void changeSpeed(Actor & player, int gameBoard[CONSOLE_WIDTH][CONSOLE_HEIGHT],
	int newSpeed, int xMove, int yMove);

#endif
