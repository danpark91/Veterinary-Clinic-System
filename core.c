#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
	// Discard all remaining char's from the standard input buffer:
	while (getchar() != '\n')
	{
		; // do nothing!
	}
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

// Dispaly an array of 10-character digits
void displayFormattedPhone(const char* validatedString)
{
	int i = 0;
	int isValid = 1; // validate that characters are digits

	if (validatedString == NULL)
	{
		// Print an empty phone number
		printf("(___)___-____");
	}
	else if (validatedString == 0)
	{
		printf("(___)___-____");
	}
	else if (strlen(validatedString) != 10)
	{
		printf("(___)___-____");
	}
	else if (strlen(validatedString) == 10)
	{

		for (i = 0; i < 10; i++)
		{
			if (validatedString[i] != '0' && validatedString[i] != '1' &&
				validatedString[i] != '2' && validatedString[i] != '3' &&
				validatedString[i] != '4' && validatedString[i] != '5' &&
				validatedString[i] != '6' && validatedString[i] != '7' &&
				validatedString[i] != '8' && validatedString[i] != '9')
			{
				isValid = 0; // character is not a digit
			}
		}

		if (isValid && i == 10)
		{
			// Print the phone number with the digits
			printf("(%c%c%c)%c%c%c-%c%c%c%c",
				validatedString[0],
				validatedString[1],
				validatedString[2],
				validatedString[3],
				validatedString[4],
				validatedString[5],
				validatedString[6],
				validatedString[7],
				validatedString[8],
				validatedString[9]);
		}
		else
		{
			printf("(___)___-____");
		}

	}
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get a valid integer
int inputInt()
{
	char newline; // represent the enter key
	int value; // integer named value

	do
	{
		scanf(" %d%c", &value, &newline); //input a value and enter

		if (newline == '\n')
		{
			;
		}
		else
		{
			clearInputBuffer(); // clear the input buffer
			// Print the error message when the input buffer is not '\n'
			printf("Error! Input a whole number: ");
		}
	} while (newline != '\n');

	return value;// return the input value
}

// Get a positive integer
int	inputIntPositive()
{
	int value;

	do
	{
		value = inputInt(); //call inputInt and assign the value to value

		if (value <= 0)
		{
			// Print error message when value is less or equal to 0
			printf("ERROR! Value must be > 0: ");
		}
	} while (value <= 0);

	return value;
}

// Get a range of integer
int	 inputIntRange(int low, int high)
{
	int value;

	do
	{
		value = inputInt();

		if (value < low || value > high)
		{
			// Print error message when valus is not between the range
			printf("ERROR! Value must be between %d and %d inclusive: ",
				low, high);
		}
	} while (value < low || value > high);

	return value;
}

// Get a single valid character
char inputCharOption(const char* validChars)
{
	int error; // flag, 1 = buffer is not valid and 0 = buffer is valid
	int i;
	int n;
	char oneChar[80] = { '\0' }; // a character named oneChar, one char is expected

	do
	{
		i = 0;
		n = 0;
		scanf(" %s", oneChar); // input one single character

		for (i = 0; i < (int)strlen(validChars); i++)
		{
			if (validChars[i] == oneChar[0])
			{
				n++;
			}
		}

		if (n == 1 && (int)strlen(oneChar) == 1)
		{
			error = 0;
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", validChars);
			error = 1;
		}
	} while (error != 0);

	return oneChar[0];
}

// Obtain user input for C String with a length range specified in inputIntRange
void inputCString(char* result, int minChars, int maxChars)
{
	char cString[80] = { 0 };// C String containing input string
	int error = 0;

	do
	{
		// input a string that can contain multiple words
		scanf("%[^\n]", cString);

		if (minChars == maxChars && strlen(cString) != minChars)
		{
			clearInputBuffer();
			printf("Invalid %d-digit number! Number: ",
				minChars);

			error = 1;
		}
		else if (strlen(cString) < minChars)
		{
			clearInputBuffer();
			printf("ERROR: String length must be between %d and %d chars: ",
				minChars, maxChars);
			error = 1;
		}
		else if (strlen(cString) > maxChars)
		{
			clearInputBuffer();
			printf("ERROR: String length must be no more than %d chars: ",
				maxChars);
			error = 1;
		}
		else
		{
			strcpy(result, cString); //copy the input string into result
			error = 0;
		}
	} while (error != 0);
}