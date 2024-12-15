;===================================================================================================
; Executes a macro if a specified button is pressed by checking the var_gamepad input state.
;---------------------------------------------------------------------------------------------------
; button : 8-bit input constant found in input.inc
; macro  : macro to execute if the button is pressed
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro ON_BUTTON_PRESS button, macro
    lda var_gamepad                     ; Load var_gamepad state 
    and #button                         ; Check if the button is pressed
    beq :+                              ; If not, skip the next instruction
      macro                            ; Execute the macro
:
.endmacro

;===================================================================================================
; Executes a macro if a specified button is released by checking the var_gamepad input state.
;---------------------------------------------------------------------------------------------------
; button : 8-bit input constant found in input.inc
; macro  : macro to execute if the button is released
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro ON_BUTTON_RELEASE button, macro
    lda var_gamepad_released           ; Load var_gamepad state
    and #button                        ; Check if the button is released
    beq :+                             ; If not, skip the next instruction
      macro                          ; Execute the macro
:
.endmacro

;===================================================================================================
; Transfers a 16-bit address from src_addr to dest_addr.
;---------------------------------------------------------------------------------------------------
; src_addr : The 16-bit source address to be transferred.
; dst_addr : The 16-bit destination where the address is stored.
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro TRANSFER_ADDRESS src_addr, dest_addr
    lda #.lobyte(src_addr)
    sta dest_addr
    lda #.hibyte(src_addr)
    sta dest_addr + 1
.endmacro

;===================================================================================================
; Increment a 16-bit variable at the specified address, handling carry to the high byte. 
;---------------------------------------------------------------------------------------------------
; address : 16-bit address of the variable to increment
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro INCREMENT_VALUE address
    ADD_VALUE address, 1
.endmacro

;===================================================================================================
; Adds an 8-bit value to a 16-bit address while handling carry propagation. 
;---------------------------------------------------------------------------------------------------
; address : The 16-bit address where the addition operation is performed.
; value   : The 8-bit value to be added to the contents of the 16-bit target address.
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro ADD_VALUE address, value
.local @end_increment_value
    clc
    lda address
    adc #value
    sta address
    lda address + 1
    adc #0
    sta address + 1
.endmacro

;===================================================================================================
; Toggles a flip-flop variable and executes macro_a if the flip-flop is 0, or macro_b if it is 1.
;---------------------------------------------------------------------------------------------------
; macro_a : macro to execute if the flip-flop is 0
; macro_b : macro to execute if the flip-flop is 1
;---------------------------------------------------------------------------------------------------
; Pseudo code:
; if flip_flop == 0
;     macro_a
; else
;     macro_b
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro FLIP_FLOP macro_a, macro_b
    lda var_flip_flop
    and #%00000001
    bne @execute_macro_b
      macro_a
      jmp @flip_variable
@execute_macro_b:
    macro_b
@flip_variable:
    lda var_flip_flop
    eor #%00000001
    sta var_flip_flop
.endmacro

;===================================================================================================
; Toggles a flip-flop variable and executes one of two macros based on a specified frame count.
;---------------------------------------------------------------------------------------------------
; macro_a : macro to execute if the flip-flop is 0
; macro_b : macro to execute if the flip-flop is 1
; frame   : 8-bit frame count to synchronize the flip-flop, must be a power of 2
;---------------------------------------------------------------------------------------------------
; Pseudo code:
; if current_frame % frame == 0
;     if flip_flop == 0
;         macro_a
;     else
;         macro_b
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro TIMED_FLIP_FLOP macro_a, macro_b, frame
.local @flip_variable, @execute_macro_b, @return
    lda var_frame_count_unclamped
    and #(frame - 1)
    bne @return
      lda var_flip_flop
      and #%00000001
      bne @execute_macro_b
        macro_a
        jmp @flip_variable
@execute_macro_b:
      macro_b
@flip_variable:
      lda var_flip_flop
      eor #%00000001
      sta var_flip_flop
@return:
.endmacro

;===================================================================================================
; Increments an 8-bit variable and resets it to 0 if it reaches a specified maximum value.
;---------------------------------------------------------------------------------------------------
; variable  : 8-bit variable to increment
; max_value : 8-bit maximum integer value for the variable, exclusive
;---------------------------------------------------------------------------------------------------
; Pseudo code:
; if variable == max_value - 1
;     variable = 0;
; else
;     variable = variable + 1;
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro CIRCULAR_INCREMENT variable, max_value
.local reset, store
    lda variable
    cmp #(max_value - 1)
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
; Decrements an 8-bit variable and resets it to a specified maximum value - 1 if it goes below 0.
;---------------------------------------------------------------------------------------------------
; variable  : 8-bit variable to decrement
; max_value : 8-bit maximum integer value for the variable, exclusive
;---------------------------------------------------------------------------------------------------
; Pseudo code:
; if variable == 0
;     variable = max_value - 1;
; else
;     variable = variable - 1;
;---------------------------------------------------------------------------------------------------
; Affected registers: A
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
    lda #(max_value - 1)
store:
    sta variable
.endmacro

;===================================================================================================
; Loads an 8-bit value from a specified address and stores it in another address if a condition is met.
;---------------------------------------------------------------------------------------------------
; from_address     : 8-bit address to load a value from
; value_to_compare : 8-bit integer value to compare with the loaded value
; to_address       : 8-bit address to store the loaded value
; value_to_load    : 8-bit integer value to load if the comparison is true
;===================================================================================================
; Pseudo code:
; if *from_address == value_to_compare
;     *to_address = value_to_load;
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro CONDITIONAL_LOAD from_address, value_to_compare, to_address, value_to_load
    lda from_address
    cmp #value_to_compare
    bne :+
    lda #value_to_load
    sta to_address
:
.endmacro
