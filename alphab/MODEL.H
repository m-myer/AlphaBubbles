/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  model.h                                                         *
******************************************************************************/


#ifndef MODEL_H
#define MODEL_H
#include "types.h"


/* ========================================================================== *
 *                                                                            *
 *                                Constants                                   *
 *                                                                            *
 * ==========================================================================*/

#define CLOCK_RATE 70		/* used to calculate fall speed */
/* ========================== Bubble Constants ============================= */
#define MAX_BUBBLES 8		/* max num of bubbles */
#define SPAWN_RATE 175		/* ticks between bubble spawns */
#define BUBBLE_SPAWN_Y 6	/* y coor for spawning bubbles */
#define BUBBLE_SPAWN_HIT 51 /* y coor for spawning bubbles hitbox*/
#define BUBBLE_HEIGHT 48    /* height of bubbles in pixels */
#define BUBBLE_WIDTH 48		/* width of bubbles in pixels */
#define BUBBLE_SPEED 17 	/* times a bubble moves per second */
#define POP_DURATION 19		/* number of clock ticks popping persists */
#define BUBBLE_AREA_X1 8	/* x1 coor of the bubble tray area */
#define BUBBLE_AREA_X2 391	/* x2 coor of the bubble tray area */
#define BUBBLE_AREA_Y 3		/* y coor of the bubble tray area */
#define NUM_COLMNS 8 		/* number of columns in which bubbles spawn */
/* ========================== Letter Constants ============================= */
#define NUM_LETTERS 26
#define EMPTY '0'			/* character of unspawned bubbles */
/* ======================= Line of Death Constants ========================= */
#define LOD_X 3 			/* x coordinate of the line of death */
#define LOD_START_Y 389  	/* starting y coordinate of line of death */
#define LOD_RAISE 32 		/* # pixels line of death raises per diff level */
#define LOD_WIDTH 395		/* width of line of death in pixels */
#define LOD_MAX 128
/* ======================== Progress Bar Constants ========================= */		
#define PROG_BAR_X 423	/* x coor of the progress bar */
#define PROG_BAR_Y 134	/* y coor of the progress bar */
#define PROG_BUBBLE_Y 144	/* y coor of the progress bar bubbles */
#define PROG_BUBBLE_WIDTH 16/* width of progress bar bubbles in pixels */
#define MAX_PROGRESS 11		/* progress level that increases difficulty */
#define MAX_DIFFICULTY 11
/* ======================== Life Counter Constants ========================= */
#define LIVES_X 423			/* x coor of the life counter */
#define LIVES_Y 225			/* y coor of the life counter */
#define MAX_LIVES 3			/* starting number of lives */
/* ========================= Score Table Constants ========================= */
#define HUNDREDS_X 550		/* x coor of the score table's hundreds digit */
#define TENS_X 572			/* x coor of the score table's tens digit */
#define ONES_X 594			/* x coor of the score table's ones digit */
#define DIGITS_Y 322		/* y coor of the score table's digits */
/* ============================= Menu Constants ============================ */
#define ONE_PLAYER_GAME 1
#define TWO_PLAYER_GAME 2
#define EXIT 3
#define WAIT '0'
#define ONE_PLAYER_X 369
#define ONE_PLAYER_Y 203
#define TWO_PLAYER_X 369
#define TWO_PLAYER_Y 239
#define EXIT_X 323
#define EXIT_Y 274

extern const char letters[];
extern const int colX[];
extern const int progBubbX[];




/* ========================================================================== *
 *                                                                            *
 *                                Structures                                  *
 *                                                                            *
 * ==========================================================================*/

typedef struct Bubble
{
    UINT16 x;
    UINT16 y;
    UINT16 hitY;
    int column;
    char letter;
    int letterIndex;
    bool active; 
    bool alive;		/* is it currently visible on the screen */
    int popCountDown;
} Bubble;

typedef struct LineOfDeath
{
	UINT16 x; 
	UINT16 y;
} LineOfDeath;

typedef struct BubbleTray
{
    Bubble bubbles[MAX_BUBBLES];
	LineOfDeath lod;
    int activeBubbles;
    int firstRow; 
    int fallSpeed; 
    int bubblesMidPop;
	bool renderBubbles;
	bool renderLod;
} BubbleTray;

typedef struct ProgressBar
{
	UINT16 x;
	UINT16 y;
	int progress;
	int	difficulty;
	bool render;
} ProgressBar;

typedef struct Life
{
	UINT16 x;
	UINT16 y;
} Life;

typedef struct LivesCounter
{
	UINT16 x;
	UINT16 y;
	int lives;
	bool render;
} LivesCounter;

typedef struct ScoreDigit
{
	UINT16 x;
	UINT16 y;
	int value;
} ScoreDigit;

typedef struct ScoreTable
{
	ScoreDigit digits[3];
	int score;
	bool render;
} ScoreTable;

typedef struct Model
{
	bool gameOver;
	bool render;
	BubbleTray tray;
	ProgressBar pBar;
	LivesCounter lCount;
	ScoreTable sTable;
} Model;

typedef struct Menu
{
	UINT16 selectionX;
	UINT16 selectionY;
	int selection;
	bool inMenu;
	bool quit;
	bool hasChanged;
} Menu;





/* ========================================================================== *
 *                                                                            *
 *                         Initialization Functions                           *
 *                                                                            *
 * ==========================================================================*/


void initializeGame(Model *model);
void initializeTray(BubbleTray *tray);
void initializeBubbles(Bubble *bubbles);
void initializeProgressBar(ProgressBar *pbar);
void initializeLivesCounter(LivesCounter *lCount);
void initializeScoreTable(ScoreTable *sTable);





/* ========================================================================== *
 *                                                                            *
 *                         Bubble Tray Functions                              *
 *                                                                            *
 * ========================================================================== *
 

/******************************************************************************
 *	Function: generateBubble                                                  *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the values for a bubble to appear in the play area.              *
 *                                                                            *
 *****************************************************************************/
void generateBubble(BubbleTray *tray, Bubble *bubble,
		    int difficulty, int random);

/******************************************************************************
 *	Function: getColumn                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Randomly generates a column index that does not currently contain a   * 
 *      Bubble in the first row.                                              *
 *                                                                            *
 *****************************************************************************/
int getColumn(BubbleTray *tray, int random);

/******************************************************************************
 *	Function: checkColumn                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Determines whether a Bubble already exists within the first row of a  *
 * 		column inside the play area.                                          *
 *                                                                            *
 *****************************************************************************/
bool checkColumn(Bubble *bubbles, int activeBubbles, int column);

/******************************************************************************
 *	Function: moveBubble                                                      *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Moves a bubble down the play area.                                    *
 *                                                                            *
 *****************************************************************************/
void moveBubble(Model *model, Bubble *bubble);

/******************************************************************************
 *	Function: setFallSpeed                                                    *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the fall speed of the bubble tray based on the current           *
 * 		difficulty level.                                                     *
 *                                                                            *
 *****************************************************************************/
void setFallSpeed(BubbleTray *tray, int difficulty);

/******************************************************************************
 *  Function: raiseLod                                                        *
 *                                                                            *
 *  Purpose:                                                                  *
 * 		Raises the "line of death" in the play area                           *
 *                                                                            *
 *****************************************************************************/
void raiseLod(BubbleTray *tray);

/******************************************************************************
 *	Function: checkForMatch                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Determines whether the user input character matches any of the active *
 * 		bubbles' letter.                                                      *
 *                                                                            *
 *****************************************************************************/
int checkForMatch(BubbleTray *tray, char input);

/******************************************************************************
 *	Function: popBubble                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the bubble tray to reflect a bubble having popped.               *
 * 	                                                                          *
 *****************************************************************************/
void popBubble(BubbleTray *tray, Bubble *bubble);

/******************************************************************************
 *	Function: countDownPop                                                    *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Decrements the timer for a bubble's popping animation to persist.     *
 *                                                                            *
 *****************************************************************************/
void countDownPop(Bubble *bubble);

/******************************************************************************
 *	Function: clearBubble                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Removes a bubble from the play area.                                  *
 *                                                                            *
 *****************************************************************************/
void clearBubble(BubbleTray *tray, Bubble *bubble);





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
void increaseProgress(ProgressBar *pBar);

/******************************************************************************
 *	Function: increaseDifficulty                                              *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Increases the game's current difficulty level by 1.                   *
 *                                                                            *
 *****************************************************************************/
void increaseDifficulty(ProgressBar *pBar);

/******************************************************************************
 *	Function: resetProgress                                                   *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the progress bar back to 0.                                      *
 *                                                                            *
 *****************************************************************************/
void resetProgress(ProgressBar *pBar);





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
void increaseScore(ScoreTable *sTable);

/******************************************************************************
 *	Function: bonusPoints                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Increases the game's current score by 5.                              *
 *                                                                            *
 *****************************************************************************/
void bonusPoints(ScoreTable *sTable);





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
void loseLife(LivesCounter *lCount);






/* ========================================================================== *
 *                                                                            *
 *                         Render Flag Functions                              *
 *                                                                            *
 * ========================================================================== *
 

/******************************************************************************
 *	Function: setRender                                                       *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets render flag of the game model to true.                           *
 *                                                                            *
 *****************************************************************************/
void setRender(Model *model);

/******************************************************************************
 *	Function: resetRender                                                     *
 *                                                                            *
 *	Purpose:                                                                  *
 *	 	Sets the render flags of the game model and all the game's structures *
 * 		to false;                                                             *
 *                                                                            *
 *****************************************************************************/
void resetRender(Model *model);

#endif
