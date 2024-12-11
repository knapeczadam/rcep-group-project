.macro MOVE_LEFT
    lda oam + 3                         ; Get current X of first sprite
    cmp #0                              ; Check if sprite is already at position 0
    beq :+                              ; If so then don't move left
    sec                                 ; Set carry
    sbc #1                              ; Substract 1
    sta oam + 3                         ; Store X - 1 to X
    
    lda var_bullets_arr                 ; Load the current var_bullets_arr byte
    and #%11111100                      ; Clear bits 0 and 1
    ora #%00000011                      ; Combine with the direction for left 11
    sta var_bullets_arr                 ; Store the updated value back to var_bullets_arr
.endmacro

.macro MOVE_RIGHT
    lda oam + 3                         ; Get current X of first sprite
    cmp #248                            ; Check if sprite is already at position 248 (256 - 8)
    beq :+                              ; If so then don't move right
    clc                                 ; Clear carry
    adc #1                              ; Add 1
    sta oam + 3                         ; Store X + 1 to X

    lda var_bullets_arr                 ; Load the current var_bullets_arr byte
    and #%11111100                      ; Clear bits 0 and 1
    ora #%00000001                      ; Combine with the direction for right 01
    sta var_bullets_arr                 ; Store the updated value back to var_bullets_arr
.endmacro

.macro MOVE_UP
    lda oam                             ; Get current Y of the first sprite      
    cmp #0                              ; Check if Y is already 0
    beq :+                              ; If so don't move up
    sec                                 ; Set carry   
    sbc #1                              ; Substract 1
    sta oam                             ; Store Y - 1 to Y

    lda var_bullets_arr                 ; Load the current var_bullets_arr byte
    and #%11111100                      ; Clear bits 0 and 1 
    ; ora #%00000000                    ; Don't need to combine Up is 00
    sta var_bullets_arr                 ; Store the updated value back to var_bullets_arr
.endmacro

.macro MOVE_DOWN
    lda oam                             ; Get current Y of the first sprite      
    cmp #232                            ; Check if Y is 232 because maximum Y (240 - 8, since sprite height is 8px)
    beq :+                              ; If so don't move down
    clc                                 ; Clear carry   
    adc #1                              ; Add 1
    sta oam                             ; Store Y + 1 to Y

    lda var_bullets_arr                 ; Load the current var_bullets_arr byte
    and #%11111100                      ; Clear bits 0 and 1
    ora #%00000010                      ; Combine with the direction for down 10
    sta var_bullets_arr                 ; Store the updated value back to var_bullets_arr
.endmacro

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
    lda oam + 20                        ; Get Y position of the player sprite
    sta temp_00                         ; Store it
    lda oam + 20 + 3                    ; Get X position of the player sprite
    clc 
    adc #$08                            ; Add 8 to X (dont want to spawn on the player)
    sta temp_01                         ; Store it

; Loop through the bullets
    ldx #$FF                            ; Reset X
label:
    inx                                 ; ++x
    cpx #6                              ; If x == 6 we checked all 6 bullets
    beq end                             ; Skip ahead (If I do my math correctly we shouldn't be able to shoot more than 6 bullets anyways)
    lda var_bullets_arr, x              ; Load the value at var_bullets_arr, x
    and #%00000100                      ; Mask out all bits except bit 2
    bne label                           ; If bit 2 is 1 (result is 1), branch (means bullet is already active we dont want to touch it)

; If bullet is not active (also dont just overrite it just flip the bit because direction shouldnt be overwriteen)
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