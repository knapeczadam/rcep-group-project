;===================================================================================================
; Loads sprite data from the specified memory address into the OAM starting at offset.
; address : Base address of the sprite data in memory
; count   : Number of sprites to load
; offset  : Offset within the OAM to start storing the sprite data
;===================================================================================================
.macro LOAD_SPRITE address, count, offset
.local @loop, @oam_location, @idx
    @oam_location = oam + offset
    @idx = 0
    
    ldx #@idx
@loop:
    lda address, x                     ; We fetch bytes from the address
    sta @oam_location, x               ; We store the bytes starting at OAM address oam
    inx                                ; ++x
    cpx #(count * 4)
    bne @loop                          ; Loop 4 times (1 hardware sprites, 4 bytes each)
.endmacro
