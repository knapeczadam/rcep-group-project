.macro MULTIPLY_X_BY_4
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

.macro SHOOT_BULLET
; Check if we can shoot first, then shoot
    lda var_bools                       ; Load bools
    and #%00000001                      ; Check canShoot
    beq end                             ; if not return
; Don't reset shoot timer yet we don't know if we have an available bullet yet

    @player_y_pos = oam + 16
    @player_x_pos = oam + 19

    lda @player_y_pos                  ; Get Y position of the player sprite
    sta temp_00                        ; Store it
    lda @player_x_pos                  ; Get X position of the player sprite
    clc 
    adc #$08                           ; Add 8 to X (don't want to spawn on the player)
    sta temp_01                        ; Store it

; Loop through the bullets
    ldx #$FF                            ; Reset X
label:
    inx                                 ; ++x
    cpx #6                              ; If x == 6 we checked all 6 bullets
    beq end                             ; Skip ahead (If I do my math correctly we shouldn't be able to shoot more than 6 bullets anyways)
    lda var_bullets_arr, x              ; Load the value at var_bullets_arr, x
    and #%00000100                      ; Mask out all bits except bit 2
    bne label                           ; If bit 2 is 1 (result is 1), branch (means bullet is already active we dont want to touch it)

; If bullet is not active 
    lda #FIRE_RATE                      ; Load fire rate
    sta var_last_frame_count            ; Reset fire rate
    lda var_bools                       ; Load bools
    and #%11111110                      ; Set CanShoot to false
    sta var_bools

;(also dont just overrite it just flip the bit because direction shouldnt be overwriteen)
; I'm also adding a default move right mopvement but we can get parent movement and update accordingly
    lda #5                              ; Flip bit 2
    sta var_bullets_arr, x              ; Activate the bullet

; Change its position
; positionY = oam + x * 4
; positionX = oam+3 + x * 4
    txa                                 ; Transfer X to A
    tay                                 ; Transfer A to Y

    MULTIPLY_X_BY_4

    lda temp_00                         ; Load back Y position
    sta oam, x                          ; Set Y position of active bullet
    lda temp_01                         ; Load back X position
    sta oam+3,x                         ; Set X position of active bullet
end:
.endmacro