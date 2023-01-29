/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  raster.h                                                        *
******************************************************************************/

#ifndef RASTER_H
#define RASTER_H

#include "types.h"
#include "video.h"


/* ========================================================================== *
 *                                                                            *
 *                                Constants                                   *
 *                                                                            *
 * ==========================================================================*/

#define VIDEO_REG_HIGH 0xFF8201
#define VIDEO_REG_MID 0xFF8203
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BITS_IN_BYTE 8
#define BITS_IN_WORD 16
#define BITS_IN_LONG 32
#define CLEAR8 0x00
#define CLEAR32 0x00000000
#define SOLID16 0xFFFF



/******************************************************************************
 *	                       Function: getVideoBase                             *
 *****************************************************************************/
UINT32 *getVideoBase();


/******************************************************************************
 *	                       Function: setVideoBase                             *
 *****************************************************************************/
void setVideoBase(UINT32 *base);

/******************************************************************************
 *	                        Function: clearScreen                             *
 *****************************************************************************/
void clearScreen(UINT32 *base);

/******************************************************************************
 *	                         Function: clearBox                               *
 *****************************************************************************/
void clearBox(UINT8 *base, int x1, int x2, int y, int height);

/******************************************************************************
 *	                      Function: plotFilledBox                             *
 *****************************************************************************/
void plotFilledBox(UINT16 *base, int x1, int x2, int y, int height);

/******************************************************************************
 *	                      Function: plotIndexedBitmap8                        *
 *****************************************************************************/
void plotIndexedBitmap8(UINT8 *base, int x, int y, int height, int index, 
                    const UINT8 *bitmap);

/******************************************************************************
 *	                  Function: plotBitmap16ToBlack                           *
 *****************************************************************************/
void plotBitmap16ToBlack(UINT16 *base, int x, int y, int height, 
							const UINT16 *bitmap);

/******************************************************************************
 *	                     Function: plotBitmap16ToWhite                        *
 * ***************************************************************************/
void plotBitmap16ToWhite(UINT16 *base, int x, int y, int height, 
                    const UINT16 *bitmap);

/******************************************************************************
 *	                  Function: plotIndexedBitmap16ToBlack                    *
 *****************************************************************************/
void plotIndexedBitmap16ToBlack(UINT16 *base, int x, int y, int height, 
                            int index, const UINT16 *bitmap);

/******************************************************************************
 *	                        Function: plotBitmap48                            *
 *****************************************************************************/
void plotBitmap48(UINT32 *base, int x, int y, int height, 
                const UINT32 *bitmap);

/******************************************************************************
 *	                       Function: plotBitmap192                            *
 *****************************************************************************/
void plotBitmap192(UINT32 *base, int x, int y, int height, 
                const UINT32 *bitmap);

/******************************************************************************
 *	                        Function: plotBitmap640                           *  
 *****************************************************************************/
void plotBitmap640(UINT32 *base, int height, const UINT32 *bitmap);


#endif
