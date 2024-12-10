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
;; in:  16-bit address
;; out: 16-bit address
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.macro STORE_ADDRESS in, out
    lda #<in
    sta out
    lda #>in
    sta out+1
.endmacro
