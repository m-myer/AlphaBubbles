;/******************************************************************************
;* Authors:    Michael Myer, David Olah                                        *
;* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
;* Course:     COMP 2659                                                       *
;* Instructor: Paul Pospisil                                                   *
;* File Name:  vbl.s                                                           *
;******************************************************************************/


		xdef		_vblIsr
		xref		_vblIsrC

_vblIsr:
		movem.l		d0/a0,-(sp)
		jsr			_vblIsrC
		movem.l		(sp)+,d0/a0
		rte

