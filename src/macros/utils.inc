;===================================================================================================
; Executes a macro if a specified button is pressed by checking the var_gamepad input state.
; button : 8-bit input constant found in input.inc
; macro  : macro to execute if the button is pressed
;===================================================================================================
.macro ON_BUTTON_PRESS button, macro
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
.macro ON_BUTTON_RELEASE button, macro
    lda var_gamepad_released           ; Load var_gamepad state
    and #button                        ; Check if the button is released
    beq :+                             ; If not, skip the next instruction
    macro                              ; Execute the macro
:
.endmacro

;===================================================================================================
; Stores a 16-bit address (in) into another 16-bit address (out) by handling low and high bytes.
; First, the low byte is stored, then the high byte is stored.
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
; out : PPU_ADDRESS ($2006)
;===================================================================================================
.macro SET_PPU_VRAM_ADRESS in
    lda in
    sta PPU_ADDRESS
    lda in+1
    sta PPU_ADDRESS
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

;===================================================================================================
; Increments an 8-bit variable and resets it to 0 if it exceeds a specified maximum value.
; variable  : 8-bit variable to increment
; max_value : 8-bit maximum integer value for the variable, inclusive
;===================================================================================================
.macro CIRCULAR_INCREMENT variable, max_value
.local reset, store
    lda variable
    cmp #max_value
    beq reset
    clc
    adc #1
    jmp store
reset:
    lda #0
store:
    sta variable
.endmacro

;===================================================================================================
; Decrements an 8-bit variable and resets it to a specified maximum value if it goes below 0.
; variable  : 8-bit variable to decrement
; max_value : 8-bit maximum integer value for the variable, inclusive
;===================================================================================================
.macro CIRCULAR_DECREMENT variable, max_value
.local reset, store
    lda variable
    cmp #0
    beq reset
    sec
    sbc #1
    jmp store
reset:
    lda #max_value
store:
    sta variable
.endmacro

;===================================================================================================
; Loads an 8-bit value from a specified address and stores it in another address if a condition is met.
; if *from_address == value_to_compare, *to_address = value_to_load.
; from_address     : 8-bit address to load a value from
; value_to_compare : 8-bit integer value to compare with the loaded value
; to_address       : 8-bit address to store the loaded value
; value_to_load    : 8-bit integer value to load if the comparison is true
;===================================================================================================
.macro CONDITIONAL_LOAD from_address, value_to_compare, to_address, value_to_load
    lda from_address
    cmp #value_to_compare
    bne :+
    lda #value_to_load
    sta to_address
:
.endmacro
