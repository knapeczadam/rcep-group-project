;===================================================================================================
; Get the X offset in oam for the target bullet.
;===================================================================================================
.macro MULTIPLY_X_BY_4 ;; TODO: rename this to GET_BULLET_SPRITE_ADDRESS (based on x)
    lda #$20                            ; Clear A (set start to second OAM line)
	cpy #00                             ; if Y == 0
	beq return                          ; Don't multiply
multiply_loop:                          ;
    clc                                 ; Clear Carry
	adc #4                              ; Add 4 (because sprites have 4 bytes of information)
	dey                                 ; --Y    
	beq return                          ; if Y == 0 we're done
	jmp multiply_loop
return:
    tax                                 ; Store A back into X so that X = X * 4
.endmacro

;===================================================================================================
; Shoots a bullet duh.
;===================================================================================================
.macro SHOOT_BULLET
; Check if we can shoot first, then shoot
    lda var_bools                       ; Load bools
    and #%00000001                      ; Check canShoot
    beq end                             ; if not return
; Don't reset shoot timer yet we don't know if we have an available bullet yet

; Loop through the bullets
    ldx #$FF                            ; Reset X
@loop_bullets:
    inx                                 ; ++x
    cpx #6                              ; If x == 6 we checked all 6 bullets
    beq end                             ; Skip ahead (If I do my math correctly we shouldn't be able to shoot more than 6 bullets anyways)
    lda var_bullets_arr, x              ; Load the value at var_bullets_arr, x
    and #%00000100                      ; Mask out all bits except bit 2
    bne @loop_bullets                   ; If bit 2 is 1 (result is 1), branch (means bullet is already active we dont want to touch it)

; If bullet is not active 
    lda #FIRE_RATE                      ; Load fire rate
    sta var_last_frame_count            ; Reset fire rate
    lda var_bools                       ; Load bools
    and #%11111110                      ; Set CanShoot to false
    sta var_bools

; Set direction of the bullet and activate it
    jsr load_bullet_position

    lda var_player_info                 ; Load player movement
    and #%00000011                      ; Keep only movement info
    ora #%00000100                      ; FLip bit 2 to activate bullet
    sta var_bullets_arr, x              ; Store the info back into the correct bullet

; Change its position
; positionY = oam + x * 4
; positionX = oam+3 + x * 4
    txa                                 ; Transfer X to A
    tay                                 ; Transfer A to Y

    MULTIPLY_X_BY_4

    jsr rotate_bullet                   ; Rotate the bullet to correct direction

    lda temp_00                         ; Load back Y position
    sta oam, x                          ; Set Y position of active bullet
    lda temp_01                         ; Load back X position
    sta oam+3,x                         ; Set X position of active bullet

; Play a sound when firing
    SELECT_FX FX_2
    PLAY_FX
end:
.endmacro