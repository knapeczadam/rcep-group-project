; all 4 macros work similarily
; if (player.pos in Viewport)
;   player.pos++
;   player_info.direction = direction
; if (player.pos in Viewport)
;   player.pos++
; Todo, room for optimization
.macro MOVE_LEFT
	lda var_player_x                    ; Get X position of player
	beq @end_move_left                  ; If zero don't go left

	dec var_player_x                    ; Move one pixel
	lda var_player_info                 ; Load player info
	and #%11111100                      ; Clear bits 0 and 1
	ora #%00000011                      ; Combine with the direction for left 11
	sta var_player_info                 ; Store player info
	beq @end_move_left                  ; Check for zero again

	dec var_player_x                    ; Move him one more pixel
@end_move_left:
.endmacro

.macro MOVE_RIGHT
begin_move_right:
    lda var_player_x                    ; Get X position of player
    cmp #240                            ; Check if sprite is already at position 240 (256 - 16)
    beq end_move_right                 ; If so then don't move right

; ;Door collision
; 	lda var_player_y					; Get X position of player
; 	cmp #$87
; 	bcs @skip_collision

; 	cmp #$57
; 	bcc @skip_collision

; 	cmp #$6F
; 	bcs @skip_collision

; 	cmp #$77
; 	bcs @skip_collision
; 	; jmp @check_restitriction

; ; @skip_left_door_collision:
; ; 	lda var_player_y
; ;     cmp #216      						; Compare A with 232
; ;     bcc @skip_right_door_collision ; Branch if A < 232 (Carry = 0)

; @check_restitriction:
; 	lda var_player_x                    ; Get Y position of player
; 	cmp #214
; 	bcs end_move_right                 
; 	; cmp #87
; 	; beq end_move_down                    ; If zero don't go up

; @skip_collision:
; ;End door collision

	lda var_player_info                 ; Load player info
	and #%11111100                      ; Clear bits 0 and 1
	ora #%00000001                      ; Combine with the direction for right 01
	sta var_player_info                 ; Store player info
	inc var_player_x                    ; Move one pixel
	cmp #240                            ; Check if sprite is already at position 240 (256 - 16)
	beq end_move_right                 ; Check again

	inc var_player_x                    ; Move one pixel
end_move_right:
.endmacro

.macro MOVE_UP
    lda var_player_y                    ; Get Y position of player
    beq @end_move_up                    ; If zero don't go up

;Door collision
	lda var_player_x					; Get X position of player
	cmp #24
	bcs @skip_left_door_collision

	jmp @check_restitriction

@skip_left_door_collision:
	lda var_player_x
    cmp #216      						; Compare A with 232
    bcc @skip_right_door_collision ; Branch if A < 232 (Carry = 0)

@check_restitriction:
	lda var_player_y                    ; Get Y position of player
	cmp #135
	beq @end_move_up                    ; If zero don't go up

	cmp #111
	beq @end_move_up                    ; If zero don't go up

@skip_right_door_collision:
; End door collision

	lda var_player_info                 ; Load player info
	and #%11111100                      ; Clear bits 0 and 1
	sta var_player_info                 ; Store player info
	dec var_player_y                    ; Move one pixel
	beq @end_move_up                    ; If zero don't go up

    dec var_player_y                    ; Move one pixel
@end_move_up:    
.endmacro

.macro MOVE_DOWN
begin:
    lda var_player_y                    ; Get Y position of player
    cmp #224                            ; Check if Y is 224 because maximum Y (240 - 16, since sprite height is 16px)
    beq end_move_down                  ; If so don't move down

;Door collision
	lda var_player_x					; Get X position of player
	cmp #24
	bcs @skip_left_door_collision

	jmp @check_restitriction

@skip_left_door_collision:
	lda var_player_x
    cmp #216      						; Compare A with 232
    bcc @skip_right_door_collision ; Branch if A < 232 (Carry = 0)

@check_restitriction:
	lda var_player_y                    ; Get Y position of player
	cmp #119
	beq end_move_down                    ; If zero don't go up

	cmp #87
	beq end_move_down                    ; If zero don't go up

@skip_right_door_collision:
;End door collision

	inc var_player_y                    ; Move one pixel
	lda var_player_info                 ; Load player info
	and #%11111100                      ; Clear bits 0 and 1
	ora #%00000010                      ; Combine with the direction for down 10
	sta var_player_info                 ; Store player info
	cmp #224                            ; Check if Y is 224 because maximum Y (240 - 16, since sprite height is 16px)
	beq end_move_down                  ; If so don't move down

	inc var_player_y                    ; Move one pixel
end_move_down:
.endmacro

;===================================================================================================
; Animates the player sprite walking left and right.
;===================================================================================================
.macro ANIMATE_WALK
    TIMED_FLIP_FLOP WALK_LEFT, WALK_RIGHT, WALK_SPEED
.endmacro

;===================================================================================================
; Macro to change the player sprite to the walking right animation.
;===================================================================================================
.macro WALK_RIGHT
.local @body_left, @body_right, @stand_tile, @walk_tile
    @body_left  = oam + PLAYER_LEFT_BODY_TILE_OAM_OFFSET        ; Left body tile in OAM (see player_data)
    @body_right = oam + PLAYER_RIGHT_BODY_TILE_OAM_OFFSET       ; Right body tile in OAM (see player_data)
    @stand_tile = PLAYER_STAND_TILE_IDX                    ; Standing tile index in pattern table
    @walk_tile  = PLAYER_WALK_TILE_IDX                     ; Walking tile index in pattern table
    
    lda #@stand_tile                   ; Load standing tile index
    sta @body_left                     ; Store it in the left body tile
    lda #@walk_tile                    ; Load walking tile index
    sta @body_right                    ; Store it in the right body tile
.endmacro

;===================================================================================================
; Macro to animate the player sprite walking left.
;===================================================================================================
.macro WALK_LEFT
.local @body_left, @body_right, @stand_tile, @walk_tile
    @body_left  = oam + PLAYER_LEFT_BODY_TILE_OAM_OFFSET        ; Left body tile in OAM (see player_data)
    @body_right = oam + PLAYER_RIGHT_BODY_TILE_OAM_OFFSET       ; Right body tile in OAM (see player_data)
    @stand_tile = PLAYER_STAND_TILE_IDX                    ; Standing tile index in pattern table
    @walk_tile  = PLAYER_WALK_TILE_IDX                     ; Walking tile index in pattern table
    
    lda #@walk_tile                    ; Load walking tile index
    sta @body_left                     ; Store it in the left body tile
    lda #@stand_tile                   ; Load standing tile index
    sta @body_right                    ; Store it in the right body tile
.endmacro

;===================================================================================================
; Macro to change the player sprite to the cigar left animation.
;===================================================================================================
.macro CIGAR_LEFT
.local @cigar, @cigar_left_tile
    @cigar  = oam + PLAYER_CIGAR_TILE_OAM_OFFSET                ; Cigar sprite in OAM (see player_data)
    @cigar_left_tile = PLAYER_CIGAR_LEFT_TILE_IDX          ; Cigar tile index in pattern table
    
    lda #@cigar_left_tile              ; Load cigar tile index
    sta @cigar                         ; Store it in the cigar sprite
.endmacro

;===================================================================================================
; Macro to change the player sprite to the cigar right animation.
;===================================================================================================
.macro CIGAR_RIGHT
.local @cigar, @cigar_right_tile
    @cigar  = oam + PLAYER_CIGAR_TILE_OAM_OFFSET                ; Cigar sprite in OAM (see player_data)
    @cigar_right_tile  = PLAYER_CIGAR_RIGHT_TILE_IDX       ; Cigar tile index in pattern table
    
    lda #@cigar_right_tile             ; Load cigar tile index
    sta @cigar                         ; Store it in the cigar sprite
.endmacro
