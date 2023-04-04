/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  effects.c                                                       *
******************************************************************************/ 

#include "effects.h"


/******************************************************************************
 *	Function: playChime                                                   *
 *                                                                            *
 *	Purpose:                                                              *
 *	 	 Plays a chiming sound when the progress bar has been filled  *
 *                                                                            *
 *****************************************************************************/
void playChime()
{
	disableChannel(CH_C);
	enableChannel(CH_C, 1, 0);
	setTone(CH_C, 0x010);
	setVolume(CH_C, 16);
	setEnvelope(0, 48);
	
	return;
}


/******************************************************************************
 *	Function: playPop                                                     *
 *                                                                            *
 *	Purpose:                                                              *
 *	 	 Plays a popping sound when the player has popped a bubble    *
 *                                                                            *
 *****************************************************************************/
void playPop()
{
	disableChannel(CH_C);
	enableChannel(CH_C, 0, 1);
	setVolume(CH_C, 16);
	setEnvelope(0, 10);
	
	return;
}


/******************************************************************************
 *	Function: playSpawn                                                   *
 *                                                                            *
 *	Purpose:                                                              *
 *	 	 Plays a unique sound when a bubble has spawned into the      *
 *               play area                                                    *
 *                                                                            *
 *****************************************************************************/
void playSpawn()
{
	disableChannel(CH_C);
	enableChannel(CH_C, 1, 0);
	setTone(CH_C, 0x327);
	setVolume(CH_C, 16);
	setEnvelope(4, 1);
	
	return;
}
