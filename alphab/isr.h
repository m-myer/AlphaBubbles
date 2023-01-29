/******************************************************************************
* Authors:    Michael Myer, David Olah                                        *
* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
* Course:     COMP 2659                                                       *
* Instructor: Paul Pospisil                                                   *
* File Name:  isr.h                                                           *
******************************************************************************/


#ifndef ISR_H
#define ISR_H

#include "vbl.h"
#include "ikbd.h"
#include "music.h"
#include "renderer.h"
#include "types.h"

#define VBL_ISR 28
#define IKBD_ISR 70

#define IKBD_RX_DEFAULT 0xfffc96
#define IKBD_RX_INTERRUPT_OFF 0xfffc16

#define MFB_BIT_6_MASK_ON 0x40
#define MFB_BIT_6_MASK_OFF 0xbf

#define MOUSE_STATE_FIRST_PACKET 0
#define MOUSE_STATE_DELTA_X 1
#define MOUSE_STATE_DELTA_Y 2

#define MOUSE_MOVE_CODE 0xf8
#define MOUSE_LEFT_BUTTON_CODE 0xfa

#define IKBD_BUFFER_SIZE 256

typedef void (*Vector) ();

/* Timers that are used by the VBL. */
extern int musicTimer;
extern int gameTimer;

/* Flags that will allow rendering when they are set to true. */
extern bool renderRequest;
extern bool renderMouseRequest;

extern int mouseX;
extern int mouseY;

extern bool mouseLeftClick;

extern UINT8 mouseButton;
extern UINT8 mouseDeltaX;
extern UINT8 mouseDeltaY;
extern int previousMouseX;
extern int previousMouseY;
extern bool keyRepeat;
extern bool mouseMoved;

extern UINT8 IKBDBuffer[IKBD_BUFFER_SIZE];
extern unsigned int bufferHead;
extern unsigned int bufferTail;
extern UINT8 repeatedKey;

extern Vector vblVector;
extern Vector ikbdVector;


/**
 * Updates timer on VBL IRQ
 * VBL ISR does following:
 *    • Time the page flipping for double buffered graphics.
 *    • Time the playing of music.
 *    • Time any other synchronous events needed by the game.
 */
void vblIsrC();

/**
 * Processes keyboard and mouse input on IKBD IRQ.
 */
void ikbdIsrC();

/**
 * Installs vector.
 */
Vector installVector(int num, Vector vector);

/**
 * Installs vbl and ikbd vectors.
 */
void installVectors();

/**
 * Removes vectors.
 */
void removeVectors();

/**
 * Checks if the keyboard is waiting for input.
 */
bool ikbdWaiting();

/**
 * Checks if mouse has moved.
 */
bool ikbdMouseMoved();

/**
 * Write keyboard value to the keyboard buffer.
 */
void writeIkbdBuffer(UINT8 scancode);

/**
 * Read keyboard value from the keyboard buffer.
 */
unsigned long readIkbdBuffer();

/**
 * Clears the keyboard buffer.
 */
void clearIkbdBuffer();




#endif
