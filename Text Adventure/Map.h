#ifndef MAP_H
#define MAP_H

class Room;
#include "Room.h"

class Vector2D;
#include "Vector2D.h"

class Map
{
private:
	Room*				theMap;
	static const int	CHANCE_OF_ITEMS = 50;	// This is a percentage. 100 means every room has an item. 0 means none do.

public:
	Vector2D			mapSize;

						Map();
						Map(int numRoomsX, int numRoomsY);
						~Map();

	void				GenerateMap();
	int					ResolveIndex(Vector2D coordinates);
	Vector2D			IndexToVector(int index);
	void				SetFinish(int index);
	void				Reset(int numRoomsX, int numRoomsY);
	void				DisplayRoom(Vector2D location, bool isTorchOn);
	char*				AvailableExits(Vector2D location);
	Item*				GetItemPointer(char* itemName, Vector2D location);
	Item*				GetItem(char* itemName, Vector2D location);
	void				DestroyItem(char* itemName, Vector2D location);
	bool				HasRoom(Vector2D location);
	void				AddItem(Item* itemPointer, Vector2D location);
	bool				WeAreAtFinish(Vector2D location);

};




#endif
