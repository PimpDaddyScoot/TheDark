#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// Item class
//
// By Scott Purcival
// AIE - Introduction to C++ Assignment (First Year)
class myString;
#include "myString.h"
class Map;
#include "Map.h"
class Player;
#include "Player.h"


class Item
{
protected:
	myString	itemName;
	myString	itemDescription;


public:
				Item();
				~Item();
				Item(char* newItemName, char* newItemDescription);

	void		SetName(char* newItemName);
	char*		GetName();
	void		SetDescription(char* newItemDescription);
	virtual void Use(Player* targetPlayer, Map* targetMap, char* args);
	bool		destroyMe = false;
	char*		GetDescription();

};

class Food : public Item											// Food - Used to add Energy
{
public:
					Food();
					~Food();
	virtual void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Bread : public Food
{
private:
	static const int	ENERGY_TO_ADD = 10;

public:
				Bread();
				~Bread();
	void		Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Mushroom : public Food
{
private:
	static const int	ENERGY_TO_ADD = 5;

public:
	Mushroom();
	~Mushroom();
	void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Batteries : public Item										// Batteries - Used for torch
{
private:
	int		batEnergyLeft = rand() % 20 + 1;						// New Battery objects get random amount of charge
public:
			Batteries();
			~Batteries();
	void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Throwable : public Item											// Throwable - Used to throw, to check for rooms ahead
{
public:
			Throwable();
			~Throwable();
	virtual void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Stone : public Throwable
{
public:
			Stone();
			~Stone();
	void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Bone : public Throwable
{
public:
	Bone();
	~Bone();
	void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class DeadRat : public Throwable
{
public:
	DeadRat();
	~DeadRat();
	void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

class Torch : public Item
{
public:
			Torch();
			~Torch();
	void	Use(Player* targetPlayer, Map* targetMap, char* args);
};

#endif