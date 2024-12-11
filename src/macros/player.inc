.macro MOVE_LEFT
    lda var_player_x                    ; Get X position of player
    beq @end_move_left                  ; If zero don't go left
    dec var_player_x                    ; Move one pixel
    beq @end_move_left                  ; Check for zero again
    dec var_player_x                    ; Move him one more pixel
@end_move_left:
.endmacro

.macro MOVE_RIGHT
    lda var_player_x                    ; Get X position of player
    cmp #240                            ; Check if sprite is already at position 240 (256 - 16)
    beq @end_move_right                 ; If so then don't move right
    inc var_player_x                    ; Move one pixel
    cmp #240                            ; Check if sprite is already at position 240 (256 - 16)
    beq @end_move_right                 ; Check again
    inc var_player_x                    ; Move one pixel
@end_move_right:
.endmacro

.macro MOVE_UP
    lda var_player_y                    ; Get Y position of player
    beq @end_move_up                    ; If zero don't go up
    dec var_player_y                    ; Move one pixel
    beq @end_move_up                    ; If zero don't go up
    dec var_player_y                    ; Move one pixel
@end_move_up:
.endmacro

.macro MOVE_DOWN
    lda var_player_y                    ; Get Y position of player
    cmp #224                            ; Check if Y is 224 because maximum Y (240 - 16, since sprite height is 16px)
    beq @end_move_down                  ; If so don't move down
    inc var_player_y                    ; Move one pixel
    cmp #224                            ; Check if Y is 224 because maximum Y (240 - 16, since sprite height is 16px)
    beq @end_move_down                  ; If so don't move down
    inc var_player_y                    ; Move one pixel
@end_move_down:
.endmacro
