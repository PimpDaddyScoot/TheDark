#include "Room.h"

Room::Room()
{
	//roomInventory = new Item[MAX_ITEMS];
}

Room::~Room()
{
	for (int i = 0; i < numItemsInRoom; i++)
	{
		if(roomInventory[i] != nullptr)
			delete roomInventory[i];
	}
}

bool Room::IsFinalExit()
{
	return isFinalExit;
}

void Room::IsFinalExit(bool setExit)
{
	isFinalExit = setExit;
}

void Room::Look(bool isTorchOn)
{
	if (isTorchOn)
	{
		std::cout << roomDescription.GetValue() << "\n";
		std::cout << "You see " << numItemsInRoom << " items in the room.\n";
		if (numItemsInRoom > 0)
		{
			std::cout << "They are: ";
			for (int i = 0; i < numItemsInRoom; i++)
			{
				std::cout << roomInventory[i]->GetName() << "\t";
			}
			std::cout << "\n";
		}
		std::cout << "The exits are: " << exits.GetValue() << "\n";
	}
	else
	{
		std::cout << roomDescription.GetValue() << "\n";
		std::cout << "It is too dark to see anything more.\n";
	}
}

bool Room::AddItem(Item* itemToAdd)
{
	if (numItemsInRoom < MAX_ITEMS)
	{
		roomInventory[numItemsInRoom] = itemToAdd;
		++numItemsInRoom;
		return true;
	}
	else
		return false;
}

void Room::SetExits(char * newexits)
{
	this->exits = newexits;
}

char * Room::GetExits()
{
	return exits.GetValue();
}

void Room::SetDescription(char * newDescription)
{
	roomDescription = newDescription;
}

bool Room::IsRoomCreated()
{
	if (roomDescription == "")
		return false;
	else
		return true;
}

int Room::GetNumItems()
{
	return numItemsInRoom;
}

char * Room::GetItemName(int index)
{
	return roomInventory[index]->GetName();
}

Item * Room::GetItem(int index)
{
	return roomInventory[index];
}

void Room::RemoveItem(int index)
{
	roomInventory[index] = roomInventory[numItemsInRoom - 1];
	numItemsInRoom--;
	roomInventory[numItemsInRoom] = nullptr;
}

bool Room::HasRoom()
{
	if (numItemsInRoom < MAX_ITEMS)
		return true;
	else
		return false;
}
