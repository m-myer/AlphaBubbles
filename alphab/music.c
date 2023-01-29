/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  music.c                                                         *
******************************************************************************/

#include "music.h"
#include <stdio.h>

int song[] = {
	A_NOTE, A_NOTE, E_NOTE, G_NOTE,
	A_NOTE, A_NOTE, E_NOTE, G_NOTE,
	A_NOTE, A_NOTE, E_NOTE, G_NOTE,
	B_NOTE, B_NOTE, A_NOTE, A_NOTE,
	A_NOTE, A_NOTE, E_NOTE, G_NOTE,
	A_NOTE, A_NOTE, E_NOTE, G_NOTE,
	A_NOTE, A_NOTE, E_NOTE, G_NOTE,
	B_NOTE, B_NOTE, A_NOTE, A_NOTE,
	C_NOTE, C_NOTE, A_NOTE, G_NOTE, 
	C_NOTE, C_NOTE, HIGH_E_NOTE, D_NOTE,
	C_NOTE, C_NOTE, A_NOTE, G_NOTE, 
	C_NOTE, C_NOTE, HIGH_E_NOTE, D_NOTE 
	};
	 


/******************************************************************************
 *	Function: startMusic                                                      *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Enables to proper settings to allow the music to be played            *
 *                                                                            *
 *****************************************************************************/
void startMusic()
{
	enableChannel(CH_A, 1, 0);
	setEnvelope(4, 10);
	setVolume(CH_A, 8);
	return;
}


/******************************************************************************
 *	Function: updateMusic                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Changes the note of the melody                                        *
 *                                                                            *
 *****************************************************************************/
int updateMusic(UINT32 timeElapsed, int lastNote)
{
	if (timeElapsed >= 35)
	{	
		if (lastNote == 48)
			lastNote = 0;
		
		setTone(CH_A, song[lastNote]);
		lastNote++;
	}
		
	return lastNote;
}