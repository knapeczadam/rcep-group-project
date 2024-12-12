; all 4 macros work similarily
; if (player.pos in Viewport)
;   player.pos++
;   player_info.direction = direction
; if (player.pos in Viewport)
;   player.pos++
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
    lda var_player_x                    ; Get X position of player
    cmp #240                            ; Check if sprite is already at position 240 (256 - 16)
    beq @end_move_right                 ; If so then don't move right
    lda var_player_info                 ; Load player info
    and #%11111100                      ; Clear bits 0 and 1
    ora #%00000001                      ; Combine with the direction for right 01
    sta var_player_info                 ; Store player info
    inc var_player_x                    ; Move one pixel
    cmp #240                            ; Check if sprite is already at position 240 (256 - 16)
    beq @end_move_right                 ; Check again
    inc var_player_x                    ; Move one pixel
@end_move_right:
.endmacro

.macro MOVE_UP
    lda var_player_y                    ; Get Y position of player
    beq @end_move_up                    ; If zero don't go up
    lda var_player_info                 ; Load player info
    and #%11111100                      ; Clear bits 0 and 1
    sta var_player_info                 ; Store player info
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
    lda var_player_info                 ; Load player info
    and #%11111100                      ; Clear bits 0 and 1
    ora #%00000010                      ; Combine with the direction for down 10
    sta var_player_info                 ; Store player info
    cmp #224                            ; Check if Y is 224 because maximum Y (240 - 16, since sprite height is 16px)
    beq @end_move_down                  ; If so don't move down
    inc var_player_y                    ; Move one pixel
@end_move_down:
.endmacro
