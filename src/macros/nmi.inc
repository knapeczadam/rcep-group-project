;===================================================================================================
; Pushes the registers A, X, Y, and the processor status onto the stack. 
;===================================================================================================
.macro PUSH_REGISTERS
	pha
	txa
	pha
	tya
	pha
	php
.endmacro

;===================================================================================================
; Pull the registers processor status, Y, X, and A from the stack.
; The order of the registers is reversed from the PUSH_REGISTERS macro.
;===================================================================================================
.macro POP_REGISTERS
	plp
	pla
	tay
	pla
	tax
	pla
.endmacro
