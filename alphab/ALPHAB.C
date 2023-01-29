/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  alphab.c                                                        *
******************************************************************************/ 

#include "alphab.h"

const UINT32 * const clock = (UINT32 *)0x462;
const UINT8 buffer2[32256]; /* used for double buffering */
const UINT8 snapshotBuffer[32000];

int main()
{

	UINT32 *base1 = getVideoBase();
	UINT32 *base2 = getBuffer();
	UINT32 *baseSnapshot = (UINT32 *)snapshotBuffer;
	
	installVectors();

	mainMenu(base1, base2, baseSnapshot);
	
	clearIkbdBuffer();
	removeVectors();
	
	return 0;
}


/******************************************************************************
 *	                        Function: mainMenu                                *
 *****************************************************************************/
void mainMenu( UINT32 *base1, UINT32 *base2, UINT32 *baseSnapshot )
{
	char input = WAIT;
	bool hasInput = false;
	bool swap = true;
	Menu menu = {
		ONE_PLAYER_X,
		ONE_PLAYER_Y,
		ONE_PLAYER_GAME,
		true,
		false,
		false
	};

	setVideoBase(base1);
	renderMainMenu(baseSnapshot);
	memcpy(base1, baseSnapshot, 32000);
	renderArrow(base1, &menu);
	
	while (menu.quit == false && input != '1')
	{
		hasInput = checkInput();
		
		if (hasInput == true)
		{
			input = getInput();
		}
		switch (input)
		{
			case 'e':
				if (menu.selection == ONE_PLAYER_GAME)	
				{
					menu.inMenu = false;
					onePlayerGame(base1, base2, baseSnapshot);	
				}
				else if (menu.selection == EXIT)
					menu.quit = true;
				break;
			
			case 's':
				if (menu.selection >= EXIT)
					menu.selection = ONE_PLAYER_GAME;
				else 
					menu.selection++;
				menu.hasChanged = true;
				break;
				
			case 'w':
				if (menu.selection <= ONE_PLAYER_GAME)
					menu.selection = EXIT;
				else 
					menu.selection--;
				menu.hasChanged = true;
				break;
		}
		
		input = WAIT;
		
		if (menu.inMenu == false)
		{
			renderMainMenu(base1);
			renderMainMenu(baseSnapshot);
			renderArrow(base1, &menu);
			menu.inMenu = true;
		}
		
		if (menu.hasChanged == true)
		{
			switch (menu.selection)
			{
				case ONE_PLAYER_GAME:
					menu.selectionX = ONE_PLAYER_X;
					menu.selectionY = ONE_PLAYER_Y;
					break;
					
				case TWO_PLAYER_GAME:
					menu.selectionX = TWO_PLAYER_X;
					menu.selectionY = TWO_PLAYER_Y;
					break;
					
				case EXIT:
					menu.selectionX = EXIT_X;
					menu.selectionY = EXIT_Y;
					break;
			}
			
			if (swap == true)
			{	
				memcpy(base1, baseSnapshot, 32000);
				renderArrow(base1, &menu);
				setVideoBase(base1);
					
				while (!renderRequest)
					;
				renderRequest = false;
			}
			else
			{
				memcpy(base2, baseSnapshot, 32000);
				renderArrow(base2, &menu);
				setVideoBase(base1);
					
				while (!renderRequest)
					;
				renderRequest = false;
			}

			menu.hasChanged = false;
		}
		
		setVideoBase(base1);
	}
	
	return;
}


/******************************************************************************
 *	                        Function: onePlayerGame                           *
 *****************************************************************************/
void onePlayerGame( UINT32 *base1, UINT32 *base2, UINT32 *baseSnapshot )
{
	Model *model, model1;
	UINT32 timeNow = 1;
	UINT32 timeThen = 0;
	UINT32 movedTimer = 0;
	UINT32 lastMoved = 0;
	UINT32 lastSpawn = 0;
	UINT32 musicTimer = 0;
	UINT32 lastNoteChange = 0;
	int ticksPerPixel;
	int currentNote;
	int lastNote;
	char input = '0';
	bool hasInput;
	bool swap = true;
	
	model = &model1;
	srand(timeNow);
	
	startGame(model);
	renderGameScreen(baseSnapshot);
	memcpy(base1, baseSnapshot, 32000);
	
	startMusic();


	while (input != '1' && model->gameOver == false)
	{
		
		hasInput = checkInput();
		
		if (hasInput == true)
		{
			input = getInput();
			userInput(model, input);
		}
		
	    if (renderRequest)
	    {

			musicTimer = gameTimer - lastNoteChange;
			currentNote = updateMusic(musicTimer, lastNote);
			
			if (currentNote != lastNote)
			{
				lastNoteChange = gameTimer;
				lastNote = currentNote;
			}
			
			movedTimer = gameTimer - lastMoved;
			ticksPerPixel = CLOCK_RATE / model->tray.fallSpeed;

			if (movedTimer >= ticksPerPixel) 
			{
				bubblesFall(model);
				lastMoved = gameTimer;
			}
			
			if (gameTimer - lastSpawn >= SPAWN_RATE) 
			{
				addBubble(model, rand());
				lastSpawn = gameTimer;
			}
			
			if (model->tray.bubblesMidPop > 0)
				bubblesMidPopping(model);

			if (model->render == true)
			{
				timeThen = gameTimer;
					while (!renderRequest)
						;
				renderRequest = false;
				
				if (swap == true)
				{	
					memcpy(base1, baseSnapshot, 32000);
					render(base1, model);
					setVideoBase(base1);
					
					timeThen = gameTimer;
					while (!renderRequest)
						;
					renderRequest = false;
					
					renderSnapshot(baseSnapshot, model);
				}
				else
				{
					memcpy(base2, baseSnapshot, 32000);
					render(base2, model);
					setVideoBase(base2);
					
					timeThen = gameTimer;
					while (!renderRequest)
						;
					renderRequest = false;
					
					renderSnapshot(baseSnapshot, model);
				}
				
				hasRendered(model);
				swap = !swap;

			}
		
		}
		
		timeThen = gameTimer;
	}
	
	setVideoBase(base1);
	stopSound();
	
	return;
}


/******************************************************************************
 *	                           Function: getTime                              *
 *****************************************************************************/
UINT32 getTime()
{
	UINT32 timeNow;
	long old_ssp;
	
	old_ssp = Super(0);
	timeNow = *clock;
	Super(old_ssp);
	
	return timeNow;
}

UINT32* getBuffer()
{
	UINT32 *base;
	UINT32 buffer2Addr;
	UINT32 align; /* difference between buffer2Addr and 256 aligned address */
	
	/* initializes the back buffer to be 256 aligned */
	buffer2Addr = (UINT32)buffer2;
	align = buffer2Addr % 256;
	base = (UINT32 *)(buffer2 + (256 - align));
	
	return base;
}


