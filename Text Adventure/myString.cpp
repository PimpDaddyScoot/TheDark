#include "myString.h"

// private
int myString::calculateLength(char * newString)
{
	int currentPosition = 0;		// this tracks the current pos in the incoming string
	while (newString[currentPosition] != 0)
	{
		++currentPosition;
	}
	return currentPosition;
}

void myString::resizeString()		// this resizes the string
{
	char * toBeDeleted = theString;
	theString = new char[stringLength+1];
	delete[] toBeDeleted;
}

bool myString::compareIfEqual(char* string1, char*string2)
{
	for (int currentIndex = 0; currentIndex <= calculateLength(string1); ++currentIndex)
	{
		if (string1[currentIndex] != string2[currentIndex])				// compare each character, if not the same, return false.
			return false;
	}

	return true;
}

// public
myString::myString()							// Constructor to create blank string
{
	theString = new char[1];
	theString[0] = 0;
	outputString = new char[1];
	outputString[0] = 0;
}

myString::myString(char* newValue)				// overloaded constructor to accept incoming string
{
	stringLength = calculateLength(newValue);
	theString = new char[stringLength+1];
	for (int currentPos = 0; currentPos <= stringLength; ++currentPos)
	{
		theString[currentPos] = newValue[currentPos];
	}
	outputString = new char[1];
	outputString[0] = 0;
}

myString::~myString()
{
	delete[] theString;
	delete[] outputString;
}

void myString::SetValue(char * newValue)
{
	stringLength = calculateLength(newValue);
	resizeString();
	for (int currentPos = 0; currentPos <= stringLength; ++currentPos)
	{
		theString[currentPos] = newValue[currentPos];
	}
}

char * myString::GetValue()
{
	return theString;
}

int myString::Length()
{
	return stringLength;
}

char * myString::Mid(int startIndex, int numChars)
{
	delete[] outputString;																// this was defined in the constructor
	outputString = new char[numChars+1];												// have to add 1 for the terminator

	int outputStringPos = 0;
 	while (outputStringPos < numChars && (startIndex + outputStringPos) < stringLength)
	{
		outputString[outputStringPos] = theString[startIndex + outputStringPos];
		++outputStringPos;
	}
	outputString[outputStringPos] = 0;													// set the terminator
	return outputString;
}

bool myString::IsEqual(char * inputString)
{
	return compareIfEqual(theString, inputString);
}

char * myString::LCase()
{
	delete[] outputString;
	outputString = new char[stringLength + 1];

	for (int i = 0; i <= stringLength ; i++)
	{
		if (theString[i] >= 65 && theString[i] <= 90)
			outputString[i] = theString[i] + 32;
		else
			outputString[i] = theString[i];
	}
		
	return outputString;
}

char * myString::UCase()
{
	delete[] outputString;
	outputString = new char[stringLength + 1];

	for (int i = 0; i <= stringLength; i++)
	{
		if (theString[i] >= 97 && theString[i] <= 122)
			outputString[i] = theString[i] - 32;
		else
			outputString[i] = theString[i];
	}

	return outputString;
}

char * myString::Prepend(char * stringToPrepend)
{
	int stringToPrependLength = calculateLength(stringToPrepend);
	delete[] outputString;
	outputString = new char[stringLength + stringToPrependLength + 1];

	for (int i = 0; i < stringToPrependLength; i++)
	{
		outputString[i] = stringToPrepend[i];
	}

	for (int i = 0; i <= stringLength; i++)
	{
		outputString[i + stringToPrependLength] = theString[i];
	}

	return outputString;
}

char * myString::Append(char * stringToAppend)
{
	int stringToAppendLength = calculateLength(stringToAppend);
	delete[] outputString;
	outputString = new char[stringLength + stringToAppendLength + 1];

	for (int i = 0; i < stringLength; i++)
	{
		outputString[i] = theString[i];
	}

	for (int i = 0; i <= stringToAppendLength; i++)
	{
		outputString[stringLength + i] = stringToAppend[i];
	}

	return outputString;
}

int myString::Find(char * stringToFind)
{
	int lengthOfStringToFind = calculateLength(stringToFind);
	
	for (int i = 0; i < stringLength; i++)
	{
		if (compareIfEqual(Mid(i, lengthOfStringToFind), stringToFind))
			return i;
	}

	return -1;																	// return -1 indicates the function failed to find a match
}

int myString::Find(char * stringToFind, int startIndex)
{
	int lengthOfStringToFind = calculateLength(stringToFind);

	for (int i = startIndex; i < stringLength; i++)								// start at index startIndex. If startIndex !< stringLength then loop will end.
	{
		if (compareIfEqual(Mid(i, lengthOfStringToFind), stringToFind))
			return i;
	}

	return -1;																	// return -1 indicates the function failed to find a match
}

char * myString::Replace(char * stringToFind, char * stringToInsert)
{
	int stringToFindStart = Find(stringToFind);												// find stringToFind
	int stringToFindLength = calculateLength(stringToFind);									// calc stringToFind's length
	int stringToInsertLength = calculateLength(stringToInsert);								// calc	stringToInsert's length
	int outputStringLength;

	if (stringToFindStart != -1)															// if we found the string, replace it!
	{
		outputStringLength = (stringLength + stringToInsertLength) - stringToFindLength;
		delete[] outputString;
		outputString = new char[outputStringLength + 1];

		for (int i = 0; i < stringToFindStart; i++)
		{
			outputString[i] = theString[i];
		}
		for (int i = 0; i < stringToInsertLength; i++)
		{
			outputString[i + stringToFindStart] = stringToInsert[i];
		}
		int remainderOfOutputString = outputStringLength - (stringToFindStart + stringToInsertLength);
		for (int i = 0; i <= remainderOfOutputString; i++)
		{
			outputString[i + (stringToFindStart + stringToInsertLength)] = theString[i + (stringToFindStart + stringToFindLength)];
		}
		return outputString;
	}
	else
		return theString;																	// otherwise just return theString unaltered.
}

char * myString::ReplaceAll(char * stringToFind, char * stringToInsert)
{
	myString outputmyString = theString;													// temporary myString object to allow recursive replacing.
	while (outputmyString.Find(stringToFind) != -1)
	{
		outputmyString = outputmyString.Replace(stringToFind, stringToInsert);
	}

	delete[] outputString;
	outputString = new char[outputmyString.Length() + 1];
	for (int i = 0; i <= outputmyString.Length(); i++)
	{
		outputString[i] = *outputmyString.Mid(i, 1);
	}
	return outputString;
}

char myString::GetChar(int index)
{
	if (index < stringLength && index >= 0)
		return theString[index];
	else
		return 0;
}

// Operator Overloads
bool myString::operator==(char * inputString)
{
	return IsEqual(inputString);
}

bool myString::operator==(myString& inputString)
{
	return IsEqual(inputString.GetValue());
}

void myString::operator=(char * inputString)
{
	SetValue(inputString);
}

void myString::operator=(myString & inputString)
{
	SetValue(inputString.GetValue());
}
