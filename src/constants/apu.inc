;===================================================================================================
; Defines memory-mapped registers for the APU and constants for music and sound effects.
;===================================================================================================
APU_DM_CONTROL = $4010
APU_FLAGS      = $4015

APU_SQ1_ENV    = $4000
APU_SQ1_SWEEP  = $4001
APU_SQ1_LO     = $4002
APU_SQ1_HI     = $4003

APU_SQ2_ENV    = $4004
APU_SQ2_SWEEP  = $4005
APU_SQ2_LO     = $4006
APU_SQ2_HI     = $4007

SONG_COUNT     = 4
SONG_1         = 0
SONG_2         = 1
SONG_3         = 2

FX_COUNT       = 3
FX_1           = 0
FX_2           = 1
FX_3           = 2
