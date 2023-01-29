/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  input.c                                                         *
******************************************************************************/

#include "input.h"


/******************************************************************************
 *	Function: checkInput                                                      *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Checks to see if the user has entered anything on their keyboard.     *
 *                                                                            *
 *****************************************************************************/
bool checkInput()
{
	bool  hasInput = false;
	
	if (ikbdWaiting())
		hasInput = true;
	
	return hasInput;
}


/******************************************************************************
 *	Function: getInput                                                        *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Reads the user input.                                                 *
 *                                                                            *
 *****************************************************************************/
UINT32 getInput()
{
	UINT32 input;
	
	input = readIkbdBuffer();
	
	return input;
}


/******************************************************************************
 *	Function: checkMouseInput                                                 *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Checks to see if the user has moved the mouse                         *
 *                                                                            *
 *****************************************************************************/
bool checkMouseInput() 
{
	bool hasInput = false;
	
	if (ikbdMouseMoved())
		hasInput = true;
	
  return hasInput;
}

