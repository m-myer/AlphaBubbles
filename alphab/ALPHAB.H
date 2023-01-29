/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  alphab.h                                                        *
******************************************************************************/

#ifndef ALPHAB_H
#define ALPHAB_H

#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "model.h"
#include "events.h"
#include "renderer.h"
#include "types.h"
#include "music.h"
#include "effects.h"
#include "raster.h"
#include "video.h"
#include "isr.h"


/******************************************************************************
 *	Function: mainMenu                                                        *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Retrieves the current value of the 70HZ system timer.                 *
 *                                                                            *
 *****************************************************************************/
void mainMenu( UINT32 *base, UINT32 *base2, UINT32 *baseSnapshot );


/******************************************************************************
 *	Function: onePlayerGame                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Retrieves the current value of the 70HZ system timer.                 *
 *                                                                            *
 *****************************************************************************/
void onePlayerGame( UINT32 *base, UINT32 *base2, UINT32 *baseSnapshot );

/******************************************************************************
 *	Function: getTime                                                         *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Retrieves the current value of the 70HZ system timer.                 *
 *                                                                            *
 *****************************************************************************/
UINT32 getTime();

UINT32* getBuffer();

#endif
