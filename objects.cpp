/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 3/7/15
* Edited: 3/14/15
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

Room::~Room()
{
	vector<Item*>* roomItems = this->getItems();
	for(unsigned int j = 0; j < roomItems->size(); j++)
	{
		delete roomItems->at(j);
	}
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
		cout << "(1)" << (this->getN())->getName() << " ";
	}
	if(this->getE())
	{
		cout << "(2)" << (this->getE())->getName() << " ";
	}
	if(this->getS())
	{
		cout << "(3)" << (this->getS())->getName() << " ";
	}
	if(this->getW())
	{
		cout << "(4)" << (this->getW())->getName() << " ";
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
		cout << "I don't think he'd like me looking through his stuff..." << endl;
	return itemAvailable;
}
/*
* Purpose: checks if the player has the newspaper already and shows/hides USB
* Parameters: takes list of items in room
* Return: true if items can be taken or false if no items in room
*/
bool Lobby::listItems( vector<Item*>* items)
{	//account for NULL
	bool itemAvailable = false;
	
	//go through the vector
	for(unsigned int i = 0; i < items->size(); i++)
	{
		Item* item = items->at(i);
		//print out names of items in room
		if(item != NULL)
		{
			//do not print out the USB if the player never grabbed the paper
			if( item->getName() == "USB Drive" && !this->grabbedPaper())
				continue;
			cout << "(" << i + 1 << ")" << item->getName() << " ";
			itemAvailable = true; //there is at least one item to show
		}
	}
	
	if(!itemAvailable)
		cout << "There's nothing here to take..." ;
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
//senior developer's possible actions
void Cubicle2::listActions(vector<Room*> map, Player* p)
{
	if(this->isDistracted())
	{
		cout << " Use Computer ";
	}
	//else if player put cupcakes in break room
	//using static_cast because the pointer is an abstract class pointer
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		cout << " Tell him about Cupcakes ";
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
//server options
void Server::listActions(vector<Room*> map, Player* p)
{
	bool hasCard = p->inPocket("Keycard");
	if(hasCard)
	{
		cout << "Use the server";
	}
	else
	{
		cout << "Try the door";
	}
}
//outside options
void Outside::listActions(vector<Room*> map, Player* p)
{
	cout << "Walk away and abandon the mission";
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
		if(!p->inPocket("USB Drive"))
			cout << "I need someplace to save this evidence!" << endl;
		else
		{//search email
			cout << "Looks like there's some emails between him and the NSA. I'll copy these..." << endl;
			Item* usb = p->getUSB();
			static_cast<USB*>(usb)->copyEmails(true);
		}
	}
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		this->distract(true);
		cout << "\"I left some cupcakes in the breakroom!\"" << endl;
	}
	else
	{
		//short conversation
		cout << "\"Hope everything is going well!\"" << endl;
	}
}

//programmer analyst interaction
void Cubicle1::interact(Room* room, vector<Room*> map, Player* p)
{
	if(this->isDistracted())
	{
		if(!p->inPocket("USB Drive"))
			cout << "I need someplace to save this evidence!" << endl;
		else
		{	//copy files from computer
			cout << "Looks like she has access to the database of private user data. I'll make copies of this." << endl;
			Item* usb = p->getUSB();
			static_cast<USB*>(usb)->copyData(true);
		}
	}
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		this->distract(true);
		cout << "\"I left some cupcakes in the breakroom!\"" << endl;
	}
	else
	{
		//short conversation
		cout << "\"Everything ok?\"" << endl;
	}
}
//senior developer's interaction options
void Cubicle2::interact(Room* room, vector<Room*> map, Player* p)
{
	if(this->isDistracted())
	{
		if(!p->inPocket("USB Drive"))
			cout << "I need someplace to save this evidence!" << endl;
		else
		{//copy files from computer
			cout << "Looks like he has access to the database of private user data. I'll make copies of this." << endl;
			Item* usb = p->getUSB();
			static_cast<USB*>(usb)->copyData(true);
		}
	}
	else if(!this->isDistracted() && static_cast<Breakroom*>(map[BREAK])->hasCakes())
	{
		this->distract(true);
		cout << "\"I left some cupcakes in the breakroom!\"" << endl;
	}
	else
	{
		//short conversation
		cout << "\"Everything ok?\"" << endl;
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
		cout << "You leave cupcakes for your coworkers. How nice of you!" << endl;
	}
	else
	{
		cout << "There's nothing interesting to see..." << endl;
	}
}
//server interactions
void Server::interact(Room* room, vector<Room*> map, Player* p )
{
	bool hasCard = p->inPocket("Keycard");
	if(hasCard)
	{
		bool hasUSB = p->inPocket("USB Drive");
		if(hasUSB)
		{
			cout << "Uploaded the killswitch to the server!" << endl;
			//set the usb to show that the USB has uploaded the killswitch
			Item* usb = p->getUSB();
			static_cast<USB*>(usb)->uploading(true);
		}
		else
		{
			cout << "I need the killswitch program first!" << endl;
		}
	}
	else
	{
		cout << "The door is locked and you need a key card to get in" << endl;
	}
}
//outside interaction
void Outside::interact(Room*, vector<Room*>, Player* p)
{
	cout << "You decide to walk away with the mission incomplete..." << endl;
	p->abortingMission(true);
}
/*
* Purpose: gives hints on what to do next. tells the story. For rooms of class room,
*		it will have to find what type of room it is and then call another function
* Parameters: pointer to player
* Return: nothing
*/
void Room::showDescription(Player* p)
{
	int roomType = this->getType();
	if(roomType == MYDESK)
		myDeskDescription(p);
	else if(roomType == DEVFLOOR)
		cout << "This entire floor is dedicated to developing Ingen System's software." << endl;
	else if(roomType == OFFICES)
		cout << "This is were the main developers of Project Erebus work." << endl;
	else if(roomType == ELEVATOR)
		cout << "Soft music plays through the speakers. Now, to what floor do I want to go?" << endl;
}
//MYDESK description
void myDeskDescription(Player* p)
{
	if(p->inPocket("USB Drive"))
		cout << "I think I'll just calm my nerves at my desk for a bit." << endl;
	else if(p->inPocket("Newspaper"))
		cout << "I can't leave that USB lying around for someone to find!" << endl;
	else
	{
		cout << "There's a HERMES agent waiting for me in the lobby."<< endl;
		cout << "I better head there first." << endl;
	}
}
//cw1 room description
void Cubicle1::showDescription(Player* p)
{	
	if(!this->isDistracted())
		cout << "I know she has access to the user data collected by Erebus but I can't use her computer while she's here." << endl;
	else
		cout << "Her computer should have some data from Project Erebus that HERMES could use." << endl;
}
//cw2 room description
void Cubicle2::showDescription(Player* p)
{
	if(!this->isDistracted())
		cout << "I know he has access to the user data collected by Erebus but I can't use his computer while he's here." << endl;
	else
		cout << "I should look into his files to see if there's user data that could be used as evidence." << endl;
}
//boss description
void Boss::showDescription(Player* p)
{
	if(!this->isDistracted())
	{	cout << "I won't be able to get into the server room without his keycard." << endl;
		cout << "His email should also have proof that the government is using this software to spy on its citizens." << endl;
		cout << "I just need to get him away from his office.." << endl;
	}
	else if (!p->inPocket("Keycard"))
		cout << "I need both the keycard to get into the server and some evidence from his computer." << endl;
	else
		cout << "I don't think I need anything else from this room." << endl;
}
//break room description
void Breakroom::showDescription(Player* p)
{
	if(this->hasCakes())
		cout << "The cupcakes I left are still here." << endl;
	else
		cout << "The breakroom is empty. If only I could get my coworkers in here long enough for me to use their computers." << endl;
}
//server description
void Server::showDescription(Player* p)
{
	if(p->inPocket("USB Drive") && p->uploadedUSB())
		cout << "The killswitch has been uploaded. I should finish up and get out of the building!" << endl;
	else if(p->inPocket("Keycard"))
		cout << "I'm in the server room now. It's time to upload the killswitch and end this progam." << endl;
	else
		cout << "The server is through this door. I don't have the keycard to get in though. Only my supervisor has that." << endl;
}
//lobby description
void Lobby::showDescription(Player* p)
{
	if(!p->inPocket("Newspaper"))
	{
		cout << "The HERMES agent should be around here. There he is!" << endl;
		cout << "He's sitting at a table reading a newspaper by the cafe." << endl; 
		cout << "He's seen me. He's set down the paper and walked out the door." << endl;
		cout << "There must be something about the paper that's meant for me." << endl;
		if(!p->inPocket("Cupcakes"))
			cout << "Maybe I'll grab some cupcakes while I'm here, too..." << endl;
	}
	else if(!p->inPocket("USB Drive"))
		cout << "I better grab the USB drive before someone else sees it!" << endl;
	else
		cout << "The lobby, again. I could always leave right now..." << endl;
}
//outside description
void Outside::showDescription(Player* p)
{
	cout << "Should I just leave with what I have? Will it be enough to expose the truth?" << endl;
}
/*
* Purpose: gets a choice from the use for an item to pick up, then adds it to player's pocket
* Parameters: takes the current room
* Return: nothing
*/
void Player::chooseItem(Room* room)
{
	vector<Item*>* items = room->getItems();
	int itemsSize = (int)items->size();
	if(itemsSize != 0)
	{
		if(room->listItems(items))
		{	cout << endl << "Grab item # ";
			int selection;
			//do not allow player to choose the usb in the lobby if they do not have
			//the newspaper. This does not look very good but it gives the proper
			//restrictions to selection while the usb is hidden.
			if(room->getType() == LOBBY && !this->inPocket("Newspaper") && !this->inPocket("Cupcakes"))
			{
				itemsSize--;
			}
			else if(room->getType() == LOBBY && !this->inPocket("Newspaper") && this->inPocket("Cupcakes"))
			{
				itemsSize--;
			}
			
			while( !(cin >> selection) || selection < 1 || selection > itemsSize )
			{
				cout << "Your selection must be 1 - " << itemsSize << endl;
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
* Purpose: if there is space in pocket, grabs an item. Adding a feature: grabbing 
*		the newspaper also adds the USB hidden inside!
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
		//if a newspaper was grabbed, it comes with the hidden USB drive
		if(i->getName() == "Newspaper")
		{
			cout << "A USB drive fell out of the newspaper!" << endl;
			//only way to get access to paper is by player's current room
			Room* lobby = this->getCurrentRoom();
			static_cast<Lobby*>(lobby)->updatePaper(true);
		}
		return true;
	}
	else
		cout << "Can't pick up" << i->getName() <<"! No more room!" << endl;
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
* Purpose: get a pointer to the usb drive in the player's pocket
* Parameters: none
* Return: pointer to the usb drive
*/
Item* Player::getUSB()
{	//go through your pockets
	vector<Item*>* pocket = this->getPocket();
	for(unsigned int i = 0; i < pocket->size(); i++)
	{
		if(pocket->at(i)->getName() == "USB Drive")
		{	//did we find the item?
			return pocket->at(i);
		}
	}
	//control should not reach here!
	cout << "ERROR! USB was not in player's pocket!" << endl;
	exit(-2);
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
	if( !(this->hasEmailData()) )
	{
		return false;
	}
	//data samples?
	if( !(this->hasCodeData()) )
	{
		return false;
	}
	//uploaded kill switch?
	if( !(this->uploadedUSB()) )
	{
		return false;
	}
	
	//made it here? Mision was a success!
	return true;
}
/*
* Purpose: All three check the player's pocket, finds the usb, and checks if a certain
*		task was completed
*Parameters: nothing
* Return: true if requirement met
*/
bool Player::hasEmailData()
{	//go through your pockets
	vector<Item*>* pocket = this->getPocket();
	for(unsigned int i = 0; i < pocket->size(); i++)
	{
		if(pocket->at(i)->getName() == "USB Drive")
		{	//did we find the item? If so does it have the data we need?
			if( static_cast<USB*>(pocket->at(i))->hasEmails() )
				return true;
			//we found the usb, no need to keep looking
			return false;
		}
	}
	return false;
}
bool Player::hasCodeData()
{	//go through your pockets
	vector<Item*>* pocket = this->getPocket();
	for(unsigned int i = 0; i < pocket->size(); i++)
	{
		if(pocket->at(i)->getName() == "USB Drive")
		{	//did we find the item? If so does it have the data we need?
			if( static_cast<USB*>(pocket->at(i))->hasData() )
				return true;
			//we found the usb, no need to keep looking
			return false;
		}
	}
	return false;
}
bool Player::uploadedUSB()
{	//go through your pockets
	vector<Item*>* pocket = this->getPocket();
	for(unsigned int i = 0; i < pocket->size(); i++)
	{
		if(pocket->at(i)->getName() == "USB Drive")
		{	//did we find the item? If so does it have the data we need?
			if( static_cast<USB*>(pocket->at(i))->getUpload() )
				return true;
			//we found the usb, no need to keep looking
			return false;
		}
	}
	return false;
}
/*
* Purpose: player class destrucor. Deletes any items in player pocket
*Parameters: nothing
* Return: nothing
*/
Player::~Player()
{
	vector<Item*>* items = this->getPocket();
	int pocketSize = (int)items->size();
	for(int i = 0; i < pocketSize; i++)
	{
		delete items->at(i);
	}
}
