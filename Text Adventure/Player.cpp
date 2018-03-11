#include "Player.h"

void Player::Initialise()
{
	isAlive = true;
	food = MAX_FOOD;
	torchEnergy = MAX_TORCH_ENERGY;
	for (int i = 0; i < currentNumItems; i++)
	{
		delete items[i];
	}
	//items = new Item[MAX_ITEMS];
	currentNumItems = 1;
	items[0] = new Torch;
	Position = Vector2D(0, 0);
	isTorchOn = false;
}

Player::Player()
{
	//items = new Item[1];
	Initialise();
}

Player::~Player()
{
	for (int i = 0; i < currentNumItems; i++)
	{
		delete items[i];
	}
}

void Player::Move(char * direction, Vector2D mapSize, myString exits)
{
	food--;
	Vector2D newPosition = Position;
	switch (*direction)
	{
	case 78:
	case 110:
		newPosition.y--;
		break;
	case 83:
	case 115:
		newPosition.y++;
		break;
	case 69:
	case 101:
		newPosition.x++;
		break;
	case 87:
	case 119:
		newPosition.x--;
		break;
	default:
		break;
	}
	if (newPosition.x < 0 || newPosition.x > mapSize.x || newPosition.y < 0 || newPosition.y > mapSize.y || exits.Find(direction) == -1)
	{
		std::cout << "You try to move that way, but hit a brick wall. Or was it a stone wall...?\n";
	}
	else
		Position = newPosition;
	if (food == 0)
		isAlive = false;
}

void Player::SetTorchEnergy(int amount)
{
	torchEnergy = amount;
	if (torchEnergy > MAX_TORCH_ENERGY)
		torchEnergy = MAX_TORCH_ENERGY;
	if (torchEnergy == 0)
	{
		isTorchOn = false;
		std::cout << "Your torch flickers out...\n";
	}
}

int Player::GetTorchEnergy()
{
	return torchEnergy;
}

void Player::AddFood(int amount)
{
	food += amount;
	if (food > MAX_FOOD)
		food = MAX_FOOD;
}

int Player::GetCurrentFood()
{
	return food;
}

Item* Player::GetItemPointer(char * itemName)
{
	myString invItem;
	myString itemNameMS = itemName;
	int itemToUse = -1;
	// check inventory for said item
	for (int i = 0; i < currentNumItems; i++)
	{
		invItem = items[i]->GetName();
		invItem = invItem.LCase();
		if (itemNameMS.Find(invItem.GetValue()) != -1)
		{
			return items[i];
		}
	}
	return nullptr;
}

void Player::SetTorchOn(bool isTorchOn)
{
	this->isTorchOn = isTorchOn;
}

void Player::DisplayInventory()
{
	std::cout << "You have on your person: ";
	for (int i = 0; i < currentNumItems; i++)
	{
		std::cout << items[i]->GetName() << "\t";
	}
	std::cout << "\n";
}

void Player::DisplayStatus()
{
	std::cout << "Player Stamina: " << food <<"\t Torch Energy Left: "<<torchEnergy;
}

bool Player::HasRoom()
{
	if (currentNumItems < MAX_ITEMS)
		return true;
	else
		return false;
}

void Player::AddItem(Item * itemToAdd)
{
	items[currentNumItems] = itemToAdd;
	currentNumItems++;
}

void Player::DestroyItem(char * itemName)
{
	myString invItem;
	int itemToUse = -1;
	// check inventory for said item
	for (int i = 0; i < currentNumItems; i++)
	{
		invItem = items[i]->GetName();
		invItem = invItem.LCase();
		if (invItem == itemName)
		{
			RemoveItem(i);
		}

	}
}

void Player::RemoveItem(int index)
{
	items[index] = items[currentNumItems - 1];
	currentNumItems--;
	items[currentNumItems] = nullptr;
}

Item * Player::GetItem(char * itemName)
{
	myString invItem;
	int itemToUse = -1;
	// check inventory for said item
	for (int i = 0; i < currentNumItems; i++)
	{
		invItem = items[i]->GetName();
		invItem = invItem.LCase();
		if (invItem == itemName)
		{
			Item* tempPointer = items[i];
			RemoveItem(i);
			return tempPointer;
		}
	}
	return nullptr;
}
