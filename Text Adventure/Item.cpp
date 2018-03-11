#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

Item::Item(char * newItemName, char * newItemDescription)
{
	SetName(newItemName);
	SetDescription(newItemDescription);
}

void Item::SetName(char * newItemName)
{
	itemName = newItemName;
}

char * Item::GetName()
{
	return itemName.GetValue();
}

void Item::SetDescription(char* newItemDescription)
{
	itemDescription = newItemDescription;
}

void Item::Use(Player * targetPlayer, Map * targetMap, char * args)
{
}

char * Item::GetDescription()
{
	return itemDescription.GetValue();
}

Food::Food()
{
}

Food::~Food()
{
}

void Food::Use(Player* targetPlayer, Map* targetMap, char* args)
{
}

Bread::Bread()
{
	SetName("Old Bread");
	SetDescription("Dusty old bread. Beats starving to death...");
}

Bread::~Bread()
{
}

void Bread::Use(Player * targetPlayer, Map * targetMap, char * args)
{
	targetPlayer->AddFood(ENERGY_TO_ADD);
	std::cout << "You eat the bread and gain " << ENERGY_TO_ADD << " energy.\n";
	destroyMe = true;
}

Mushroom::Mushroom()
{
	SetName("Mushroom");
	SetDescription("A small mushroom... looks edible?");
}

Mushroom::~Mushroom()
{
}

void Mushroom::Use(Player * targetPlayer, Map * targetMap, char * args)
{
	targetPlayer->AddFood(ENERGY_TO_ADD);
	std::cout << "You eat the mushroom and gain " << ENERGY_TO_ADD << " energy.\n";
	destroyMe = true;
}

Batteries::Batteries()
{
	SetName("Batteries");
	SetDescription("Some old batteries. Maybe they have some charge left?");
}

Batteries::~Batteries()
{
}

void Batteries::Use(Player* targetPlayer, Map* targetMap, char* args)
{
	int currentBatteryEnergy = targetPlayer->GetTorchEnergy();
	targetPlayer->SetTorchEnergy(batEnergyLeft);
	batEnergyLeft = currentBatteryEnergy;					// We have essentially swapped the batteries out from torch to inventory
	if (batEnergyLeft == 0)
		SetDescription("These Batteries are flat.");
	else
		SetDescription("Old Batteries, but there is still some go left in them.");
	std::cout << "You swap the batteries.\n";
}

Throwable::Throwable()
{
}

Throwable::~Throwable()
{
}

void Throwable::Use(Player* targetPlayer, Map* targetMap, char* args)
{
}

Stone::Stone()
{
	SetName("Stone");
	SetDescription("A small rock. Maybe I can USE it somehow?");
}

Stone::~Stone()
{
}

void Stone::Use(Player* targetPlayer, Map* targetMap, char* args)
{
	myString availableExits;
	bool stillLooking = true;
	int roomsFound = 0;
	Vector2D locationModifier(0, 0);
	myString directionToLook;

	switch (args[0])
	{
	case 0:	// NO ARGUMENT
		switch (rand() % 3)
		{
		case 0:
			std::cout << "You look at it and see nothing special. You throw it over your shoulder and it makes a sound as it hits the wall... Perhaps you could USE these with DIRECTION to find your way?\n";
			break;
		case 1:
			std::cout << "You throw it in disgust. *ting* It hits something in the dark. with a bit of DIRECTION you could USE this to reveal things in the dark...\n";
			break;
		case 2:
			std::cout << "A boring item... if only you could USE the ITEM. You need some sort of DIRECTION... No use throwing things blindly in the dark...\n";
			break;
		}
		return;
		break;
	case 110: // NORTH
		std::cout << "You throw it North. ";
		break;
	case 101: // EAST
		std::cout << "You throw it East. ";
		break;
	case 115: // SOUTH
		std::cout << "You throw it South. ";
		break;
	case 119: // WEST
		std::cout << "You throw it West. ";
		break;
	default:
		std::cout << "I have no idea what you are trying to do. Try something else maybe?\n";
		return;
		break;
	}

	// Look for rooms in direction.
	availableExits = args;
	availableExits = availableExits.UCase();
	availableExits = availableExits.Mid(0, 1);
	directionToLook = availableExits.Mid(0, 1);				// directionToLook is now equal to uppercase args[0]

	while (stillLooking)
	{
		availableExits = targetMap->AvailableExits(targetPlayer->Position + locationModifier);
		if (availableExits.Find(directionToLook.GetValue()) != -1)
		{
			roomsFound++;
			switch (directionToLook.GetChar(0))
			{
			case 78:	//n
				locationModifier.y--;
				break;
			case 69:	//e
				locationModifier.x++;
				break;
			case 83:	//s
				locationModifier.y++;
				break;
			case 87:	//w
				locationModifier.x--;
				break;
			};

			if (locationModifier.x < 0 || locationModifier.x == targetMap->mapSize.x || locationModifier.y < 0 || locationModifier.y == targetMap->mapSize.y)
				stillLooking = false;
		}
		else
			stillLooking = false;
	}

	std::cout << "The sound of it hitting the wall echoes back at you.\nAt your best guess, it travelled " << roomsFound << " rooms.\n";
	destroyMe = true;

}

Bone::Bone()
{
	SetName("Bone");
	SetDescription("An old bone. Part gnawed upon. Looks human...");
}

Bone::~Bone()
{
}

void Bone::Use(Player* targetPlayer, Map* targetMap, char* args)
{
	myString availableExits;
	bool stillLooking = true;
	int roomsFound = 0;
	Vector2D locationModifier(0, 0);
	myString directionToLook;

	switch (args[0])
	{
	case 0:	// NO ARGUMENT
		switch (rand() % 3)
		{
		case 0:
			std::cout << "You look at it and see nothing special. You throw it over your shoulder and it makes a sound as it hits the wall... Perhaps you could USE these with DIRECTION to find your way?\n";
			break;
		case 1:
			std::cout << "You throw it in disgust. *ting* It hits something in the dark. with a bit of DIRECTION you could USE this to reveal things in the dark...\n";
			break;
		case 2:
			std::cout << "A boring item... if only you could USE the ITEM. You need some sort of DIRECTION... No use throwing things blindly in the dark...\n";
			break;
		}
		return;
		break;
	case 110: // NORTH
		std::cout << "You throw it North. ";
		break;
	case 101: // EAST
		std::cout << "You throw it East. ";
		break;
	case 115: // SOUTH
		std::cout << "You throw it South. ";
		break;
	case 119: // WEST
		std::cout << "You throw it West. ";
		break;
	default:
		std::cout << "I have no idea what you are trying to do. Try something else maybe?\n";
		return;
		break;
	}

	// Look for rooms in direction.
	availableExits = args;
	availableExits = availableExits.UCase();
	availableExits = availableExits.Mid(0, 1);
	directionToLook = availableExits.Mid(0, 1);				// directionToLook is now equal to uppercase args[0]

	while (stillLooking)
	{
		availableExits = targetMap->AvailableExits(targetPlayer->Position + locationModifier);
		if (availableExits.Find(directionToLook.GetValue()) != -1)
		{
			roomsFound++;
			switch (directionToLook.GetChar(0))
			{
			case 78:	//n
				locationModifier.y--;
				break;
			case 69:	//e
				locationModifier.x++;
				break;
			case 83:	//s
				locationModifier.y++;
				break;
			case 87:	//w
				locationModifier.x--;
				break;
			};

			if (locationModifier.x < 0 || locationModifier.x == targetMap->mapSize.x || locationModifier.y < 0 || locationModifier.y == targetMap->mapSize.y)
				stillLooking = false;
		}
		else
			stillLooking = false;
	}

	std::cout << "The sound of it hitting the wall echoes back at you.\nAt your best guess, it travelled " << roomsFound << " rooms.\n";
	destroyMe = true;

}

DeadRat::DeadRat()
{
	SetName("Rat");
	SetDescription("A dead rat. Mind you, anything could be useful down here...");
}

DeadRat::~DeadRat()
{
}

void DeadRat::Use(Player* targetPlayer, Map* targetMap, char* args)
{
	myString availableExits;
	bool stillLooking = true;
	int roomsFound = 0;
	Vector2D locationModifier(0, 0);
	myString directionToLook;

	switch (args[0])
	{
	case 0:	// NO ARGUMENT
		switch (rand() % 3)
		{
		case 0:
			std::cout << "You look at it and see nothing special. You throw it over your shoulder and it makes a sound as it hits the wall... Perhaps you could USE these with DIRECTION to find your way?\n";
			break;
		case 1:
			std::cout << "You throw it in disgust. *ting* It hits something in the dark. with a bit of DIRECTION you could USE this to reveal things in the dark...\n";
			break;
		case 2:
			std::cout << "A boring item... if only you could USE the ITEM. You need some sort of DIRECTION... No use throwing things blindly in the dark...\n";
			break;
		}
		return;
		break;
	case 110: // NORTH
		std::cout << "You throw it North. ";
		break;
	case 101: // EAST
		std::cout << "You throw it East. ";
		break;
	case 115: // SOUTH
		std::cout << "You throw it South. ";
		break;
	case 119: // WEST
		std::cout << "You throw it West. ";
		break;
	default:
		std::cout << "I have no idea what you are trying to do. Try something else maybe?\n";
		return;
		break;
	}

	// Look for rooms in direction.
	availableExits = args;
	availableExits = availableExits.UCase();
	availableExits = availableExits.Mid(0, 1);
	directionToLook = availableExits.Mid(0, 1);				// directionToLook is now equal to uppercase args[0]

	while (stillLooking)
	{
		availableExits = targetMap->AvailableExits(targetPlayer->Position + locationModifier);
		if (availableExits.Find(directionToLook.GetValue()) != -1)
		{
			roomsFound++;
			switch (directionToLook.GetChar(0))
			{
			case 78:	//n
				locationModifier.y--;
				break;
			case 69:	//e
				locationModifier.x++;
				break;
			case 83:	//s
				locationModifier.y++;
				break;
			case 87:	//w
				locationModifier.x--;
				break;
			};

			if (locationModifier.x < 0 || locationModifier.x == targetMap->mapSize.x || locationModifier.y < 0 || locationModifier.y == targetMap->mapSize.y)
				stillLooking = false;
		}
		else
			stillLooking = false;
	}

	std::cout << "The sound of it hitting the wall echoes back at you.\nAt your best guess, it travelled " << roomsFound << " rooms.\n";
	destroyMe = true;

}

Torch::Torch()
{
	SetName("Torch");
	SetDescription("A torch, might be useful when LOOKing about...");
}

Torch::~Torch()
{
}

void Torch::Use(Player * targetPlayer, Map * targetMap, char * args)
{
	Item* itemPointer = targetPlayer->GetItemPointer("torch");
	if (itemPointer != nullptr)
	{
		targetPlayer->isTorchOn = !(targetPlayer->isTorchOn);
		if (targetPlayer->GetTorchEnergy() == 0)
		{
			targetPlayer->isTorchOn = false;
			std::cout << "The torch batteries appear to be flat.\n";
		}
		if (targetPlayer->isTorchOn)
			std::cout << "Torch is now ON.\n";
		else
			std::cout << "Torch is now OFF.\n";
	}
	else
	{
		std::cout << "You should probably pick that one up first.\n";
	}
}


