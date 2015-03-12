/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 3/10/15
* Edited: 3/11/15
* Final Project
*
* Purpose: provides definitions for the functions that run the main function
*******************************************************************************/
#include "objects.h"
#include "functions.h"
//text file with room names
const char* NAME = "names.txt";

/*
*	Purpose: runs the entire game loop
*	Parameters: Takes the player object and the map of the offices
*	Returns: nothing
*/
void play( Player* player, vector<Room*> map )
{
	
	//runs while the player has not met all three requirements or player hasn't aborted mission
	while( !(player->allDone()) && !player->abortStatus() )
	{
		Room* currentRoom = player->getCurrentRoom();
		
		//output room description or story
		cout << endl << "Current Room is " << currentRoom->getName() << endl;
		
		//list all player options
		currentRoom->listOptions(player, map);
		
		//get what user wants to do
		//of that action, follow through and get direction/item/interaction
		performAction(getAction(), player, currentRoom, map);
	}
	cout << "leaving!" << endl;
}

/*
*	Purpose: stores created rooms in the office vector. 
*/
void loadRooms( vector<Room*>& map )
{
	//create cubicle
	Room* cubicle = new MyCubicle(MYDESK);
	map.push_back( cubicle );
	
	//create development floor
	Room* devFloor = new Hallway(DEVFLOOR);
	map.push_back(devFloor);
	
	//create cubicle/offices transition room
	Room* offices = new Offices(OFFICES);
	map.push_back(offices);
	
	//create coworker 1's office
	Room* cw1 = new Cubicle1(CW1);
	map.push_back(cw1);
	
	//create coworker 2's office
	Room* cw2 = new Cubicle2(CW2);
	map.push_back(cw2);
	
	//create boss' office
	Room* boss = new Boss(BOSS);
	map.push_back(boss);
	
	//create breakroom
	Room* breakroom = new Breakroom(BREAK);
	map.push_back(breakroom);
	
	//create elevator
	Room* elevator = new Elevator(ELEVATOR);
	map.push_back(elevator);
	
	//create server floor
	Room* server = new Server(SERVER);
	map.push_back(server);
	
	//create lobby
	Room* lobby = new Lobby(LOBBY);
	map.push_back(lobby);
	
	//create outside
	Room* outside = new Outside(OUT);
	map.push_back(outside)	;
}
/*
*	Purpose: links rooms together
*	Parameters: Takes the map of the offices
*	Returns: nothing
*/
void linkRooms(vector<Room*>& map)
{	//desk
	map[MYDESK]->setN(map[DEVFLOOR]);
	//end desk
	//development floor hallway
	map[DEVFLOOR]->setS(map[MYDESK]);
	map[DEVFLOOR]->setN(map[OFFICES]);
	map[DEVFLOOR]->setE(map[ELEVATOR]);
	map[DEVFLOOR]->setW(map[BREAK]);
	//end development floor
	//breakroom
	map[BREAK]->setE(map[DEVFLOOR]);
	//end breakroom
	//cubicle transition
	map[OFFICES]->setE(map[CW2]);
	map[OFFICES]->setW(map[CW1]);
	map[OFFICES]->setN(map[BOSS]);
	map[OFFICES]->setS(map[DEVFLOOR]);
	//end cubicle transition
	//cubicles lead back to transition room
	map[CW2]->setW(map[OFFICES]);
	map[CW1]->setE(map[OFFICES]);
	map[BOSS]->setS(map[OFFICES]);
	//end cubicle loop back to transition
	//elevator
	map[ELEVATOR]->setW(map[DEVFLOOR]);
	map[ELEVATOR]->setN(map[SERVER]);
	map[ELEVATOR]->setS(map[LOBBY]);
	//end elevator
	//server
	map[SERVER]->setS(map[ELEVATOR]);
	//end server
	//lobby
	map[LOBBY]->setN(map[ELEVATOR]);
	map[LOBBY]->setS(map[OUT]);
	//end lobby
	//outside
	map[OUT]->setN(map[LOBBY]);
}
/*
*	Purpose: gets the names of each room form a file
*	Parameters: the map of room pointers
*	Returns: nothing
*/
void nameRooms(vector<Room*>& map)
{
	ifstream names(NAME, ios::in);
	if(!names)
	{
		cout << "Could not open " << NAME << endl;
		exit(-1);
	}
	
	string buffer;	//stores name from file
	int room = 0; 	//iterator
	while( getline(names, buffer) && room < OUT+1)
	{
		map[room]->setName(buffer);
		room++;
		
		if(names.fail() )
		{
			cout << "An error occured with " << NAME << endl;
			exit(-1);
		}
	}
	
	//close file
	names.close();
	
}
/*
*	Purpose: user was presented with three different actions in the room. This function
*			gets which of those three the user would like to follow up on
*	Parameters: none
*	Returns: returns an action(int)
*/
int getAction()
{
	cout << "Perform action # ";
	int selection;
	while( !(cin >> selection) || selection > INTERACT || selection < LEAVE )
	{
		cout << "Your selection must be 1 - 3: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	return selection;
}
/*
*	Purpose: allows the user to choose next room, or pick up item or interact with 
*			something in the room
*	Parameters: the action, the current room, the map, and the player
*	Returns: nothing
*/
void performAction(int act, Player* player, Room* room, vector<Room*> map )
{
	action choice = (action)act;
	if(choice == LEAVE)
		player->changeRoom( getDirection(player, room));
	else if(choice == GRAB)
		player->chooseItem(room);
	else if(choice == INTERACT)
		room->interact(room, map, player);
}
/*
*	Purpose: allows the user to choose next room and puts him there
*	Parameters: the current room and the player
*	Returns: returns a point to a room
*/
Room* getDirection(Player* player, Room* room)
{
	room->displayDoors();
	cout << endl << "Go to room # ";
	int selection;
	while( !(cin >> selection) || selection < NORTH || selection > WEST )
	{
		cout << "Your selection must be 1 -4: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	if(selection == NORTH && room->getN())
		return room->getN();
	else if( selection == EAST && room->getE())
		return room->getE();
	else if( selection == SOUTH && room->getS())
		return room->getS();
	else if( selection == WEST && room->getW())
		return room->getW();
		
	//if control reaches here, a pointer to null must have been chosen
	cout << "You cannot go that way!" << endl;
	return getDirection(player, room);
	
}
/*
*	Purpose: creates items and then loads them into the appropriate room
*	Parameters: the vector of room pointers
*	Returns: nothing
*/
void loadItems(vector<Room*>& map )
{
	//load MYDESK items
	Item* photo = new Photo("Photo");
	map[MYDESK]->addItemToRoom(photo);
	//finished MYDESK items
	//lobby Items
	Item* paper = new Newspaper("Newspaper");
	Item* usb = new USB("USB Drive");
	Item* cakes = new Cupcakes("Cupcakes");
	map[LOBBY]->addItemToRoom(paper);
	map[LOBBY]->addItemToRoom(usb);
	map[LOBBY]->addItemToRoom(cakes);
	//end lobby items
	//boss office
	Item* key = new Keycard("Keycard");
	map[BOSS]->addItemToRoom(key);
	//end boss office
}



