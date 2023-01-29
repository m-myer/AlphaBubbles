/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  music.h                                                         *
******************************************************************************/

#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"

#define PAUSE 0
#define E_NOTE 170
#define G_NOTE 143
#define A_NOTE 127
#define B_NOTE 113
#define C_NOTE 107
#define D_NOTE 95
#define HIGH_E_NOTE 85


/******************************************************************************
 *	                        Function: startMusic                              *
 *****************************************************************************/
void startMusic();


/******************************************************************************
 *	                       Function: updateMusic                              *
 *****************************************************************************/
int updateMusic(UINT32 timeElapsed, int lastNote);

#endif