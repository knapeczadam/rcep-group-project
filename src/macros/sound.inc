;===================================================================================================
; Load music data and initialize the sound engine. The sound engine is set to PAL (0).
; https://nesasm.com/sound/famistudio-music/
;---------------------------------------------------------------------------------------------------
; Affected registers: A, X, Y
;===================================================================================================
.macro INIT_SOUND_ENGINE
    @region = 0

    ldx #.lobyte(music_data)
    ldy #.hibyte(music_data)

    lda @region
    jsr famistudio_init

    ldx #.lobyte(fx_data)
    ldy #.hibyte(fx_data)
    jsr famistudio_sfx_init
.endmacro

;===================================================================================================
; Private macro to play the music.
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro __PLAY_MUSIC
    jsr famistudio_music_stop
    lda var_current_song
    jsr famistudio_music_play
.endmacro

;===================================================================================================
; Private macro to stop the music. 
;===================================================================================================
.macro __STOP_MUSIC
    jsr famistudio_music_stop
.endmacro

;===================================================================================================
; A macro to select a song by its ID. IDs are defined in constans/apu.inc.
;---------------------------------------------------------------------------------------------------
; song_id : 8-bit song ID found in constants/apu.inc
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro SELECT_SONG song_id
    lda #song_id
    sta var_current_song
.endmacro

;===================================================================================================
; A macro that toggles music by switching between __PLAY_MUSIC and __STOP_MUSIC.
;===================================================================================================
.macro TOGGLE_MUSIC
    FLIP_FLOP __PLAY_MUSIC, __STOP_MUSIC
.endmacro

.macro PLAY_NEXT_SONG
    CIRCULAR_INCREMENT var_current_song, SONG_COUNT
    __PLAY_MUSIC
.endmacro

;===================================================================================================
; Macro to play a sound effect on the first channel.
;---------------------------------------------------------------------------------------------------
; Affected registers: A, X
;===================================================================================================
.macro PLAY_FX
    lda var_current_fx
    ldx #FAMISTUDIO_SFX_CH0
    jsr famistudio_sfx_play
.endmacro

;===================================================================================================
; Macro to select a sound effect by its ID. IDs are defined in constans/apu.inc.
;---------------------------------------------------------------------------------------------------
; fx_id : 8-bit sound effect ID
;---------------------------------------------------------------------------------------------------
; Affected registers: A
;===================================================================================================
.macro SELECT_FX fx_id
    lda #fx_id
    sta var_current_fx
.endmacro