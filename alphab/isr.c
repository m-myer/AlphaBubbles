/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  isr.c                                                           *
******************************************************************************/


#include "isr.h"

int musicTimer = 0;
int gameTimer = 0;

bool renderRequest = true;
bool renderMouseRequest = false;


Vector vblVector;
Vector ikbdVector;

volatile UINT8* const IKBD_Control = 0xfffc00;
volatile UINT8* const IKBD_Status = 0xfffc00;
volatile UINT8* const IKBD_Reader = 0xfffc02;
volatile UINT8* const ISRB_MFP_Register = 0xfffa11;
volatile UINT8* const ASCIITable = 0xFFFE829C;

UINT8 IKBDBuffer[IKBD_BUFFER_SIZE];
unsigned int bufferHead = 0;
unsigned int bufferTail = 0;
UINT8 repeatedKey = 0;

int mouseState = 0;
UINT8 mouseButton;
UINT8 mouseDeltaX;
UINT8 mouseDeltaY;
bool keyRepeat = false;
bool mouseMoved = false;

int mouseX = 0;
int mouseY = 0;
bool mouseLeftClick = false;
int previousMouseX = 0;
int previousMouseY = 0;


void vblIsrC()
{
  musicTimer++;
  gameTimer++;

  renderRequest = true;
  renderMouseRequest = true;
}

void ikbdIsrC() 
{
  UINT8 scancode;

  *IKBD_Control = 0x16;
  
  if (*IKBD_Status & 0x1) /* Check if data was received. */
  {
    scancode = *IKBD_Reader;
    if (mouseState == MOUSE_STATE_FIRST_PACKET) 
	{      
      if (scancode >= MOUSE_MOVE_CODE) /* Check if scancode is mouse event. */
	  {
        mouseButton = scancode;
        mouseState = MOUSE_STATE_DELTA_X;
        mouseMoved = scancode == MOUSE_MOVE_CODE;
      } 
	  else if ((scancode & 0x80) == 0x00) /* Check if it is a make code. */
	  { 
        writeIkbdBuffer(scancode);
        keyRepeat = true;
      } 
	  else if ((scancode & 0x80) == 0x80) /* Check if it is a break code. */
	  { 
        keyRepeat = false;
      }
    } 
	else if (mouseState == MOUSE_STATE_DELTA_X) 
	{ 
      mouseState = MOUSE_STATE_DELTA_Y;
      mouseDeltaX = scancode;
    } 
	else if (mouseState == MOUSE_STATE_DELTA_Y) 
	{ 
      mouseState = MOUSE_STATE_FIRST_PACKET;
      mouseDeltaY = scancode;
    }

    *ISRB_MFP_Register &= MFB_BIT_6_MASK_OFF; /* Clears the 6th bit. */
  }

  *IKBD_Control = 0x96;
}




void installVectors() 
{
  vblVector = installVector(VBL_ISR, vblIsr);
  ikbdVector = installVector(IKBD_ISR, ikbd_Isr);
}

void removeVectors() 
{
  installVector(VBL_ISR, vblVector);
  installVector(IKBD_ISR, ikbdVector);
}

Vector installVector(int num, Vector vector) 
{
  Vector* vectp = (Vector *) ((long) num << 2);
  Vector original;
  long old_ssp = Super(0);

  original = *vectp;
  *vectp = vector;

  Super(old_ssp);
  return original;
}

bool ikbdWaiting() 
{
  return bufferHead != bufferTail;
}

bool ikbdMouseMoved() 
{
  return mouseMoved;
}

void writeIkbdBuffer(UINT8 scancode) 
{
  if (bufferTail == IKBD_BUFFER_SIZE - 1)
  {
    bufferTail = 0;
  }

  IKBDBuffer[bufferTail] = scancode;
  bufferTail++;
}

unsigned long readIkbdBuffer() 
{
  unsigned long ch;
  long old_ssp = Super(0);

  if (bufferHead == IKBD_BUFFER_SIZE - 1)
  {
    bufferHead = 0;
  }

  *ISRB_MFP_Register &= MFB_BIT_6_MASK_OFF;

  ch = IKBDBuffer[bufferHead];
  ch = ch << 16;
  ch = ch + *(ASCIITable + IKBDBuffer[bufferHead++]);

  *ISRB_MFP_Register |= MFB_BIT_6_MASK_ON; /* Turns the 6th but back on. */

  Super(old_ssp);
  return ch;
}





void clearIkbdBuffer() {
  while(ikbdWaiting()) {
    bufferHead++;
  }

  IKBDBuffer[bufferTail] = 0x00;
}





