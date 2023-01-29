/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  renderer.h                                                      *
******************************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "bitmaps.h"
#include "raster.h"
#include "model.h"
#include "screen.h"
#include "splash.h"


/******************************************************************************
 *                                                                            *
 *	Function: render                                                          *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders any aspects of the game model that have updated for the next  *
 * 		frame of animation.                                                   *
 *                                                                            *
 *  Assumptions:                                                              *
 *      The game screen background has already been rendered.                 *
 *                                                                            *
 *****************************************************************************/
void render(UINT32 *base, const Model *model);


/******************************************************************************
 *                                                                            *
 *	Function: renderSnapshot                                                  *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders the background for the game screen.                           *
 *                                                                            *
 *****************************************************************************/
void renderSnapshot(UINT32 *base, const Model *model);


/******************************************************************************
 *                                                                            *
 *	Function: renderMainMenu                                                  *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders the background for the game screen.                           *
 *                                                                            *
 *****************************************************************************/
void renderMainMenu(UINT32 *base);


/******************************************************************************
 *                                                                            *
 *	Function: renderGameScreen                                                *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders the background for the game screen.                           *
 *                                                                            *
 *****************************************************************************/
void renderGameScreen(UINT32 *base);


/******************************************************************************
 *                                                                            *
 *	Function: renderBubbles                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders all of the active bubbles.                                    *
 *                                                                            *
 *****************************************************************************/
void renderBubbles(UINT32 *base, const BubbleTray *tray);

/******************************************************************************
 *                                                                            *
 *	Function: renderPopping                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders all of the popping bubbles.                                   *
 *                                                                            *
 *****************************************************************************/
void renderPopping(UINT32 *base, const BubbleTray *tray);

/******************************************************************************
 *                                                                            *
 *	Function: renderProgress                                                  *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders the progress bar.                                             *
 *                                                                            *
 *****************************************************************************/
void renderProgress(UINT32 *base, const ProgressBar *pBar);


/******************************************************************************
 *                                                                            *
 *	Function: renderLives                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders the life counter.                                             *
 *                                                                            *
 *****************************************************************************/
void renderLives(UINT32 *base, const LivesCounter *lCounter);


/******************************************************************************
 *                                                                            *
 *	Function: renderScore                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Renders the score table digits.                                       *
 *                                                                            *
 *****************************************************************************/
void renderScore(UINT16 *base, const ScoreTable *sTable);

/* to be implemented if raising the line of death is implemented */
void renderLod(UINT16 *base, const LineOfDeath *lod);


void renderArrow(UINT32 *base, const Menu *menu);

/**
 * Plots simple mouse pointer as rectangle
 * 
 * @param base - screen
 * @param x    - x position
 * @param y    - y position
 */
void renderMouse(UINT16 *base, int x, int y);

/**
 * @brief 
 * 
 * @param base 
 * @param x 
 * @param y 
 */
void saveMouseBackground(UINT16 *base, int x, int y);

/**
 * @brief 
 * 
 * @param base 
 * @param x 
 * @param y 
 */
void restoreMouseBackground(UINT16 *base, int x, int y);

#endif
