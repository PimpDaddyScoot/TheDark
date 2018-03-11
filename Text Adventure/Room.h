#ifndef ROOM_H
#define ROOM_H

#include "myString.h"
class Item;
#include "Item.h"

// Room class
//
// By Scott Purcival
// AIE - Introduction to C++ Assignment (First Year)

class Room
{
private:
	myString			roomDescription = "";
	myString			exits = "";
	static const int	MAX_ITEMS = 5;
	Item*				roomInventory[MAX_ITEMS];
	int					numItemsInRoom = 0;
	bool				isFinalExit = false;

public:
						Room();
						~Room();
	bool				IsFinalExit();
	void				IsFinalExit(bool setExit);
	void				Look(bool isTorchOn);
	Item				Get(char* itemName);
	bool				AddItem(Item* itemToDrop);
	void				SetExits(char * exits);
	char*				GetExits();
	void				SetDescription(char * newDescription);
	bool				IsRoomCreated();
	int					GetNumItems();
	char*				GetItemName(int index);
	Item*				GetItem(int index);
	void				RemoveItem(int index);
	bool				HasRoom();


	

};

#endif

