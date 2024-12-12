;===================================================================================================
; Loads the next slide
; TODO
;===================================================================================================
.macro LOAD_NEXT_SLIDE
    lda current_slide_index
	cmp #MAX_SLIDE_INDEX
    beq :+

	inc current_slide_index
	inc current_slide_index

    jsr load_slide

    lda current_slide_index
	cmp #MAX_SLIDE_INDEX
    beq :+

	ldx current_slide_index
    inx
	inx
	lda temp_00_ptr
	sta slide_base_adresses,x
	lda temp_00_ptr+1
	sta slide_base_adresses+1, x
:
.endmacro

;===================================================================================================
; Loads the previous slide
; TODO
;===================================================================================================
.macro LOAD_PREVIOUS_SLIDE
    lda current_slide_index
    beq :+

    dec current_slide_index
    dec current_slide_index
    jsr load_slide
:
.endmacro

;===================================================================================================
; Loads a slide from the base address stored in temp_00_ptr
;===================================================================================================
.proc load_slide
    ; Disable rendering
	lda #0
	sta PPU_MASK

	jsr clear_nametable                ; Clear the nametable

    SET_PPU_ADDRESS NT1_ADDRESS        ; Set the first nametable as the PPU target address

	lda #MAX_SLIDE_ROWS                ; Load the initial amount of available rows left
	sta temp_00                        ; Store the former amount in temp_00, which will decrement with each row change

    ldx current_slide_index
    lda slide_base_adresses, x
	sta temp_00_ptr
    lda slide_base_adresses + 1, x
	sta temp_00_ptr + 1
        
	; Reset the X and Y registers
	ldx #0                             ; Used as the nametable column index in text_loop and as the amount of available rows left in go_to_next_row
	ldy #0                             ; Used as the character index of our slides data

    ; Write characters to the nametable, row by row
text_loop:
	lda (temp_00_ptr),y                ; Load the character
	iny                                ; Increment the character index

    ; Check for NEWLINE
	cmp #NEWLINE
	beq prepare_newline

	 ; Check for NEXT_SLIDE
	cmp #NEXT_SLIDE
	beq prepare_next_slide

    ; Write the character to the nametable
	sta PPU_DATA
	inx                                ; Increment the nametable column index

    ; If the current row has reached MAX_SLIDE_COLUMNS, go to the next row
	cpx #MAX_SLIDE_COLUMNS
	beq go_to_next_row

    ; Go to the next character
	jmp text_loop

    ; Prepare for the NEWLINE by loading a space into the accumulator
prepare_newline:
	lda #' '
	
	; Fill the remaining columns on the current row with spaces
fill_after_newline:
    ; Write the space to the nametable
	sta PPU_DATA
	inx                                ; Increment the nametable column index

    ; If the current row has not reached MAX_SLIDE_COLUMNS, loop
	cpx #MAX_SLIDE_COLUMNS
	bne fill_after_newline

    ; Go to the next row
go_to_next_row:
	ldx temp_00                        ; Load the amount of available rows left into X

    ; Add the character index to the the base address of the slides data stored in temp_00_ptr
	tya                                ; Transfer the character index into the accumulator
	sta temp_00                        ; Store the former in temp_00
    lda temp_00_ptr                 ; Load the low byte of the base address
	clc                                ; Clear the carry flag before addition
	adc temp_00                        ; Add the character index to the low byte of the base address
	sta temp_00_ptr                 ; Store the result in the low byte of the base address
	lda temp_00_ptr + 1             ; Load the high byte of the base address
	adc #0                             ; Add the carry to the high byte of the base address
	sta temp_00_ptr + 1             ; Store the result in the high byte of the base address
	
	dex                                ; Decrement the amount of available rows left
	beq end_slide                      ; End the slide if no available rows are left with temp_00_ptr now pointing to the next slide

	stx temp_00                        ; Store the amount of available rows left in temp_00, as we have overwritten it in the addition above

	; Reset the X and Y registers
	ldx #0                             ; Reset the nametable column index
	ldy #0                             ; Reset the character index
    
	; Go to the next character
	jmp text_loop

    ; Prepare for the next slide by incrementing the base address to point to the character after NEXT_SLIDE
prepare_next_slide:
    inc temp_00_ptr                 ; Increment the low byte of the base address
	bne end_slide                      ; End the slide if the low byte did not overflow
	inc temp_00_ptr + 1             ; Increment the high byte of the base address
	
    ; End the slide
end_slide:

    ; Enable rendering
	lda #%00011110
	sta PPU_MASK

	rts
.endproc