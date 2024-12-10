;===================================================================================================
; Executes a macro if a specified button is pressed by checking the var_gamepad input state.
; button : 8-bit input constant found in input.inc
; macro  : macro to execute if the button is pressed
;===================================================================================================
.macro ON_BUTTON_PRESSED button, macro
    lda var_gamepad                     ; Load var_gamepad state 
    and #button                         ; Check if the button is pressed
    beq :+                              ; If not, skip the next instruction
    macro                               ; Execute the macro
:
.endmacro

;===================================================================================================
; Executes a macro if a specified button is released by checking the var_gamepad input state.
; button : 8-bit input constant found in input.inc
; macro  : macro to execute if the button is released
;===================================================================================================
.macro ON_BUTTON_RELEASED button, macro
    lda var_gamepad_released               ; Load var_gamepad state
    and #button                        ; Check if the button is released
    beq :+                             ; If not, skip the next instruction
    macro                              ; Execute the macro
:
.endmacro

;===================================================================================================
; Stores a 16-bit address (in) into another 16-bit address (out) by handling low and high bytes.
; in  : 16-bit address
; out : 16-bit address
;===================================================================================================
.macro STORE_ADDRESS in, out
    lda #.lobyte(in)
    sta out
    lda #.hibyte(in)
    sta out+1
.endmacro

;===================================================================================================
; in  : 16-bit address
; out : PPU_VRAM_ADDRESS2 ($2006)
;===================================================================================================
.macro SET_PPU_VRAM_ADRESS in
    lda in
    sta PPU_VRAM_ADDRESS2
    lda in+1
    sta PPU_VRAM_ADDRESS2
.endmacro

;===================================================================================================
; Toggles a flip-flop variable and executes macro_a if the flip-flop is 0, or macro_b if it is 1.
; macro_a : macro to execute if the flip-flop is 0
; macro_b : macro to execute if the flip-flop is 1
;===================================================================================================
.macro FLIP_FLOP macro_a, macro_b
.local flip_variable, execute_macro_b
    lda var_flip_flop
    and #%00000001
    bne execute_macro_b
    macro_a
    jmp flip_variable
execute_macro_b:
    macro_b
flip_variable:
    eor #%00000001
    sta var_flip_flop
.endmacro
