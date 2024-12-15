;===================================================================================================
; Loads the top or bottom border based on bool input
;===================================================================================================
.macro LOAD_BORDER is_top_border
	@top_left_corner_location 		= $05
	@bottom_left_corner_location 	= $07

    lda #is_top_border					; Check if we're doing top or bottom border
	bne @top_border				
	lda #@bottom_left_corner_location	; Load the left corner location
	sta temp_01							; Store it for later use
	ldy #1								; Load y with non-zero we use this as bool for later to indicate we are doing the top border

	jmp @end
@top_border:
	lda #@top_left_corner_location
	sta temp_01
	ldy #0

@end:
	sta temp_02							; Store the left corner
	inc temp_02							; Increase it by one to point to the right corner

	jsr load_borders					; Now load the whole line
.endmacro

;===================================================================================================
; Loads the next slide
; TODO
;===================================================================================================
.macro LOAD_NEXT_SLIDE
    lda current_slide_index
	cmp #MAX_SLIDE_INDEX
    beq @end_load_next_slide

	inc current_slide_index
	inc current_slide_index

; animation test
	; lda var_elapsed_sec
	; sta var_test
	; lda var_bools
	; ora #%00010000
	; sta var_bools
	
    jsr load_slide

    lda current_slide_index
	cmp #MAX_SLIDE_INDEX
    beq @end_load_next_slide

	ldx current_slide_index
    inx
	inx
	lda temp_00_ptr
	sta slide_base_adresses,x
	lda temp_00_ptr+1
	sta slide_base_adresses+1, x
@end_load_next_slide:
.endmacro

;===================================================================================================
; Loads the previous slide
; TODO
;===================================================================================================
.macro LOAD_PREVIOUS_SLIDE
    lda current_slide_index
    beq @end_load_previous_slide

    dec current_slide_index
    dec current_slide_index
    jsr load_slide
@end_load_previous_slide:
.endmacro

;===================================================================================================
; Point to next line
;===================================================================================================
.macro POINT_TO_NEXT_LINE
	ldx temp_00                        	; Load the amount of available rows left into X

    ; Add the character index to the the base address of the slides data stored in temp_00_ptr
	tya                                	; Transfer the character index into the accumulator
	sta temp_00                        	; Store the former in temp_00
    lda temp_00_ptr                 	; Load the low byte of the base address
	clc                                	; Clear the carry flag before addition
	adc temp_00                        	; Add the character index to the low byte of the base address
	sta temp_00_ptr                 	; Store the result in the low byte of the base address
	lda temp_00_ptr + 1             	; Load the high byte of the base address
	adc #0                             	; Add the carry to the high byte of the base address
	sta temp_00_ptr + 1             	; Store the result in the high byte of the base address
.endmacro