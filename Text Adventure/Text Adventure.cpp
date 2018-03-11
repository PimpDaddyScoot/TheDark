#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "myString.h"
#include "Vector2D.h"
#include "Room.h"
#include "Map.h"
#include "Player.h"
#include "Item.h"


using namespace std;
void Initialise();
void PlayGame();

static const int	numRoomsX = 5;
static const int	numRoomsY = 5;
Map					theMap(numRoomsX, numRoomsY);
Player				thePlayer;

void main()
{
	bool isPlaying = true;
	while (isPlaying)
	{
		system("CLS");
		cout << "Welcome to THE DARK\nA horror survival Text Adventure.\n\nFind your way to the exit, before you starve...\n\n";
		cout << "Type HELP for a command list.\n\n";

		Initialise();
		PlayGame();

		char response = 0;
		while (response == 0)
		{
			cout << "\nPlay again? (Y/N) ";
			response = getchar();
			switch (response)
			{
			case 89:
			case 121:
				isPlaying = true;
				break;
			case 78:
			case 110:
				isPlaying = false;
				break;
			default:
				response = 0;
				break;
			}
			cin.ignore();
		}
	}
}

void Initialise()
{
	// seed rand
	srand(time(NULL));

	// Reset Data
	thePlayer.Initialise();
	theMap.Reset(numRoomsX, numRoomsY);
	thePlayer.Position = Vector2D(rand() % numRoomsX, rand() % numRoomsY);	// random start
	
	// Generate Map
	theMap.GenerateMap();
	theMap.SetFinish(rand() % (numRoomsX*numRoomsY));						// random end
}

void PlayGame()
{
	bool		weArePlaying = true;
	string		userInput;
	myString	command;
	Item*		itemPointer;
	myString	commandArgs;

	// Readout room
	cout << "\n";
	theMap.DisplayRoom(thePlayer.Position, thePlayer.isTorchOn);
	thePlayer.DisplayStatus();

	while (weArePlaying)
	{
		// ask for input
		cout << "\nWhat do you want to do? ";
		getline(cin, userInput);
		command = (char*)userInput.c_str();
		command = command.LCase();

		// Parse command
		if (command.Find("look") >= 0)
		{
			// look in general or at something?
			if (command.Length() == 4)
			{
				// look in general
				theMap.DisplayRoom(thePlayer.Position, thePlayer.isTorchOn);
				if (thePlayer.isTorchOn)
					thePlayer.SetTorchEnergy(thePlayer.GetTorchEnergy() - 1);
			}
			else
			{
				// look at something
				if (thePlayer.isTorchOn)
				{
					command = command.Replace("look ", "");
					itemPointer = thePlayer.GetItemPointer(command.GetValue());							// check the player
					if (itemPointer == nullptr)
					{
						itemPointer = theMap.GetItemPointer(command.GetValue(), thePlayer.Position);	// check the map
					}
					if (itemPointer != nullptr)
						cout << itemPointer->GetDescription() << "\n";
					else
						cout << "You don't seem to have one of those nearby to look at.\n";
				}
				else
					cout << "It's too dark to really see anything.\n";
			}
		}
		if (command.Find("go") >= 0)
		{
			if (command.Find("n") >= 0)
				thePlayer.Move("N", theMap.mapSize, theMap.AvailableExits(thePlayer.Position));
			else if (command.Find("e") >= 0)
				thePlayer.Move("E", theMap.mapSize, theMap.AvailableExits(thePlayer.Position));
			else if (command.Find("s") >= 0)
				thePlayer.Move("S", theMap.mapSize, theMap.AvailableExits(thePlayer.Position));
			else if (command.Find("w") >= 0)
				thePlayer.Move("W", theMap.mapSize, theMap.AvailableExits(thePlayer.Position));
			// Readout room
			cout << "\n";
			theMap.DisplayRoom(thePlayer.Position, thePlayer.isTorchOn);
			if (thePlayer.isTorchOn)
				thePlayer.SetTorchEnergy(thePlayer.GetTorchEnergy() - 1);
			thePlayer.DisplayStatus();

		}
		if (command.Find("quit") >= 0)
			weArePlaying = false;
		if (command.Find("help") >=0)
			cout << "The following are your available commands: GO, LOOK, USE, INV, GET, DROP, QUIT, and obviously, HELP.\n";
		if (command.Find("inv") >= 0)
			thePlayer.DisplayInventory();
		if (command.Find("use") >= 0)
		{
			bool itemIsOnMap = false;
			command = command.Replace("use ", "");
			itemPointer = thePlayer.GetItemPointer(command.GetValue());							// check the player
			if (itemPointer == nullptr)
			{
				itemIsOnMap = true;
				itemPointer = theMap.GetItemPointer(command.GetValue(), thePlayer.Position);		// check the map
			}
			if (itemPointer != nullptr)
			{
				// GET Args
				int argsStart = command.Find(" ");
				if (argsStart != -1)
				{
					commandArgs = command.Mid(argsStart + 1, command.Length() - argsStart);
					command = command.Mid(0, argsStart);
				}
				else
					commandArgs = "";
				// Use Item
				itemPointer->Use(&thePlayer, &theMap, commandArgs.GetValue());
				if (itemPointer->destroyMe)
				{
					if (itemIsOnMap)
						theMap.DestroyItem(command.GetValue(), thePlayer.Position);
					else
						thePlayer.DestroyItem(command.GetValue());
					delete itemPointer;
				}
			}
			else
				cout << "You do not appear to have that item on you, or nearby.\n";
		}

		if (command.Find("get") >= 0)
		{
			if (thePlayer.HasRoom())
			{
				command = command.Replace("get ", "");
				itemPointer = theMap.GetItem(command.GetValue(), thePlayer.Position);		// check the map
				if (itemPointer != nullptr)
					thePlayer.AddItem(itemPointer);
				else
					cout << "You can't see that item nearby.\n";
			}
			else
				cout << "You do not have enough room to carry any more.\n";
		}

		if (command.Find("drop")>=0)
		{
			if (theMap.HasRoom(thePlayer.Position))
			{
				command = command.Replace("drop ", "");
				itemPointer = thePlayer.GetItem(command.GetValue());
				if (itemPointer != nullptr)
				{
					theMap.AddItem(itemPointer, thePlayer.Position);
					// in case they drop the torch
					myString theItemsName = itemPointer->GetName();
					theItemsName = theItemsName.LCase();
					if (theItemsName == "torch" && thePlayer.isTorchOn)
					{
						thePlayer.isTorchOn = false;
						cout << "The room goes dark.\n";
					}
				}
			}
			else
				cout << "The floor is a bit too cluttered to go dropping things here...\n";
		}
		// check for dead
		if (thePlayer.isAlive == false)
		{
			cout << "\n\n\nYou Starved to Death. GAME OVER.\n";
			weArePlaying = false;
		}
		if (theMap.WeAreAtFinish(thePlayer.Position))
		{
			cout << "\n\nYOU WIN!! :D\n";
			weArePlaying = false;
		}
	}


}
