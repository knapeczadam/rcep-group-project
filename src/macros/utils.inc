;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; button : 8-bit input constant found in input.inc
;; macro  : macro to execute if the button is pressed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.macro ON_BUTTON_PRESSED button, macro
    lda gamepad                        ; Load gamepad state 
    and #button                        ; Check if the button is pressed
    beq :+                             ; If not, skip the next instruction
    macro                              ; Execute the macro
:
.endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; button : 8-bit input constant found in input.inc
;; macro  : macro to execute if the button is released
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.macro ON_BUTTON_RELEASED button, macro
    lda gamepad_released               ; Load gamepad state
    and #button                        ; Check if the button is released
    beq :+                             ; If not, skip the next instruction
    macro                              ; Execute the macro
:
.endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; in  : 16-bit address
;; out : 16-bit address
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.macro STORE_ADDRESS in, out
    lda #<in
    sta out
    lda #>in
    sta out+1
.endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; macro_a : macro to execute if the flip-flop is 0
;; macro_b : macro to execute if the flip-flop is 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.macro FLIP_FLOP macro_a, macro_b
.local flip_variable, execute_macro_b
    lda flip_flop
    and #%00000001
    bne execute_macro_b
    macro_a
    jmp flip_variable
execute_macro_b:
    macro_b
flip_variable:
    eor #%00000001
    sta flip_flop
.endmacro