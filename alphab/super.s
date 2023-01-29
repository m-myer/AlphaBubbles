;/******************************************************************************
;* Authors:    Michael Myer, David Olah                                        *
;* Emails:     mmyer488@mtroyal.ca, dolah663@mtroyal.ca                        *
;* Course:     COMP 2659                                                       *
;* Instructor: Paul Pospisil                                                   *
;* File Name:  super.s                                                         *
;******************************************************************************/


		xdef		superOn
		xdef		superOff
		

; Turns supervisor mode on.

superOn:
		move.l		d0,-(sp)
		clr.l		-(sp)
		move.w 		#$20,-(sp)
		trap		#1
		addq.l		#6,sp
		move.l		d0,oldSsp
		move.l		(sp)+,d0
		rts
		
		
; Turns supervisor mode off.

superOff:
		move.l 		d0,-(sp)
		move.l		(oldSsp),-(sp)
		move.w		#$20,-(sp)
		trap		#1
		addq.l 		#6,sp
		move.l 		(sp)+,d0
		rts

oldSsp:
		ds.l		1
