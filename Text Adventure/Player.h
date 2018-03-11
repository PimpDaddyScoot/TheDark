#ifndef PLAYER_H
#define PLAYER_H


// Player Class
//
// By Scott Purcival
// AIE - Introduction to C++ Assignment (First Year)
class Item;
#include "Item.h"
class Vector2D;
#include "Vector2D.h"
class Map;
#include "Map.h"

class Player
{
private:
	int					food;
	int					torchEnergy;
	static const int	MAX_FOOD = 25;
	static const int	MAX_TORCH_ENERGY = 10;
	static const int	MAX_ITEMS = 5;
	Item*				items[MAX_ITEMS];
	int					currentNumItems = 0;


public:

	Vector2D			Position;
	bool				isAlive;
	bool				isTorchOn;
		
			Player();
			~Player();

	void	Initialise();								// Function Sets Player to initial default values
	void	Move(char * direction, Vector2D mapSize, myString exits);
	void	SetTorchEnergy(int amount);
	int		GetTorchEnergy();
	void	AddFood(int amount);
	int		GetCurrentFood();
	Item*	GetItemPointer(char* itemName);
	void	SetTorchOn(bool isTorchOn);
	void	DisplayInventory();
	void	DisplayStatus();
	bool	HasRoom();
	void	AddItem(Item* itemToAdd);
	void	DestroyItem(char* itemName);
	void	RemoveItem(int index);
	Item*	GetItem(char* itemName);




};


#endif