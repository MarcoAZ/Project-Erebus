/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 3/7/15
* Edited: 3/11/15
* Final Project
*
* Purpose: definitions for rooms, player, and items
*******************************************************************************/
#include "objects.h"

/*
* Purpose: displays a messge in a nice box
* Parameters: takes a message as a string
* Return: nothing
*/
void displayTitle(string msg)
{
	cout << endl;
	for(unsigned int i = 0; i < msg.length()+2; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "*" << msg << "*" << endl;
	for(unsigned int i = 0; i < msg.length()+2; i++)
	{
		cout << "*";
	}
	cout << endl;
}

/*
* Purpose: lists the options available in the room, include leaving and interacting
*			with items. 
* Parameters: takes the player and the map
* Return: nothing
*/
void Room::listOptions(Player* p, vector<Room*> map)
{
	displayTitle("1. Available Directions");
	this->displayDoors();
	displayTitle("2. Available Items");
	this->listItems(this->getItems());
	displayTitle("3. Available Interactions");
	this->listActions(map, p);
	
	cout << endl;
}

/*
* Purpose: lists the doors in the room that are available to go through
* Parameters: takes none
* Return: nothing
*/
void Room::displayDoors()
{
	if(this->getN())
	{
		cout << "(1) " << (this->getN())->getName();
	}
	if(this->getE())
	{
		cout << "(2)" << (this->getE())->getName();
	}
	if(this->getS())
	{
		cout << "(3)" << (this->getS())->getName();
	}
	if(this->getW())
	{
		cout << "(4)" << (this->getW())->getName();
	}
}
/*
* Purpose: lists the items in the room that are available to interact with or returns
*			false if there is nothing to take
* Parameters: takes the list of items in the room
* Return: true if items to take or false if no items
*/
bool Room::listItems( vector<Item*>* items)
{	//account for NULL
	bool itemAvailable = false;
	
	//go through the vector
	for(unsigned int item = 0; item < items->size(); item++)
	{
		//print out names of items in room
		if(items->at(item) != NULL)
		{
			cout << "(" << item + 1 << ")" << items->at(item)->getName() << " ";
			itemAvailable = true; //there is at least one item to show
		}
	}
	
	if(!itemAvailable)
		cout << "There's nothing here to take..." ;
	return itemAvailable;
}
/*
* Purpose: checks if boss is in the room and shows/hides keycard
* Parameters: takes list of items in room
* Return: true if keycard can be taken or false if boss is still there
*/
bool Boss::listItems( vector<Item*>* items)
{
	//account for NULL
	bool itemAvailable = false;
	
	if(this->isDistracted())
	{	//go through the vector
		for(unsigned int item = 0; item < items->size(); item++)
		{
			//print out names of items in room
			if(items->at(item) != NULL)
			{
				cout << "(" << item + 1 << ")" << items->at(item)->getName() << " ";
				itemAvailable = true; //there is at least one item to show
			}
		}
	}
	
	if(!itemAvailable)
		cout << "I don't think he'd like me looking through his stuff..." ;
	return itemAvailable;
}
/*
* Purpose: lists interactions possible in the room
* Parameters: takes map
* Return: nothing
*/
void Room::listActions(vector<Room*> map, Player* p)
{
	cout << " There is nothing to do here" << endl;
}

//boss office possible actions
void Boss::listActions(vector<Room*> map, Player* p)
{
	if(this->isDistracted())
	{
		cout << " Search Boss' Email ";
	}
	//else if player put cupcakes in break room
	//using static_cast because the pointer is an abstract class pointer
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		cout << " Tell Boss about Cupcakes ";
	}
	else if (!this->isDistracted() && !static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		cout << " Say Hello ";
	}
}

//Programmer Analyst possible actions
void Cubicle1::listActions(vector<Room*> map, Player* p)
{
	if(this->isDistracted())
	{
		cout << " Use Computer ";
	}
	//else if player put cupcakes in break room
	//using static_cast because the pointer is an abstract class pointer
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		cout << " Tell her about Cupcakes ";
	}
	else if (!this->isDistracted() && !static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		cout << " Say Hello ";
	}
}

//user can leave cupcakes in the breakroom
void Breakroom::listActions(vector<Room*> map, Player* p)
{
	//if the player has cupcakes, then they can set them here
	bool hasCupcakes = p->inPocket("Cupcakes");
	if(hasCupcakes)
	{
		cout << "Leave cupcakes in breakroom for coworkers";
	}
	else
	{
		cout << "There's nothing interesting to see...";
	}
}

/*
* Purpose: allows user to choose interaction possible in the room
* Parameters: takes none
* Return: nothing
*/
void Room::interact(Room* room, vector<Room*> map, Player* p)
{
	cout << "There's nothing to do in this room!" << endl;
}

//boss' office: choose action
void Boss::interact(Room* room, vector<Room*> map, Player* p )
{
	if(this->isDistracted())
	{
		//search email
		cout << "Doing spy stuff!" << endl;
	}
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		this->distract(true);
	}
	else
	{
		//short conversation
		//TEMPORARY
		cout << "Hope everything is going well!" << endl;
	}
}

//programmer analyst interaction
void Cubicle1::interact(Room* room, vector<Room*> map, Player* p)
{
	if(this->isDistracted())
	{
		//copy files from computer
		cout << "Copying data!" << endl;
	}
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		this->distract(true);
	}
	else
	{
		//short conversation
		//TEMPORARY
		cout << "Everything ok?" << endl;
	}
}

//break room interaction
void Breakroom::interact(Room* room, vector<Room*> map, Player* p )
{
	//if the player has cupcakes, then they can set them here
	bool hasCupcakes = p->inPocket("Cupcakes");
	if(hasCupcakes)
	{
		//remove cupcakes from player's pocket
		p->removeItem("Cupcakes");
		//set breakroom to having cupcakes
		this->setCakes(hasCupcakes);
	}
	else
	{
		cout << "There's nothing interesting to see...";
	}
}

/*
* Purpose: gets a choice from the use for an item to pick up, then adds it to player's pocket
* Parameters: takes the current room
* Return: nothing
*/
void Player::chooseItem(Room* room)
{
	vector<Item*>* items = room->getItems();

	if(items->size() != 0)
	{
		if(room->listItems(items))
		{	cout << endl << "Grab item # ";
			int selection;
			while( !(cin >> selection) || selection < 1 || selection > (int)items->size() )
			{
				cout << "Your selection must be 1 - " << items->size() << endl;
			}
			//make sure this item is not NULL
			if(items->at(selection-1))
			{	//grab selected item if possible
				bool grabbed = this->grabItem(items->at(selection-1));
				//remove item as an option from the room
				if(grabbed)
					items->erase(items->begin()+(selection-1));
			}
		}
	}
	else
	{
		cout << "Nothing to grab here!" << endl;
	}
}
/*
* Purpose: if there is room in pocket, grabs an item
* Parameters: takes the item the player wants to grab
* Return: true if item grabbed
*/
bool Player::grabItem( Item* i )
{	
	vector<Item*>* pocket = this->getPocket();

	if((int)pocket->size() < this->getPocketSize())
	{
		pocket->push_back(i);
		cout << "You grab " << i->getName() << endl;
		return true;
	}
	else
		cout << "Can't hold anymore items!" << endl;
	return false;
}
/*
* Purpose: removes item from player's pockets
* Parameters: name of the item we're looking for
* Return: nothing
*/
void Player::removeItem(string name)
{	//go through your pockets
	vector<Item*>* pocket = this->getPocket();
	for(unsigned int i = 0; i < pocket->size(); i++)
	{
		if(pocket->at(i)->getName() == name)
		{	//did we find the item?
			//remove it
			pocket->erase(pocket->begin()+i);
		}
	}
}
/*
* Purpose: find out if player has the item we're looking for
* Parameters: name of the item we're looking for
* Return: true if item found
*/
bool Player::inPocket(string name)
{
	//go through your pockets
	vector<Item*>* pocket = this->getPocket();
	for(unsigned int i = 0; i < pocket->size(); i++)
	{
		if(pocket->at(i)->getName() == name)
		{	//did we find the item?
			return true;
		}
	}
	return false;
}
/*
* Purpose: Checks every requirement to see if mission was full success
* Parameters: takes none
* Return: true if all requirements met
*/
bool Player::allDone()
{
	//is player outside?
	if( this->getCurrentRoom()->getType() != OUT)
	{
		return false;
	}
	//email data?
	if( !(this->hasEmailData(this->getPocket())) )
	{
		return false;
	}
	//data samples?
	if( !(this->hasCodeData(this->getPocket())) )
	{
		return false;
	}
	//uploaded kill switch?
	if( !(this->uploadedUSB(this->getPocket())) )
	{
		return false;
	}
	
	//made it here? Mision was a success!
	return true;
}
/*
* Purpose: All three check the player's pocket, finds the usb, and checks if a certain
*		task was completed
*Parameters: takes a vector representing the player's pocket
* Return: true if requirement met
*/
bool Player::hasEmailData( vector<Item*>* pocket )
{
	return true;
}
bool Player::hasCodeData( vector<Item*>* pocket )
{
	return true;
}
bool Player::uploadedUSB( vector<Item*>* pocket )
{
	return true;
}

