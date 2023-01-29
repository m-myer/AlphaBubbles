/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  bitmaps.h                                                       *
******************************************************************************/

/* Bitmaps translated with the help of the bitmap converter tool found at 
   http://en.radzio.dxp.pl/bitmap_converter and with byteToOther.cpp 
   written by Joel van Egmond */

#ifndef BITMAPS_H
#define BITMAPS_H

#include "types.h"

#define LETTER_MAP_HEIGHT 16
#define LETTER_MAP_WIDTH 8
#define BUBBLE_MAP_HEIGHT 48
#define ARROW_MAP_HEIGHT 24
#define PROG_BUBBLE_HEIGHT 44
#define NUM_MAP_HEIGHT 50
#define NUM_MAP_WIDTH 16
#define LIVES_MAP_HEIGHT 64
#define LIVES_MAP_WIDTH 192
#define BUBBLE_AREA_X1 3
#define BUBBLE_AREA_X2 391
#define BUBBLE_AREA_Y 3
#define MOUSE_BACKGROUND_SIZE 16
#define MOUSE_HEIGHT 16
#define MOUSE_SIZE 16

extern const UINT8 letterMaps[];	/* Bubble letters */
extern const UINT16 progBubbleMap[];/* Bubbles for filling the progress bar */
extern const UINT32 bubbleMap[]; 	/* Game Bubble */
extern const UINT32 popped1Map[];
extern const UINT32 popped2Map[]; 	/* Popped Game Bubble */
extern const UINT32 popped3Map[];
extern const UINT32 arrowMap[];
extern const UINT16 numberMaps[];  	/* Score Digits */
extern const UINT32 progBarMap[];	/* Progress Bar */
extern const UINT32 lives3Map[]; 	/* Lives Counter Table Full */
extern const UINT32 lives2Map[]; 	/* Lives Counter Table 2 Lives Left */
extern const UINT32 lives1Map[]; 	/* Lives Counter Table 1 Life Left*/
extern const UINT32 lives0Map[]; 	/* Lives Counter Table No Lives*/
extern const UINT32 scoreTableMap[];/* Score Table */
extern const UINT32 gameScreen[];   /* background w assets */

#endif
