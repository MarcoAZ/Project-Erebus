/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 3/7/15
* Edited: 3/10/15
* Final Project
*
* Purpose: the engine for the text adventure
*******************************************************************************/
#include "functions.h"
#include "objects.h"

int main()
{
	//introduce the game
	
	//gave tester ability to see the goal for the game
	
	//make rooms
	vector<Room*> HQ;
	loadRooms(HQ);
	
	//link rooms
	linkRooms(HQ);
	
	//give rooms their names
	nameRooms(HQ);
	
	//add items to rooms
	loadItems(HQ);
		
	//create player and start player in office
	Player* player = new Player( HQ[MYDESK] );
	
	//play game while user has not met finish requirements
	play(player, HQ);
	
	//deallocate items
	
	//deallocate rooms
	
	//deallocate player
	delete player;
	
	//exit
	return 0;
}
