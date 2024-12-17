;===================================================================================================
; Misc constants for text operations and other general purposes. 
;===================================================================================================
NEXT_SLIDE          = $01
NEWLINE             = $02
LAST_SLIDE          = $03
BIG_TEXT            = $04

MAX_SLIDES          = 4
MAX_SLIDE_INDEX     = (MAX_SLIDES-1)*2
MAX_SLIDE_COLUMNS   = 32
MAX_SLIDE_ROWS      = 26

FIRE_RATE           = 20
WALK_SPEED          = 8                  ; 8-bit speed value to control the animation speed, must be power of 2
CIGAR_SPEED         = 32                 ; 8-bit speed value to control the animation speed, must be power of 2

BG_COLOR_COUNT      = 3                  ; Number of background colors, maximum 4

.enum GAME_STATE
    MENU   = 0
    SLIDES = 1
.endenum