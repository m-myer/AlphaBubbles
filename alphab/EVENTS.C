/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  events.c                                                        *
******************************************************************************/

#include "events.h"



/******************************************************************************
 *	Function: startGame                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Calls the model initialization function at the start of a new game.   *
 *                                                                            *
 *	Calls:                                                                    *
 * 		initializeGame()                                                      *
 *                                                                            *
 *****************************************************************************/
void startGame(Model *model)
{
	initializeGame(model);

	return;
}





/* ========================================================================== *
 *                                                                            *
 *                           Synchronous Functions                            *
 *                                                                            *
 * ========================================================================== *

/******************************************************************************
 *	Function: bubblesFall                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	 Moves every active bubble in the play area.                          *
 *                                                                            *
 *	Calls:                                                                    *
 * 		moveBubble()                                                          *
 * 		hasChanged()                                                          *
 *                                                                            *
 *****************************************************************************/
void bubblesFall(Model *model)
{
    int i;
    int moved = 0;
    
    for (i = 0;i < MAX_BUBBLES && moved < model->tray.activeBubbles; i++) 
    {
		if (model->tray.bubbles[i].alive == true) 
		{
			moveBubble(model, &model->tray.bubbles[i]);
			moved++;
		}
    } 
    
	if (moved > 0)
		hasChanged(model);
	
    return;
}

/******************************************************************************
 *	Function: addBubble                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	 Adds a new bubble to the play area.                                  *
 *                                                                            *
 *	Details:                                                                  *
 *		Calls the model to generate a new bubble if the current active number *
 * 		of bubbles is below the maximum. Searches through the bubble array    *
 * 		for the first available inactive bubble to be spawned.                *
 *                                                                            *
 *	Calls:                                                                    *
 * 		generateBubble()                                                      *
 * 		hasChanged()                                                          *
 *                                                                            *
 *****************************************************************************/
void addBubble(Model *model, int random)
{
	int i = 0;

	if (model->tray.activeBubbles < MAX_BUBBLES) 
	{
		while (i < MAX_BUBBLES && model->tray.bubbles[i].active == true) 
			i++;
		
		if (i < MAX_BUBBLES)
		{
		    generateBubble(&model->tray, &model->tray.bubbles[i], 
		    			model->pBar.difficulty, random);
			playSpawn();
			hasChanged(model);
		}
	}
	
	return;
}

/******************************************************************************
 *	Function: bubblesMidPopping                                               *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Decrements the timer for bubbles that are popping, clearing those     *
 * 		that have finished their popping animation.                           *
 *                                                                            *
 *	Calls:                                                                    *
 * 		countDownPop()                                                        *
 * 		clearBubble()                                                         *
 * 		hasChanged()                                                          *
 *                                                                            *
 *****************************************************************************/
void bubblesMidPopping(Model *model)
{
	int i = 0;
	int checked = 0;

	for (i = 0; i < MAX_BUBBLES && checked < model->tray.bubblesMidPop; i++)
	{
		if (model->tray.bubbles[i].active == true && 
			model->tray.bubbles[i].alive == false) 
		{
			countDownPop(&model->tray.bubbles[i]);
			
			if (model->tray.bubbles[i].popCountDown == 30 || 
				model->tray.bubbles[i].popCountDown == 20)
				{
					model->tray.renderBubbles = true;
					hasChanged(model);
				}
				
			if (model->tray.bubbles[i].popCountDown == 0) 
			{
				clearBubble(&model->tray, &model->tray.bubbles[i]);
				hasChanged(model);
			}
			checked++;
		}
	}
	
	return;
}





/* ========================================================================== *
 *                                                                            *
 *                          Asynchronous Functions                            *
 *                                                                            *
 * ========================================================================== *

/******************************************************************************
 *	Function: userInput                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	 Checks the user input for any matching bubbles.                      *
 *                                                                            *
 *	Details:                                                                  *
 *		Passes the user input character to the model for comparison with any  *
 *		active bubbles. If the model returns the index of a match, sends the  *
 *		corresponding bubble to the matchMade function.                       *
 *                                                                            *
 *	Calls:                                                                    *
 * 		checkMatch()                                                          *
 * 		matchMade()                                                           *
 * 		hasChanged()                                                          *
 *                                                                            *
 *****************************************************************************/
void userInput(Model *model, char input)
{
    int matchingBubble;
    
    matchingBubble = checkForMatch(&model->tray, input);

    if (matchingBubble != -1) 
	{
		matchMade(&model->tray, &model->tray.bubbles[matchingBubble], 
				&model->pBar, &model->sTable);
		hasChanged(model);
	}
    return;
}

/******************************************************************************
 *	Function: matchMade                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	 Changes the model to reflect the user successfully popping a bubble. *
 *                                                                            *
 *	Details:                                                                  *
 *		Pops the matching bubble, increases the score, and increases the      *
 * 		progress level in the model on a match. Calls a function to handle    *
 * 		an increase in difficulty if the progress bar becomes filled.         * 
 *                                                                            *
 *	Calls:                                                                    *
 * 		popBubble()                                                           *
 * 		increaseScore()                                                       *
 * 		increaseProgress()                                                    *
 * 		progressBarFilled()                                                   *
 *                                                                            *
 *****************************************************************************/
void matchMade(BubbleTray *tray, Bubble *bubble, ProgressBar *pBar, 
			ScoreTable *sTable)
{	
    popBubble(tray, bubble);
	playPop();
	increaseScore(sTable);
	increaseProgress(pBar);
	
	if (pBar->progress >= MAX_PROGRESS) 
		progressBarFilled(tray, pBar, sTable);
	
	return;
}

/******************************************************************************
 *	Function: progressBarFilled                                               *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	 Changes the difficulty settings in the model and resets the progress.*
 *                                                                            *
 *	Calls:                                                                    *
 * 		increaseDifficulty()                                                  *
 * 		setFallSpeed()                                                        *
 * 		resetProgress()                                                       *
 *                                                                            *
 *****************************************************************************/
void progressBarFilled(BubbleTray *tray, ProgressBar *pBar, ScoreTable *sTable)
{
	if (pBar->difficulty != MAX_DIFFICULTY)
	{
		increaseDifficulty(pBar);
		raiseLod(tray);
		playChime();
	}
	else
	{
		bonusPoints(sTable);
	}
	resetProgress(pBar);

	
	return;
}





/* ========================================================================== *
 *                                                                            *
 *                           Render Flag Functions                            *
 *                                                                            *
 * ========================================================================== *

/******************************************************************************
 *	Function: hasChanged                                                      *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Calls the model to set its global render flag, signifying one or more *
 		more of its values have changed.                                      *
 *                                                                            *
 *****************************************************************************/
void hasChanged(Model *model)
{
	setRender(model);
	
	return;
}

/******************************************************************************
 *	Function: hasRendered                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Calls the model to clear its global render flag, signifying that the  *
 * 		most recent changes have been rendered.                               *
 *                                                                            *
 *****************************************************************************/
void hasRendered(Model *model)
{
	resetRender(model);
	
	return;
}
