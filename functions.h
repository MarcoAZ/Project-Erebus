/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 3/10/15
* Edited: 3/14/15
* Final Project
*
* Purpose: provides declarations for the functions that run the main function
*******************************************************************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "objects.h"
#include <fstream>
#include <cstdlib> //exit(int)
#include <limits> //numeric_limits

using std::cin;
using std::ifstream;
using std::ios;
using std::streamsize;
using std::max;
using std::numeric_limits;

//types of possible actions. Starts at 1
enum action { LEAVE = 1, GRAB, INTERACT };

//types of possible rooms. Starts at 1
enum direction { NORTH = 1, EAST, SOUTH, WEST };

//allows user to see answers to the game
void showGoal();

//saves rooms in vector
void loadRooms( vector<Room*>& map );

//gets room names from a file and reads them into the proper room
void nameRooms(vector<Room*>& map);

//links rooms together
void linkRooms( vector<Room*>& map );

//creates items and puts them in appropriate room
void loadItems(vector<Room*>& map );

//runs the game loop
void play( Player* player, vector<Room*> map );

//get input from user on next choice
int getAction();

//gets user input of next room and puts player in that room
Room* getDirection(Player* player, Room* room);

//follow through on player's choice
void performAction(int act, Player* player, Room* room, vector<Room*> map );

//free rooms and items in rooms
void deleteRooms(vector<Room*>& map);

#endif
