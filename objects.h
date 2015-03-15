/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 3/7/15
* Edited: 3/13/15
* Final Project
*
* Purpose: declarations for rooms, player, and items
*******************************************************************************/
#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <cstddef> //NULL
#include <iostream>
#include <cstdlib> //exit()

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

enum type { MYDESK, DEVFLOOR, OFFICES, CW1, CW2, BOSS, BREAK, ELEVATOR, SERVER, LOBBY, OUT };

class Player;

//for some rooms, I did not have derived class. the base class calls these functions
//when it prints out the room description
void myDeskDescription(Player*);

//item abstract class
class Item
{
public:
	Item()
	{
		name = "";
	}
	
	Item(string n)
	{
		name = n;
	}
	
	string getName()
	{	return name;}

protected:
	string name;
};

//abstract room object
class Room
{
public:
	Room()
	{
		North = NULL;
		East = NULL;
		South = NULL;
		West = NULL;
	}//default constructor
	
	Room(type t)
	{
		typeOf = t;
		North = NULL;
		East = NULL;
		South = NULL;
		West = NULL;
	}
	
	virtual bool listItems( vector<Item*>* items);	//lists items in room or says no items
	void listDirections();					//list available directions
	void displayDoors();					//shows the available doors using previous getters
	void listOptions(Player*, vector<Room*>); 	//lists user's possible actions:
												//interact with item, object, or person
	virtual void listActions(vector<Room*>, Player*);//lists available interactions in room
	virtual void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	virtual void showDescription(Player*);	//updates the player with story elements from the room
	virtual ~Room();
	
	vector<Item*>* getItems()		//get reference to items
	{	return &roomItems;}
	
	void addItemToRoom( Item* i)	//add item to room when building room
	{	roomItems.push_back(i);}
	
	type getType()			//used to find what room the player is in
	{	return typeOf;}
	
	Room* getN()			//get linked rooms
	{	return North;}
	Room* getE()
	{	return East;}
	Room* getS()
	{	return South;}
	Room* getW()
	{	return West;}
	
	void setN(Room* n)		//set linked rooms
	{	North = n;}
	void setE(Room* e)
	{	East = e;}
	void setS(Room* s)
	{	South = s;}
	void setW(Room* w)
	{	West = w;}
	
	string getName()		//get the name of the room
	{	return name;}
	void setName(string n)	//set the name of the room
	{	name = n;}

protected:
	Room* North;	//links to other rooms
	Room* East;
	Room* South;
	Room* West;
	
	type typeOf;
	string name;
	
	vector<Item*> roomItems; //items available in the room
	
};

/*
* player object
*/
class Player
{
private:
	Room* currentRoom;
	vector<Item*> pocket; //item storage
	int pocketSize;
	bool abortMission; //user can abort at any time
public:
	Player()
	{
		pocketSize = 4;
		currentRoom = NULL;
		abortMission = false;
	};

	Player(Room* current)
	{
		pocketSize = 4;
		currentRoom = current;
		abortMission = false;
	};
	~Player();
	
	Room* getCurrentRoom()		//current room location and room changes
	{	return currentRoom;}
	
	void changeRoom(Room* r)
	{	currentRoom = r;}
	
	vector<Item*>* getPocket()	//get reference to pocket
	{	return &pocket;}
	
	int getPocketSize()
	{	return pocketSize;}
	
	bool abortStatus()		//checks mission status
	{	return abortMission;}
	
	void abortingMission(bool b)		//aborts the mission
	{	abortMission = b;}
	
	bool grabItem( Item* i );		//add item to pocket
	void chooseItem(Room* room);//choose an item from the room to pass to grabItem
	void removeItem( string );	//remove item from pocket
	bool inPocket( string );	//is specified item in pocket?
	Item* getUSB();				//gets pointer to the usb in player pocket
	
	bool hasEmailData();	//finds usb in player's pocket 
							//and determines if it has the email evidence
	bool hasCodeData();		//checks if code data is on usb
	bool uploadedUSB();		//checks if usb was used on server
	
	bool allDone();	//checks if all of the requirements for mission complete are met
};

/*
* Declarations for every room in the game
*/
//lobby
class Lobby : public Room
{
private:
	bool paperStatus;	//has the player already grabbed the newspaper?
public:
	Lobby() : Room(){};
	Lobby(type t) : Room(t){};
	
	bool listItems( vector<Item*>* items);	//can hide an item
	void showDescription(Player*);	//show story elements for the room
	
	void updatePaper(bool b)
	{	paperStatus = b;}
	bool grabbedPaper()
	{	return paperStatus;}
};
//employee break room
class Breakroom : public Room
{
private:
	bool cupcakes;
public:
	Breakroom() : Room(){};
	Breakroom(type t) : Room(t){};
	
	void listActions(vector<Room*>, Player*);	//lists what can be done in the room
	void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	void showDescription(Player*);	//show story elements for the room
	
	bool hasCakes()
	{	return cupcakes;}
	void setCakes(bool b)
	{	cupcakes = b;}
};

//server room
class Server : public Room
{
private:

public:
	Server() : Room(){};
	Server(type t) : Room(t){};
	
	void listActions(vector<Room*>, Player*);	//lists what can be done in the room
	void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	void showDescription(Player*);	//show story elements for the room

};

//supervisor office
class Boss : public Room
{
private:
	bool distracted; //has the player removed boss from the office
public:
	Boss() : Room(){};
	Boss(type t) : Room(t){};
	
	void listActions(vector<Room*>, Player*);	//lists what can be done in the room
	void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	bool listItems( vector<Item*>* items);	//lists items in room or says no items
	void showDescription(Player*);	//show story elements for the room
	
	bool isDistracted()
	{	return distracted;}
	
	void distract(bool b)
	{	distracted = b;}
};
//coworker #1 cubicle
class Cubicle1 : public Room
{
private:
	bool distracted; //has the player removed coworker from the cubicle
public:
	Cubicle1() : Room(){};
	Cubicle1(type t) : Room(t){};
	
	void listActions(vector<Room*>, Player*);	//lists what can be done in the room
	void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	void showDescription(Player*);	//show story elements for the room
	
	bool isDistracted()
	{	return distracted;}
	
	void distract(bool b)
	{	distracted = b;}
};

//coworker #2 cubicle
class Cubicle2 : public Room
{
private:
	bool distracted; //has the player removed coworker from the cubicle
public:
	Cubicle2() : Room(){};
	Cubicle2(type t) : Room(t){};
	
	void listActions(vector<Room*>, Player*);	//lists what can be done in the room
	void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	void showDescription(Player*);	//show story elements for the room
	
	bool isDistracted()
	{	return distracted;}
	
	void distract(bool b)
	{	distracted = b;}
};

//outside
class Outside : public Room
{
private:

public:
	Outside() : Room(){};
	Outside(type t) : Room(t){};
	
	void listActions(vector<Room*>, Player*);	//lists what can be done in the room
	void interact(Room*, vector<Room*>, Player*);//user can select what to do in the room
	void showDescription(Player*);	//show story elements for the room
};

/*
* End of room declarations
*/

/*
* Item declarations
*/
//cupcake
class Cupcakes : public Item
{
private:

public:
	Cupcakes() : Item(){};
	Cupcakes(string n) : Item(n){};
};

//USB drive
class USB : public Item
{
private:
	bool uploaded;		//was it uploaded to the server?
	bool data;			//has examples of private data?
	bool email;			//has emails between gov't and company
public:
	USB() : Item(){};
	USB(string n) : Item(n){};
	
	void uploading(bool b)	//set uploaded
	{	uploaded = b;}
	
	bool getUpload()		//get uploaded status
	{	return uploaded;}
	
	void copyData(bool b)	//set data
	{	data = b;}
	
	bool hasData()
	{	return data;}
	
	void copyEmails(bool b)	//set emails
	{	email = b;}
	
	bool hasEmails()
	{	return email;}
	
	
};

//keycard
class Keycard : public Item
{
private:
	
public:
	Keycard() : Item(){};
	Keycard(string n) : Item(n){};
};

/*
* End of item declarations
*/
#endif
