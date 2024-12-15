;===================================================================================================
; Move Menu arrow UP.
;===================================================================================================
.macro MOVE_ARROW_UP
    lda #$87                            ; Load desired position
    sta oam + TEXT_ARROW_OAM_OFFSET     ; Set the sprite position
.endmacro

;===================================================================================================
; Move Menu arrow DOWN.
;===================================================================================================
.macro MOVE_ARROW_DOWN
    lda #$8F
    sta oam + TEXT_ARROW_OAM_OFFSET
.endmacro

;===================================================================================================
; Set the first slide and according variables for fun/not fun mode.
;===================================================================================================
.macro SELECT_MODE
    lda oam + TEXT_ARROW_OAM_OFFSET     ; Get Y Position
    cmp #$8F                            ; Check if it's not fun mode
    bne @change_game_state              ; skip changing mode (default is fun mode)

    lda var_bools   
    and #%11111100                      ; disable shooting and fun mode
    sta var_bools

@change_game_state:
    lda #1  
    sta var_gamestate                   ; Set gamestate to slide

; Load the first slide
    TRANSFER_ADDRESS slides, slide_base_adresses
	jsr load_slide
	inc loaded_slides_count
	lda temp_00_ptr
	sta slide_base_adresses+2
	lda temp_00_ptr+1
	sta slide_base_adresses+3

; Disable the arrow
    lda #$F0							; Reset the Y coord to be out of screen
	sta oam + TEXT_ARROW_OAM_OFFSET     ; 

    ; TODO find out why that sprite is on the screen? remove whatever puts it on screen and remove the code below
    lda #0
    sta oam + 27
    lda #$FF
    sta oam + 20

    rts
.endmacro