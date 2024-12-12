;===================================================================================================
; This macro sets the PPU address by loading the high and low bytes into the PPU_ADDRESS register.
;===================================================================================================
.macro SET_PPU_ADDRESS address
	lda PPU_STATUS
	lda #.hibyte(address)
	sta PPU_ADDRESS
	lda #.lobyte(address)
	sta PPU_ADDRESS
.endmacro

;===================================================================================================
; Increment the background color state variable and reset it to 0 if it exceeds 3.
;===================================================================================================
.macro UPDATE_BACKGROUND_STATE
    CIRCULAR_INCREMENT var_current_bg_state, 3
.endmacro