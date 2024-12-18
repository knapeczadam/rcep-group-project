;===================================================================================================
; This macro sets the PPU address by loading the high and low bytes into the PPU_ADDRESS register.
;---------------------------------------------------------------------------------------------------
; address : 16-bit address
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro SET_PPU_ADDRESS address
	lda PPU_STATUS
	lda #.hibyte(address)
	sta PPU_ADDRESS
	lda #.lobyte(address)
	sta PPU_ADDRESS
.endmacro

;===================================================================================================
; TODO: remove this macro
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
; Increment the background color state variable and reset it to 0 if it exceeds 3.
;===================================================================================================
.macro UPDATE_BACKGROUND_STATE
    CIRCULAR_INCREMENT var_current_bg_state, BG_COLOR_COUNT
.endmacro

;===================================================================================================
; Set the PPU state to NMI_SIG_CLEAR, NMI_SIG_READY or NMI_SIG_DISABLE_RENDERING
;---------------------------------------------------------------------------------------------------
; state : 
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro SET_PPU_STATE state
    lda #state
	sta var_nmi_ready
.endmacro

;===================================================================================================
; https://www.nesdev.org/wiki/PPU_scrolling#:~:text=Set%20the%20scroll%20last,overwrite%20the%20scroll%20position.
;===================================================================================================
.macro RESET_SCROLL
	lda #$00
	sta PPU_SCROLL
	sta PPU_SCROLL
.endmacro
