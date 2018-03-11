#include "Map.h"

Map::Map()
{
	mapSize.x = 1;
	mapSize.y = 1;
	theMap = new Room[1];
}

Map::Map(int numRoomsX, int numRoomsY)
{
	mapSize.x = numRoomsX;
	mapSize.y = numRoomsY;
	theMap = new Room[(numRoomsX * numRoomsY)];
}

Map::~Map()
{
	delete[] theMap;
}

void Map::GenerateMap()
{
	Vector2D	currentCoords(0, 0);
	Vector2D	previousCoords(-1, -1);
	myString	exits = "";
	Item*		tempItem;

	for (int majorLoopCounter = 0; majorLoopCounter < (mapSize.x*mapSize.y); majorLoopCounter++)
	{
		// Set random room description
		myString descriptions[5] = {
			"You are in a musty smelling room, water drips in the background. You think you may have just kicked a skeleton... but you can't be sure",
			"You are in a dank room, you hear a rat squeak and scurry away. It smells of stale air.",
			"You find yourself in a cold room, there is an eerie breeze that seems to come from no particular direction and chills your bones.",
			"The room is still. Completely still. The floor is some kind of loose but dry sand or dirt. It crunches under your feet.",
			"You hear echoes of muffled screams and moans in the distance. They seem to come from no particular direction. The floor seems to be some kind of uneven stone." };
		theMap[ResolveIndex(currentCoords)].SetDescription(descriptions[rand() % 5].GetValue());

		// Add a random item, or no item.
		int itemToAdd = rand() % 100;
		int chanceForEach = CHANCE_OF_ITEMS / 6;
		if (itemToAdd >= (100 - chanceForEach))
			tempItem = new Batteries;
		else if (itemToAdd >= (100 - (chanceForEach * 3)))
		{
			switch (rand() % 2)
			{
			case 0:
				tempItem = new Mushroom;
				break;
			case 1:
				tempItem = new Bread;
				break;
			}
		}
		else if (itemToAdd >= (100 - (chanceForEach * 6)))
		{
			switch (rand() % 3)
			{
			case 0:
				tempItem = new Stone;
				break;
			case 1:
				tempItem = new Bone;
				break;
			case 2:
				tempItem = new DeadRat;
				break;
			}
		}

		if (itemToAdd >= (100 - CHANCE_OF_ITEMS))
		{
			theMap[majorLoopCounter].AddItem(tempItem);
			tempItem = nullptr;
		}

		// Set Exits
		theMap[ResolveIndex(currentCoords)].SetExits(exits.GetValue());		// sets exit from room that we just came from.

		// Check available directions
		int randDirection = rand() % 4 + 1;
		myString directions = "ESWN";
		bool tryBreakThroughWall = false;

		int nextDirection;
		for (int directionLoopCounter = 0; directionLoopCounter <= 4;)
		{
			nextDirection = randDirection + directionLoopCounter;
			if (nextDirection > 4)
				nextDirection -= 4;

			Vector2D nextCoords(currentCoords.x, currentCoords.y);
			switch (nextDirection)										// Discover out next coords
			{
			case 1: // EAST
				nextCoords.x = currentCoords.x + 1;
				break;
			case 2:	// SOUTH
				nextCoords.y = currentCoords.y + 1;
				break;
			case 3: // WEST
				nextCoords.x = currentCoords.x - 1;
				break;
			case 4: // NORTH
				nextCoords.y = currentCoords.y - 1;
				break;
			default:
				break;
			}
			if (directionLoopCounter == 4)
				tryBreakThroughWall = true;

			// check if if bounds of map, and if room already created
			if (tryBreakThroughWall == false)
			{
				if (nextCoords.x == mapSize.x || nextCoords.x < 0 || nextCoords.y == mapSize.y || nextCoords.y < 0 || theMap[ResolveIndex(nextCoords)].IsRoomCreated())
				{
					++directionLoopCounter;		// Try again!
				}
				else
				{
					// create a room
					// create exits
					// current room
					myString newExits = theMap[ResolveIndex(currentCoords)].GetExits();
					newExits = newExits.Append(directions.Mid(nextDirection-1, 1));
					theMap[ResolveIndex(currentCoords)].SetExits(newExits.GetValue());
					// next room, prep exits variable
					int reverseDirection = nextDirection + 2;
					if (reverseDirection > 4)
						reverseDirection -= 4;
					exits = directions.Mid(reverseDirection-1, 1);		// set exits for the start of the loop to use.
					// set coords and exit loop
					previousCoords = currentCoords;
					currentCoords = nextCoords;
					directionLoopCounter = 5;		//to exit loop
				}

			}
			else // try to break thru a wall
			{
				if (nextCoords.x == mapSize.x || nextCoords.x < 0 || nextCoords.y == mapSize.y || nextCoords.y < 0 || nextCoords == previousCoords)		// if its the edge of map or we are trying to go back where we came from
				{
					if (directionLoopCounter == 4)
						directionLoopCounter = 0;
					else
						++directionLoopCounter;
				}
				else
				{
					// create a door both sides.

					// current room
					myString newExits = theMap[ResolveIndex(currentCoords)].GetExits();
					newExits = newExits.Append(directions.Mid(nextDirection-1, 1));
					theMap[ResolveIndex(currentCoords)].SetExits(newExits.GetValue());

					// next room
					int reverseDirection = nextDirection + 2;
					if (reverseDirection > 4)
						reverseDirection -= 4;
					newExits = theMap[ResolveIndex(nextCoords)].GetExits();
					newExits = newExits.Append(directions.Mid(reverseDirection-1, 1));
					theMap[ResolveIndex(nextCoords)].SetExits(newExits.GetValue());

					// find first empty room and exit loop
					for (int roomSearchCounter = 0; roomSearchCounter < (mapSize.x * mapSize.y); roomSearchCounter++)
					{
						if (theMap[roomSearchCounter].IsRoomCreated() == false)
						{
							currentCoords = IndexToVector(roomSearchCounter);
							roomSearchCounter = (mapSize.x * mapSize.y);
							previousCoords = nextCoords;
							// set exit to one up or left
							if (currentCoords.x != 0)
							{
								// set door to left aka WEST
								exits = "W";
								nextCoords = currentCoords;
								nextCoords.x -= 1;
								newExits = theMap[ResolveIndex(nextCoords)].GetExits();
								newExits = newExits.Append("E");
							}
							else
							{
								// set door to up aka NORTH
								exits = "N";
								nextCoords = currentCoords;
								nextCoords.y -= 1;
								newExits = theMap[ResolveIndex(nextCoords)].GetExits();
								newExits = newExits.Append("S");
							}
						}
					}
					directionLoopCounter = 5;		// exit the direction loop.
				}
			}
		}
	}
}

int Map::ResolveIndex(Vector2D coordinates)
{
	int resolvedIndex = 0;
	if (coordinates.x > mapSize.x)
		coordinates.x = mapSize.x;
	if (coordinates.y > mapSize.y)
		coordinates.y = mapSize.y;

	resolvedIndex += coordinates.x;
	resolvedIndex += coordinates.y * mapSize.x;

	return resolvedIndex;
}

Vector2D Map::IndexToVector(int index)
{
	Vector2D theVector;
	theVector.y = (index / mapSize.x);
	theVector.x = index - (theVector.y * mapSize.x);

	return theVector;
}

void Map::SetFinish(int index)
{
	theMap[index].IsFinalExit(true);
	theMap[index].SetDescription("A bright light shines above you, like a beacon from heaven. All your worries vanish as you realise you have made it. You are at the end! Congratulations!");
}

void Map::Reset(int numRoomsX, int numRoomsY)
{
	delete[] theMap;
	mapSize.x = numRoomsX;
	mapSize.y = numRoomsY;
	theMap = new Room[(numRoomsX * numRoomsY)];
}

void Map::DisplayRoom(Vector2D location, bool isTorchOn)
{
	if (location.x > mapSize.x || location.y > mapSize.y || location.x < 0 || location.y < 0)
	{
		std::cout << "\nYou see nothing. As you are looking off the edge of the known universe (ie. OUT OF BOUNDS)\n";
	}
	else
	{
		int locationIndex = ResolveIndex(location);
		theMap[locationIndex].Look(isTorchOn);
	}


}

char * Map::AvailableExits(Vector2D location)
{
	return theMap[ResolveIndex(location)].GetExits();
}

Item * Map::GetItemPointer(char * itemName, Vector2D location)
{
	myString invItem;
	myString itemNameMS = itemName;
	int itemToUse = -1;
	// check inventory for said item
	for (int i = 0; i < theMap[ResolveIndex(location)].GetNumItems(); i++)
	{
		invItem = theMap[ResolveIndex(location)].GetItemName(i); //items[i].GetName();
		invItem = invItem.LCase();
		if (itemNameMS.Find(invItem.GetValue())!=-1)
		{
			return theMap[ResolveIndex(location)].GetItem(i);
		}
	}
	return nullptr;
}

Item * Map::GetItem(char * itemName, Vector2D location)
{
	myString invItem;
	int itemToUse = -1;
	// check inventory for said item
	for (int i = 0; i < theMap[ResolveIndex(location)].GetNumItems(); i++)
	{
		invItem = theMap[ResolveIndex(location)].GetItemName(i); //items[i].GetName();
		invItem = invItem.LCase();
		if (invItem == itemName)
		{
			Item* tempPointer = theMap[ResolveIndex(location)].GetItem(i);
			theMap[ResolveIndex(location)].RemoveItem(i);
			return tempPointer;
		}
	}
	return nullptr;
}

void Map::DestroyItem(char * itemName, Vector2D location)
{
	myString invItem;
	int itemToUse = -1;
	// check inventory for said item
	for (int i = 0; i < theMap[ResolveIndex(location)].GetNumItems(); i++)
	{
		invItem = theMap[ResolveIndex(location)].GetItemName(i); //items[i].GetName();
		invItem = invItem.LCase();
		if (invItem == itemName)
			theMap[ResolveIndex(location)].RemoveItem(i);
	}
}

bool Map::HasRoom(Vector2D location)
{
	if (theMap[ResolveIndex(location)].HasRoom())
		return true;
	else
		return false;
}

void Map::AddItem(Item* itemPointer, Vector2D location)
{
	theMap[ResolveIndex(location)].AddItem(itemPointer);
}

bool Map::WeAreAtFinish(Vector2D location)
{
	return theMap[ResolveIndex(location)].IsFinalExit();
}
