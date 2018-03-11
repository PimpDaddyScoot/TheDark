#ifndef MYSTRING_H
#define MYSTRING_H

// The Worlds most amazing 'myString' Class!
//
// By Scott Purcival
// AIE - Introduction to C++ Assignment (First Year)

class myString
{
private:
	char*	theString;											// This is the array where we store our string :D
	char*	outputString;										// This is used in functions to return a string to our program
	char*	replaceAllOutputString;								// This is used in ReplaceAll to return a string to our program, as it needs outputString for Replace
	int		stringLength = 0;									// Stores the length of our string - saves calculating it every time we want it, and is always equal to the size of our array
		
	int		calculateLength(char * newString);					// calculate the length of Char[] newString
	void	resizeString();										// resizes the string array on heap to stringLength + 1
	bool	compareIfEqual(char* string1, char*string2);		// compares two strings to see if they are the same

protected:
																// Nothing yet

public:
			myString();											// Constructor, default, sets myString to ""
			myString(char* newValue);							// Constructor which sets myString to newValue, a Char[]
			~myString();										// Destructor

	void	SetValue(char* newValue);							// Sets the value of this myString object to newValue, accepts Char[]
	char*	GetValue();											// Returns the value of this myString object as Char[]
	int		Length();											// Returns Length of this myString object
	char*	Mid(int startIndex, int numChars);					// Extracts Char[] numChars in length, starting at startIndex
	bool	IsEqual(char* inputString);							// Comparator - accepts Char[], returns bool
	char*	LCase();											// Returns this string in lowercase
	char*	UCase();											// Returns this string in uppercase
	char*	Prepend(char* stringToPrepend);						// Returns stringToPrepend + self
	char*	Append(char* stringToAppend);						// Returns self + stringToAppend
	int		Find(char* stringToFind);							// Returns index of stringToFind
	int		Find(char* stringToFind, int startIndex);			// Returns index of stringToFind, starting from startIndex
	char*	Replace(char* stringToFind, char* stringToInsert);	// Returns self with first instance of stringToFind replaced with stringToInsert	
	char*	ReplaceAll(char* stringToFind, char* stringToInsert);// Returns self with all instances of stringToFind replaced with stringToInsert
	char	GetChar(int index);									// Returns a single char at index

	// Operator Overloads - just for intuitive use.
		
	bool	operator==	(char* inputString);						// Char[] Comparator - returns bool
	bool	operator==	(myString &inputString);					// myString Comparator - returns bool
	void	operator=	(char* inputString);						// Char[] Assignment operator
	void	operator=	(myString &inputString);					// myString Assignment operator
};


#endif // MYSTRING_H
