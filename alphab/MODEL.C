/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  model.c                                                         *
******************************************************************************/

#include "model.h"


/* ========================================================================== *
 *                                                                            *
 *                                Constants                                   *
 *                                                                            *
 * ==========================================================================*/

const char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
			'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z'};

const int colX[] = {8, 56, 104, 152, 200, 248, 296, 344};

const int progBubbX[] ={417, 434, 451, 468, 485, 502, 519, 536, 553, 570, 587};





/* ========================================================================== *
 *                                                                            *
 *                         Initialization Functions                           *
 *                                                                            *
 * ========================================================================== *

/******************************************************************************
 *	                        Function: initializeGame                          *
 *****************************************************************************/
void initializeGame(Model *model)
{
	model->gameOver = false;
	model->render = false;
	initializeTray(&model->tray);
	initializeProgressBar(&model->pBar);
	initializeLivesCounter(&model->lCount);
	initializeScoreTable(&model->sTable);
	
	return;
}

/******************************************************************************
 *	                        Function: initializeTray                          *
 *****************************************************************************/
void initializeTray(BubbleTray *tray)
{
	initializeBubbles(tray->bubbles); 
	tray->lod.x = LOD_X;
	tray->lod.y = LOD_START_Y;
	tray->activeBubbles = 0;
	tray->firstRow = 0;
	tray->fallSpeed = BUBBLE_SPEED;
	tray->bubblesMidPop = 0;
	tray->renderBubbles = false;
	tray->renderLod = false;
	
	return;
}

/******************************************************************************
 *	                        Function: initializeBubbles                       *
 *****************************************************************************/
void initializeBubbles(Bubble *bubbles)
{
	int i;
	
	for (i = 0; i < MAX_BUBBLES; i++)
	{
	    bubbles[i].x = 0;
	    bubbles[i].y = 0;
	    bubbles[i].hitY = 0;
	    bubbles[i].column = 0;
	    bubbles[i].active = false;
	    bubbles[i].alive = false;
	    bubbles[i].letter = EMPTY;
	    bubbles[i].letterIndex = 0;
	    bubbles[i].popCountDown = 0;
	}
	
	return;
}

/******************************************************************************
 *	                    Function: initializeProgressBar                       *
 *****************************************************************************/
void initializeProgressBar(ProgressBar *pBar)
{
	pBar->x = PROG_BAR_X;
	pBar->y = PROG_BAR_Y;
	pBar->progress = 0;
	pBar->difficulty = 1;
	pBar->render = false;
	
	return;
}

/******************************************************************************
 *	                    Function: initializeLivesCounter                      *
 *****************************************************************************/
void initializeLivesCounter(LivesCounter *lCount)
{
	lCount->x = LIVES_X;
	lCount->y = LIVES_Y;
	lCount->lives = MAX_LIVES;
	lCount->render = false;
	
	return;
}

/******************************************************************************
 *	                    Function: initializeScoreTable                        *
 *****************************************************************************/
void initializeScoreTable(ScoreTable *sTable)
{
	sTable->digits[0].x = ONES_X;
	sTable->digits[0].y = DIGITS_Y;
	sTable->digits[0].value = 0;
	sTable->digits[1].x = TENS_X;
	sTable->digits[1].y = DIGITS_Y;
	sTable->digits[1].value = 0;
	sTable->digits[2].x = HUNDREDS_X;
	sTable->digits[2].y = DIGITS_Y;
	sTable->digits[2].value = 0;
	sTable->score = 0;
	sTable->render = false;
	
	return;
}





/* ========================================================================== *
 *                                                                            *
 *                         Bubble Tray Functions                              *
 *                                                                            *
 * ========================================================================== *


 /*****************************************************************************
 *	Function: generateBubble                                                  *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the values for a bubble to appear in the play area.              *
 *                                                                            *
 *	Details:                                                                  *
 *		Initializes a new bubble to appear in the play area if the number of  *
 *      active bubbles does not exceed the maximum and there is space in one  *
 * 		of the columns along the top row. The column and letter values are    * 
 * 		randomly generated for each new bubble.                               *
 *                                                                            *
 *	Calls:                                                                    *
 * 		getColumn()                                                           *
 *                                                                            *
 *****************************************************************************/
void generateBubble(BubbleTray *tray, struct Bubble *bubble,
		    int difficulty, int random)
{
    int column;
	int letterIndex;

    if (tray->firstRow < 8)
    {
		column = getColumn(tray, random);
		letterIndex = random % NUM_LETTERS;
	
		bubble->x = colX[column];
		bubble->y = BUBBLE_SPAWN_Y;
		bubble->hitY = BUBBLE_SPAWN_HIT;
		bubble->column = column;
		bubble->letter = letters[letterIndex];
		bubble->letterIndex = letterIndex;
		bubble->active = true;
		bubble->alive = true;
		bubble->popCountDown = 0;
		tray->activeBubbles += 1;
		tray->firstRow += 1;
		tray->renderBubbles = true;
    }
    
    return;
}

/******************************************************************************
 *	Function: getColumn                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Randomly generates a column index that does not currently contain a   * 
 *      Bubble in the first row.                                              *
 *                                                                            *
 *	Details:                                                                  *
 *		Generates a value from 0-7. If there is at least one active bubble in *
 * 		the play area, checks if there is an active bubble in the first row   *
 * 		of that column. Continues generating column values until an empty     *
 * 		column is found.                                                      *
 *                                                                            *
 *	Calls:                                                                    *
 * 		checkColumn()                                                         *
 *                                                                            *
 * 	Returns:                                                                  *
 * 		int column - the index of a column with an empty first row.           *
 *                                                                            *
 *****************************************************************************/
int getColumn(BubbleTray *tray, int random)
{
	int column;
	int i = 1;
	bool valid = false;

	column = random & NUM_COLMNS - 1;

	if (tray->firstRow != 0)
	{
	    valid = checkColumn(tray->bubbles, tray->activeBubbles, column);
	
	    while (valid == false)
	    {
			column = (random + i++) & NUM_COLMNS - 1;
			valid = checkColumn(tray->bubbles, tray->activeBubbles, column);
	    }
	}
	
	return column;
}

/******************************************************************************
 *	Function: checkColumn                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Determines whether a Bubble already exists within the first row of a  *
 * 		column inside the play area.                                          *
 *                                                                            *
 *	Details:                                                                  *
 *		Searches the bubble array for any active bubbles in the same column   *
 * 		as the one which was passed, and checks their y values. The function  *
 * 		will continue searching through the array for as many active bubbles  *
 * 		as there are in the play area. Any bubble with a y coor that is < 51  *
 * 		is considered to be in the first row. Sets valid to false on a match. *
 *                                                                            *
 * 	Returns:                                                                  *
 * 		bool valid - returns true if no active bubble was found in the given  *
 * 					 column.                                                  *
 *                                                                            *
 *****************************************************************************/
bool checkColumn(Bubble *bubbles, int activeBubbles, int column)
{
	int checked = 0;
	int i = 0;
	bool valid = true;

	while (checked < activeBubbles && valid == true)
	{
	    if (bubbles[i].active == true)
	    {
			if (bubbles[i].column == column && bubbles[i].y <= 51)
					valid = false;

			checked++;
	    }

	    i++;
	}
	
	return valid;
}

/******************************************************************************
 *	Function: moveBubble                                                      *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Moves a bubble down the play area.                                    *
 *                                                                            *
  *	Details:                                                                  *
 *		Increases the y coor of the given bubble by 2. Compares the hitbox    *
 * 		coord of the bubble after moving with the line of death to detect a   *
 * 		collision.                                                            *
 *                                                                            *
 *	Calls:                                                                    *
 * 		popBubble()                                                           *
 * 		loseLife()                                                            *
 *                                                                            *
 *****************************************************************************/
void moveBubble(Model *model, Bubble *bubble)
{
	bubble->y += 2;
	bubble->hitY += 2;

	if (bubble->y == 52)
	  model->tray.firstRow -= 1;
	
	if (bubble->hitY >= model->tray.lod.y) 
	{	
		popBubble(&model->tray, bubble);
		loseLife(&model->lCount);
		
		if (model->lCount.lives == 0)
			model->gameOver = true;
	}
	
	model->tray.renderBubbles = true;
	
	return;		
}

/******************************************************************************
 *	Function: setFallSpeed                                                    *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the fall speed of the bubble tray based on the current           *
 * 		difficulty level.                                                     *
 *                                                                            *
 *****************************************************************************/
void setFallSpeed(BubbleTray *tray, int difficulty)
{
	tray->fallSpeed += 10;

	return;
}

/******************************************************************************
 *  Function: raiseLod                                                        *
 *                                                                            *
 *  Purpose:                                                                  *
 * 		Raises the "line of death" in the play area                           *
 *                                                                            *
 *****************************************************************************/
void raiseLod(BubbleTray *tray)
{
	tray->lod.y -= LOD_RAISE;
	tray->renderLod = true;
	
	return;
}

/******************************************************************************
 *	Function: checkForMatch                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Determines whether the user input character matches any of the active *
 * 		bubbles' letter.                                                      *
 *                                                                            *
 * 	Details:                                                                  *
 * 		Inspects the bubbles inside the bubble tray's bubble array comparing  *
 * 		each Bubble's letter to the user input. The function will continue    *
 * 		searching through the array for as many active bubbles as there are   *
 * 		in the play area. On a match, sets int match to the index of the      *
 * 		matching bubble. If a match was already found with a previous bubble  *
 * 		(match != -1), compares the y coordinate of both bubbles and sets     *
 * 		match equal to the greater of the two. Match is set by default to -1, *
 * 		signifying no match found.                                            *                          
 *                                                                            *
 * 	Returns:                                                                  *
 * 		int match - match contains the index of a matching bubble in the      *
 * 					array or a -1 if no match found.                          *
 *                                                                            *
 *****************************************************************************/
int checkForMatch(BubbleTray *tray, char input)
{
	int i;
	int checked = 0;
	int match = -1;
	
	for (i = 0; i < MAX_BUBBLES && checked < tray->activeBubbles; i++)
	{
	    if (tray->bubbles[i].alive == true && 
		tray->bubbles[i].letter == input)
	    {
			if (match == -1)
				match = i;
			else if (tray->bubbles[i].y > tray->bubbles[match].y)
				match = i;

		checked++;
	    }
	}
	
	return match;
}

/******************************************************************************
 *	Function: popBubble                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the bubble tray to reflect a bubble having popped.               *
 * 	                                                                          *
 *	Details:                                                                  *
 * 		Changes a bubble's alive status to false and sets the popping         *
 * 		countdown.                                                            *                     
 *                                                                            *
 *****************************************************************************/
void popBubble(BubbleTray *tray, Bubble *bubble)
{
    bubble->alive = false;
	bubble->popCountDown = POP_DURATION;
	tray->bubblesMidPop += 1;
	tray->renderBubbles = true;
	
	return;
}

/******************************************************************************
 *	Function: countDownPop                                                    *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Decrements the timer for a bubble's popping animation to persist.     *
 *                                                                            *
 *****************************************************************************/
void countDownPop(Bubble *bubble)
{
	bubble->popCountDown -= 1;	
	
	return;
}

/******************************************************************************
 *	Function: clearBubble                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Removes a bubble from the play area.                                  *
 *                                                                            *
 *****************************************************************************/
void clearBubble(BubbleTray *tray, Bubble *bubble)
{
    bubble->active = false;
	bubble->popCountDown = 0;
	tray->activeBubbles -= 1;
	tray->bubblesMidPop -= 1;

	if (bubble->y <= 51)
	    tray->firstRow -= 1;
	
	tray->renderBubbles = true;
	
	return;
}





/* ========================================================================== *
 *                                                                            *
 *                         Progress Bar Functions                             *
 *                                                                            *
 * ========================================================================== *


/******************************************************************************
 *	Function: increaseProgress                                                *
 *                                                                            *
 *	Purpose:                                                                  *
 *		Increases the game's current progress level by 1.                     *
 *                                                                            *
 *****************************************************************************/
void increaseProgress(ProgressBar *pBar)
{
	pBar->progress += 1;
	pBar->render = true;
	
	return;
}

/******************************************************************************
 *	Function: increaseDifficulty                                              *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Increases the game's current difficulty level by 1.                   *
 *                                                                            *
 *****************************************************************************/
void increaseDifficulty(ProgressBar *pBar)
{
	pBar->difficulty += 1;
	
	if (pBar->difficulty & 2 == 0)
	
	
	return;
}

/******************************************************************************
 *	Function: resetProgress                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the progress bar back to 0.                                      *
 *                                                                            *
 *****************************************************************************/
void resetProgress(ProgressBar *pBar)
{
	pBar->progress = 0;
	
	return;
}





/* ========================================================================== *
 *                                                                            *
 *                         Score Table Functions                              *
 *                                                                            *
 * ========================================================================== *


/******************************************************************************
 *	Function: increaseScore                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Increases the game's current score by 1.                              *
 *                                                                            *
 *****************************************************************************/
void increaseScore(ScoreTable *sTable )
{
	sTable->score += 1;
	sTable->digits[0].value = sTable->score % 10;
	sTable->digits[1].value = (sTable->score % 100) / 10;
	sTable->digits[2].value = sTable->score / 100;
	sTable->render = true;
	
	return;
}

/******************************************************************************
 *	Function: bonusPoints                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Increases the game's current score by 5.                              *
 *                                                                            *
 *	Details:                                                                  *
 * 		Activated for every filled progress bar once the maximum difficulty   *
 *      level has been reached.                                               *
 *                                                                            *
 *****************************************************************************/
void bonusPoints(ScoreTable *sTable)
{
	sTable->score += 5;
	sTable->digits[0].value = sTable->score % 10;
	sTable->digits[1].value = (sTable->score % 100) / 10;
	sTable->digits[2].value = sTable->score / 100;
	sTable->render = true;
	
	return;
}




/* ========================================================================== *
 *                                                                            *
 *                         Life Counter Functions                             *
 *                                                                            *
 * ========================================================================== *


/******************************************************************************
 *	Function: loseLife                                                        *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Decrements the game's life count by 1.                                *
 *                                                                            *
 *****************************************************************************/
void loseLife(LivesCounter *lCount)
{
	lCount->lives -= 1;
	lCount->render = true;
	
	return;
}





/* ========================================================================== *
 *                                                                            *
 *                         Render Flag Functions                              *
 *                                                                            *
 * ========================================================================== *


 /*****************************************************************************
 *	Function: setRender                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets render flag of the game model to true.                           *
 *                                                                            *
 *****************************************************************************/
void setRender(Model *model)
{
	model->render = true;
	
	return;
}

/******************************************************************************
 *	Function: resetRender                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the render flags of the game model and all the game's structures *
 * 		to false;                                                             *
 *                                                                            *
 *****************************************************************************/
void resetRender(Model *model)
{
	model->render = false;
	model->tray.renderBubbles = false;
	model->tray.renderLod = false;
	model->pBar.render = false;
	model->lCount.render = false;
	model->sTable.render = false;
	
	return;
}

