/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  raster.c                                                        *
******************************************************************************/

#include <osbind.h>
#include <stdio.h>
#include "raster.h"


/******************************************************************************
 *	                       Function: getVideoBase                             *
 *****************************************************************************/
UINT32 *getVideoBase()
{
	UINT8 *videoHigh = VIDEO_REG_HIGH;
	UINT8 *videoMid = VIDEO_REG_MID;
	UINT32 base;
	UINT32 *basePtr;
	long old_ssp = Super(0);
	
	base = ( (UINT32) *videoHigh << 16);
	base |= ( (UINT32) *videoMid << 8);
	
	Super(old_ssp);
	
	basePtr = (UINT32 *)base;
	
	return basePtr;
}

/******************************************************************************
 *	                       Function: setVideoBase                             *
 *****************************************************************************/
void setVideoBase(UINT32 *base)
{
	UINT32 shift = (UINT32)base >> 8;
	UINT16 newBase = (UINT16)shift;
	long oldSsp = Super(0);
	
	setVBase(newBase);
	
	Super(oldSsp);
	
	return;
}

/******************************************************************************
 *	                        Function: clearScreen                             *
 *****************************************************************************/
void clearScreen(UINT32 *base)
{
	int i, ii;
	
	for (i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (ii = 0; ii < 20; ii++)
		{
			*(base + ii + (i * 20)) = CLEAR32;
		}
	}
	
	return;
}

/******************************************************************************
 *	Function: clearBox                                                        *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets a specific section of the screen buffer to white.                *
 *                                                                            *
 *****************************************************************************/
void clearBox(UINT8 *base, int x1, int x2, int y, int height)
{
	int row1, row2, i, ii;
	UINT8 *place = base + y * 80;
	row1 = x1 >> 3;
	row2 = x2 >> 3;
	
	if (row1 == row2)
	{
		for (i = 0; i < height; i++)
			*(place + row1 + (i * 80)) = CLEAR8;
	}
	else
	{
		for (i = 0; i < height; i++)
		{
			for (ii = row1; ii <= row2; ii++)
				*(place + ii + (i * 80)) = CLEAR8;
		}
	}
	
	return;
}

/******************************************************************************
 *	Function: plotFilledBox                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *		Sets a specific section of the screen buffer to black.                *
 *                                                                            *
 *****************************************************************************/
void plotFilledBox(UINT16 *base, int x1, int x2, int y, int height)
{
	UINT16 p1, p2;
	int row1, row2, i, ii;
	int shift_F, shift_B;
	UINT16 *place = base + y * 40;
	row1 = x1 >> 4;
	row2 = x2 >> 4;
	shift_F = x1 & (BITS_IN_WORD - 1);
	shift_B = (BITS_IN_WORD - 1) - (x2 & (BITS_IN_WORD - 1));
	
	p1 = SOLID16 >> shift_F;		
	p2 = SOLID16 << shift_B;
	
	if (row1 == row2)
	{
		for (i = 0; i < height; i++)
		{
			*(place + row1 + (i * 40)) |= p1 & p2;
		}
	}		
	else
	{
		for (i = 0; i < height; i++)
		{
			*(place + row1 + (i * 40)) |= p1;

			for (ii = row1 + 1; ii < row2; ii++)
			{
				*(place + ii + (i * 40)) = SOLID16;
			}

			*(place + row2 + (i * 40)) |= p2;
		}
	}
	
	return;
}

/******************************************************************************
 *	Function: plotIndexedBitmap8                                              *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets a specific section of the screen buffer to the value of a given  *
 *      8 pixel wide bitmap.                                                  *
 *                                                                            *
 *  Assumptions:                                                              *
 *      Each "row" in the bitmap will be 8 pixels wide stored in an array     *
 *      starting at the given index.                                          *
 *                                                                            *
 *****************************************************************************/
void plotIndexedBitmap8(UINT8 *base, int x, int y, int height, int index, 
					const UINT8 *bitmap)
{
	int i, ii, offset, shift_F, shift_B;
	offset = (x >> 3) + (y * 80);
	shift_F = x & (BITS_IN_BYTE - 1);
	shift_B = (BITS_IN_BYTE - 1) - (x & (BITS_IN_BYTE - 1));

	for (i = 0; i < height; i++)
	{
		*(base + offset + (i * 80)) ^= (bitmap[index] >> shift_F);
		*(base + offset + 1 + (i * 80)) ^= (bitmap[index] << shift_B);
		index++;
	}
	
	return;
}

/******************************************************************************
 *	Function: plotBitmap16ToBlack                                            *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets a specific section of the screen buffer to the value of a given  *
 *      16 pixel wide bitmap.                                                 *
 *                                                                            *
 *  Assumptions:                                                              *
 *      Each "row" in the bitmap will be 16 pixels wide.                      *
 *      The section of the screen buffer being set is currently set to 1.     *
 *                                                                            *
 *****************************************************************************/
void plotBitmap16ToBlack(UINT16 *base, int x, int y, int height, 
							const UINT16 *bitmap)
{
	int i, ii, offset, shift_F, shift_B;
	offset = (x >> 4) + (y * 40);
	shift_F = x & (BITS_IN_WORD - 1);
	shift_B = (BITS_IN_WORD - 1) - (x & (BITS_IN_WORD - 1));

	for (i = 0; i < height; i++)
	{
		*(base + offset + (i * 40)) |= ((bitmap[i]) >> shift_F);
		*(base + offset + 1 + (i * 40)) |= ((bitmap[i]) << shift_B);
	}
	
	return;
}

/******************************************************************************
 *	Function: plotBitmap16ToWhite                                             *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets a specific section of the screen buffer to the value of a given  *
 *      16 pixel wide bitmap.                                                 *
 *                                                                            *
 *  Assumptions:                                                              *
 *      Each "row" in the bitmap will be 16 pixels wide.                      *
 *      The section of the screen buffer being set is currently set to 0.     *
 *                                                                            *
 *****************************************************************************/
void plotBitmap16ToWhite(UINT16 *base, int x, int y, int height, 
					const UINT16 *bitmap)
{
	int i, offset, shift_F, shift_B;
	offset = (x >> 4) + (y * 40);
	shift_F = x & (BITS_IN_WORD - 1);
	shift_B = (BITS_IN_WORD) - (x & (BITS_IN_WORD - 1));

	for (i = 0; i < height; i++)
	{
		*(base + offset + (i * 40)) |= (~(bitmap[i]) >> shift_F);
	
		*(base + offset + 1 + (i * 40)) |= (~(bitmap[i]) << shift_B);
	}
	
	return;
}

/******************************************************************************
 *  Function: plotIndexedBitmap16ToBlack                                      *
 *                                                                            *
 *  Purpose:                                                                  *
 *      Sets a specific section of the screen buffer to the value of a given  *
 *      16 pixel wide bitmap.                                                 *
 *                                                                            *
 *  Assumptions:                                                              *
 *      Each "row" in the bitmap will be 16 pixels wide, stored in an array   *
 *      starting at the given index.                                          *
 *                                                                            *
 *****************************************************************************/
void plotIndexedBitmap16ToBlack(UINT16 *base, int x, int y, int height, 
							int index, const UINT16 *bitmap)
{
	int i, ii, offset, shift_F, shift_B;
	offset = (x >> 4) + (y * 40);
	shift_F = x & (BITS_IN_WORD - 1);
	shift_B = (BITS_IN_WORD - 1) - (x & (BITS_IN_WORD - 1));

	for (i = 0; i < height; i++)
	{
		*(base + offset + (i * 40)) ^= (~(bitmap[index]) >> shift_F);
		*(base + offset + 1 + (i * 40)) ^= (~(bitmap[index]) << shift_B);
		index++;
	}
	
	return;
}

/******************************************************************************
 *	Function: plotBitmap48                                                    *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets a specific section of the sceen buffer to the value of a given   *
 *      48 pixel wide bitmap.                                                 *
 *                                                                            *
 * Assumptions:                                                               *
 *      One row of the bitmap is made up by two elements in the bitmap array. *                                                               * 
 *      Each array element contains a 32 pixel wide piece of the bitmap.      *
 *                                                                            *
 *****************************************************************************/
void plotBitmap48(UINT32 *base, int x, int y, int height, const UINT32 *bitmap)
{
	int i, ii, index, offset, shift_F, shift_B;
	index = 0;
	offset = (x >> 5) + (y * 20);
	shift_F = x & (BITS_IN_LONG - 1);
	shift_B = (BITS_IN_LONG - 1) - (x & (BITS_IN_LONG - 1));

	for (i = 0; i < height; i++)
	{
		*(base + offset + (i * 20)) |= (bitmap[index] >> shift_F);
	
		*(base + offset + 1 + (i * 20)) |= (bitmap[index] << shift_B);
		index++;
		*(base + offset + 1 + (i * 20)) |= (bitmap[index] >> shift_F);
	
		*(base + offset + 2 + (i * 20)) |= (bitmap[index] << shift_B);
		index++;	

	}
	
	return;
}

/******************************************************************************
 *	Function: plotBitmap192                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *      Sets a specific section of the screen buffer to the value of a given  *
 *      192 pixel wide bitmap.                                                *
 *                                                                            *
 *  Assumptions:                                                              *
 *      One row of the bitmap is made up by six elements in the bitmap array. *
 *      Each array element contains a 32 pixel wide piece of the bitmap.      *
 *                                                                            *
 *****************************************************************************/
void plotBitmap192(UINT32 *base, int x, int y, int height, 
				const UINT32 *bitmap)
{
	int i, ii, index, offset, shift_F, shift_B;
	index = 0;
	offset = (x >> 5) + (y * 20);
	shift_F = x & (BITS_IN_LONG - 1);
	shift_B = (BITS_IN_LONG - 1) - (x & (BITS_IN_LONG-2));

	for (i = 0; i < height; i++)
	{
		*(base + offset + (i * 20)) ^= (~(bitmap[index]) >> shift_F);
	
		for (ii = 1; ii < 6; ii ++)
		{
		*(base + offset + ii + (i * 20)) = (bitmap[index] << shift_B);
		index++;
		*(base + offset + ii + (i * 20)) |= (bitmap[index] >> shift_F);

		}
	
		*(base + offset + 6 + (i * 20)) ^= (~(bitmap[index]) << shift_B);
		index++;	

	}
	
	return;
}

/******************************************************************************
 *	Function: plotBitmap640                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *      Sets the screen buffer to the value of a given 640 pixel wide bitmap. *
 *                                                                            *
 *  Assumptions:                                                              *
 *      The screen buffer has been cleared.                                   *
 *      One row of the bitmap is made up by 20 elements in the bitmap array.  *
 *      Each array element contains a 32 pixel wide piece of the bitmap.      *
 *                                                                            *
 *****************************************************************************/
void plotBitmap640(UINT32 *base, int height, const UINT32 *bitmap)
{
	int i, ii, index;
	index = 0;

	for (i = 0; i < height; i++)
	{
		for (ii = 0; ii < 20; ii ++)
		{
		*(base + ii + (i * 20)) = bitmap[index];
		index++;
		}
	}
	
	return;
}

