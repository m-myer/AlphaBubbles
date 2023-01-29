;/******************************************************************************
;* Authors:    Michael Myer, David Olah                                        *
;* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
;* Course:     COMP 2659                                                       *
;* Instructor: Paul Pospisil                                                   *
;* File Name:  ikbd.s                                                          *
;******************************************************************************/


		xdef		_ikbd_Isr
		xref		_ikbdIsrC

_ikbd_Isr:
		movem.l		d0/a0,-(sp)
		jsr			_ikbdIsrC
		movem.l		(sp)+,d0/a0
		rte

