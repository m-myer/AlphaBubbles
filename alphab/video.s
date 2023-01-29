;******************************************************************************
;* Authors:    Michael Myer, David Olah                                       *
;* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                       *
;* Course:     COMP 2659                                                      *
;* Instructor: Paul Pospisil                                                  *
;* File Name:  video.s                                                        *
;******************************************************************************		
		
		xdef	_setVBase

BASE	equ		8
VIDREG	equ		$FFFF8201	
	
_setVBase:
		link	a6,#0
		movem.l	d0-d2/a0-a2,-(sp)
	
		move.w	BASE(a6),d0
		lea		VIDREG,a0
		movep.w	d0,(a0)
	
		movem.l	(sp)+,d0-d2/a0-a2
		unlk	a6
		rts