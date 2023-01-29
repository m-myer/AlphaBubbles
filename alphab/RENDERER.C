/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  renderer.c                                                      *
******************************************************************************/

#include "renderer.h"


/******************************************************************************
 *	                          Function: render                                *
 *****************************************************************************/
void render(UINT32 *base, const Model *model)
{
	if (model->tray.renderBubbles == true)
	{	
		renderBubbles(base, &model->tray);
		renderPopping(base, &model->tray);
	}
	
	if (model->tray.renderLod == true)
		renderLod((UINT16 *)base, &model->tray.lod);
	
	if (model->pBar.render == true)
		renderProgress(base, &model->pBar);	
	
	if (model->lCount.render == true)
		renderLives(base, &model->lCount);
	
	if (model->sTable.render == true)
		renderScore((UINT16 *)base, &model->sTable);

	return;
}

/******************************************************************************
 *	                      Function: renderSnapshot                            *
 *****************************************************************************/
void renderSnapshot(UINT32 *base, const Model *model)
{
	if (model->tray.renderLod == true)
		renderLod((UINT16 *)base, &model->tray.lod);
	
	if (model->pBar.render == true)
		renderProgress(base, &model->pBar);	
	
	if (model->lCount.render == true)
		renderLives(base, &model->lCount);
	
	if (model->sTable.render == true)
		renderScore((UINT16 *)base, &model->sTable);

	return;
}


/******************************************************************************
 *	                      Function: renderMainMenu                            *
 *****************************************************************************/
void renderMainMenu(UINT32 *base)
{
	clearScreen(base);
	plotBitmap640(base, SCREEN_HEIGHT, splashScreen);
	
	return;
}


/******************************************************************************
 *	                      Function: renderGameScreen                          *
 *****************************************************************************/
void renderGameScreen(UINT32 *base)
{
	clearScreen(base);
	plotBitmap640(base, SCREEN_HEIGHT, gameScreen);
	plotFilledBox((UINT16 *)base, PROG_BAR_X, PROG_BAR_X + 192, PROG_BAR_Y, 
				64);
	plotBitmap192(base, PROG_BAR_X, PROG_BAR_Y, 64, progBarMap);

	return;
}



/******************************************************************************
 *	                       Function: renderBubbles                            *
 *****************************************************************************/
void renderBubbles(UINT32 *base, const BubbleTray *tray)
{
	int printed = 0;
	int i = 0;
	int letterX;
	int letterY;
	int letterIndex;
	
	for (i = 0; i < MAX_BUBBLES && printed < tray->activeBubbles; i++)
	{	
		if (tray->bubbles[i].active == true)
		{
			if (tray->bubbles[i].alive == true)
			{
				letterX = tray->bubbles[i].x + 20;
				letterY = tray->bubbles[i].y + 16;
				letterIndex = tray->bubbles[i].letterIndex * 16;

				plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y, 
						BUBBLE_MAP_HEIGHT, bubbleMap);
				plotIndexedBitmap8((UINT8 *)base, letterX, letterY, 
						LETTER_MAP_HEIGHT, letterIndex, letterMaps);
			}
/*			else
			{
				if (tray->bubbles[i].popCountDown > 20)
					plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y,
							BUBBLE_MAP_HEIGHT, popped1Map);
				else if (tray->bubbles[i].popCountDown >12)
					plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y,
							BUBBLE_MAP_HEIGHT, popped2Map);
				else if (tray->bubbles[i].popCountDown > 0)
					plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y,
							BUBBLE_MAP_HEIGHT, popped3Map);
			}*/
		}
	}
	
	return;
}



/******************************************************************************
 *	                      Function: renderPopping                             *
 *****************************************************************************/
void renderPopping(UINT32 *base, const BubbleTray *tray)
{
	int printed = 0;
	int i = 0;
	
	for (i = 0; i < MAX_BUBBLES && printed < tray->bubblesMidPop; i++)
	{	
		if (tray->bubbles[i].active == true)
		{
			if (tray->bubbles[i].alive == false)
			{
				if (tray->bubbles[i].popCountDown > 20)
					plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y,
							BUBBLE_MAP_HEIGHT, popped1Map);
				else if (tray->bubbles[i].popCountDown >10)
					plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y,
							BUBBLE_MAP_HEIGHT, popped2Map);
				else if (tray->bubbles[i].popCountDown > 0)
					plotBitmap48(base, tray->bubbles[i].x, tray->bubbles[i].y,
							BUBBLE_MAP_HEIGHT, popped3Map);
			}
		}
	}
	
	return;
}

/******************************************************************************
 *	                      Function: renderProgress                            *
 *****************************************************************************/
void renderProgress(UINT32 *base, const ProgressBar *pBar)
{
	if (pBar->progress == 0)
	{
		plotFilledBox((UINT16 *)base, PROG_BAR_X, PROG_BAR_X + 192, 
					PROG_BAR_Y, 64);
		plotBitmap192(base, PROG_BAR_X, PROG_BAR_Y, 64, progBarMap);
	}
	else		
		plotBitmap16ToWhite((UINT16 *)base, progBubbX[pBar->progress], 
					PROG_BUBBLE_Y, PROG_BUBBLE_HEIGHT, progBubbleMap);
	
	return;
}



/******************************************************************************
 *	                       Function: renderLives                              *
 *****************************************************************************/
void renderLives(UINT32 *base, const LivesCounter *lCounter)
{
	plotFilledBox((UINT16 *)base, lCounter->x, lCounter->x + LIVES_MAP_WIDTH, 
				lCounter->y, LIVES_MAP_HEIGHT);

	switch (lCounter->lives) 
	{
		case 3:
			plotBitmap192(base, lCounter->x, lCounter->y, LIVES_MAP_HEIGHT, 
					lives3Map);
			break;
		case 2:
			plotBitmap192(base, lCounter->x, lCounter->y, LIVES_MAP_HEIGHT, 
					lives2Map);
			break;
		case 1:
			plotBitmap192(base, lCounter->x, lCounter->y, LIVES_MAP_HEIGHT, 
					lives1Map);
			break;
		case 0:
			plotBitmap192(base, lCounter->x, lCounter->y, LIVES_MAP_HEIGHT, 
					lives0Map);
			break;
	}
	return;
}



/******************************************************************************
 *	                       Function: renderScore                              *
 *****************************************************************************/
void renderScore(UINT16 *base, const ScoreTable *sTable)
{
	plotFilledBox(base, HUNDREDS_X, ONES_X + NUM_MAP_WIDTH, DIGITS_Y, 
			NUM_MAP_HEIGHT);	
	plotIndexedBitmap16ToBlack(base, sTable->digits[2].x, sTable->digits[2].y, 
			NUM_MAP_HEIGHT, sTable->digits[2].value * 50, numberMaps);
	plotIndexedBitmap16ToBlack(base, sTable->digits[1].x, sTable->digits[1].y, 
			NUM_MAP_HEIGHT, sTable->digits[1].value * 50, numberMaps);	
	plotIndexedBitmap16ToBlack(base, sTable->digits[0].x, sTable->digits[0].y, 
			NUM_MAP_HEIGHT, sTable->digits[0].value * 50, numberMaps);
	
	return;
}

/* to be implemented if raising the line of death is implemented */
void renderLod(UINT16 *base, const LineOfDeath *lod)
{
	plotFilledBox(base, lod->x, lod->x + LOD_WIDTH, lod->y, LOD_RAISE);
	
	return;
}


void renderArrow(UINT32 *base, const Menu *menu)
{
	plotBitmap48(base, menu->selectionX, menu->selectionY, ARROW_MAP_HEIGHT, arrowMap);
	
	return;
}

void renderMouse(UINT16 *base, int x, int y) 
{
	/*plotBitmap16ToBlack(base, x, y, MOUSE_HEIGHT, mouseMap);*/
	
	return;
}

void saveMouseBackground(UINT16 *base, int x, int y) 
{
/*	int i, j;

	for(i = 0, j = 0; i < MOUSE_BACKGROUND_SIZE; i++)
	{
		mouseBackground[j++] = *(base + (y + i) * 40 + (x >> 4));
	}
*/
	return;
}

void restoreMouseBackground(UINT16 *base, int x, int y) 
{
/*	int i, j;

	for(i = 0, j = 0; i < MOUSE_BACKGROUND_SIZE; i++)
	{
		*(base + (y + i) * 40 + (x >> 4)) = mouseBackground[j++];
	}
*/
	return;
}

