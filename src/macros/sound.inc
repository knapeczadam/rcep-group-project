;===================================================================================================
; Load music data and initialize the sound engine. The sound engine is set to PAL (0).
; https://nesasm.com/sound/famistudio-music/
;===================================================================================================
.macro INIT_SOUND_ENGINE
    ldx #.lobyte(music_data)
    ldy #.hibyte(music_data)

    lda #0
    jsr famistudio_init
.endmacro

;===================================================================================================
; Private macro to play the music.
;===================================================================================================
.macro __PLAY_MUSIC
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
;===================================================================================================
.macro SELECT_SONG song_id
    lda #song_id
.endmacro

;===================================================================================================
; A macro that toggles music by switching between __PLAY_MUSIC and __STOP_MUSIC.
;===================================================================================================
.macro TOGGLE_MUSIC
    FLIP_FLOP __PLAY_MUSIC, __STOP_MUSIC
.endmacro