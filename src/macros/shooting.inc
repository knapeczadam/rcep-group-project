.macro MOVE_LEFT
    lda oam + 3                          ; Get current X of first sprite
    cmp #0                               ; Check if sprite is already at position 0
    beq :+                               ; If so then don't move left
    sec                                  ; Set carry
    sbc #1                               ; Substract 1
    sta oam + 3                          ; Store X - 1 to X
    
    lda bullet_info                      ; Load the current bullet_info byte
    and #%11111100                       ; Clear bits 0 and 1
    ora #%00000011                       ; Combine with the direction for left 11
    sta bullet_info                      ; Store the updated value back to bullet_info
.endmacro

.macro MOVE_RIGHT
    lda oam + 3                          ; Get current X of first sprite
    cmp #248                             ; Check if sprite is already at position 248 (256 - 8)
    beq :+                ; If so then don't move right
    clc                                  ; Clear carry
    adc #1                               ; Add 1
    sta oam + 3                          ; Store X + 1 to X

    lda bullet_info                      ; Load the current bullet_info byte
    and #%11111100                       ; Clear bits 0 and 1
    ora #%00000001                       ; Combine with the direction for right 01
    sta bullet_info                      ; Store the updated value back to bullet_info
.endmacro

.macro MOVE_UP
    lda oam                              ; Get current Y of the first sprite      
    cmp #0                               ; Check if Y is already 0
    beq :+                   ; If so don't move up
    sec                                  ; Set carry   
    sbc #1                               ; Substract 1
    sta oam                              ; Store Y - 1 to Y

    lda bullet_info                      ; Load the current bullet_info byte
    and #%11111100                       ; Clear bits 0 and 1 
    ; ora #%00000000                     ; Don't need to combine Up is 00
    sta bullet_info                      ; Store the updated value back to bullet_info
.endmacro

.macro MOVE_DOWN
    lda oam                              ; Get current Y of the first sprite      
    cmp #232                             ; Check if Y is 232 because maximum Y (240 - 8, since sprite height is 8px)
    beq :+                 ; If so don't move down
    clc                                  ; Clear carry   
    adc #1                               ; Add 1
    sta oam                              ; Store Y + 1 to Y

    lda bullet_info                      ; Load the current bullet_info byte
    and #%11111100                       ; Clear bits 0 and 1
    ora #%00000010                       ; Combine with the direction for down 10
    sta bullet_info                      ; Store the updated value back to bullet_info
.endmacro

.macro SHOOT_BULLET
    lda oam                             ; Get Y position (dont really need to do this here can be done later)
    sta d_y                             ; Store it
    lda oam + 3                         ; Get X position
    sta d_x                             ; Store it

; Loop through the bullets (for now starting at 1 instead of 0)
    ldx #00                             ; Reset X
label:
    inx                                 ; ++x
    cpx #6                              ; If x == 6 we checked all 6 bullets
    beq end                             ; Skip ahead (If I do my math correctly we shouldn't be able to shoot more than 6 bullets anyways)
    lda bullet_info, x                  ; Load the value at bullet_info, x
    and #%00000100                      ; Mask out all bits except bit 2
    bne label                           ; If bit 2 is 1 (result is 1), branch (means bullet is already active we dont want to touch it)

; If bullet is not active (also dont just overrite it just flip the bit because direction shouldnt be overwriteen)
; I'm also adding a default move right mopvement but we can get parent movement and update accordingly
    lda #5                              ; Flip bit 2
    sta bullet_info, x                  ; Activate the bullet

; Change its position
; positionY = oam + x * 4
; positionX = oam+3 + x * 4
    txa                                 ; Transfer X to A
    tay                                 ; Transfer A to Y
    lda #00                             ; Clear A
	cpy #00                             ; if Y == 0
	beq temp_label                              ; Don't multiply
multiply_loop:                          ;
    clc                                 ; Clear Carry
	adc #4                              ; Add 4 (because sprites have 4 bytes of information)
	dey                                 ; --Y    
	beq temp_label                               ; if Y == 0 we're done
	jmp multiply_loop
temp_label:
    tax                                 ; Store A back into X so that X = X * 4

    lda d_y                             ; Load back Y position
    sta oam, x                          ; Set Y position of active bullet
    lda d_x                             ; Load back X position
    sta oam+3,x                         ; Set X position of active bullet
end:
.endmacro