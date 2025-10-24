**NAMING CONVENTIONS**
| Type       | Convention           |
|------------|----------------------|
| constants  | SCREAMING_SNAKE_CASE |
| labels     | snake_case           |
| macros     | SCREAMING_SNAKE_CASE |
| procedures | snake_case           |
| variables  | snake_case           |

**PREFIXES/POSTFIXES**
| Type                     | Prefix | Postfix | Example         |
|--------------------------|--------|---------|-----------------|
| non-reusable variable    | var_   |           | var_gamepad     |
| reusable variable        | temp_  |           | temp_00         |
| private macro            | __     |           | __PLAY_MUSIC    |
| 2 bytes pointer          |        | _ptr      | temp_00_ptr     |
| 2 bytes non-pointer      |        | _long     | temp_00_long    |
| 2+ bytes array           |        | _arr      | var_bullets_arr |
| 2+ bytes temporary array |        | VALUE_arr | temp_64_arr     |

**COMMENTS**
```
;=================================================================================================== (100 columns)
; Description
; References
;--------------------------------------------------------------------------------------------------- (100 columns)
; Variable name with its usage
;--------------------------------------------------------------------------------------------------- (100 columns)
; Pseudo code:
;--------------------------------------------------------------------------------------------------- (100 columns)
; Affected registers:
;=================================================================================================== (100 columns)
```

**INDENTATIONS**
```
label:
    instruction value                  ; Comment
____           _                       ^
   ^           ^                       |
   |           |                       |
   4 spaces    1 space                 40 columns
```

**END OF FILE**
- empty line

**USING LOCAL LABELS**

`@label:` creates a local label. To understand its scope better:

```
.proc example
begin:
  lda #0
@label:
  lda #0
  jmp @label ; this will jump up
end:
  
  jmp @label ; this will jump down
@label:
  lda #0

.endproc
```
a more thourough example would look like this:

```
.proc load_borders                      ; Start of the first codeblock
begin:                                  ; End of the first codeblock and Start the second codeblock
	tya
	bne @reset_x

	lda #0
@border_loop:                           ; border_loop is now available within the second codeblock
	sta PPU_DATA
	inx

	cpx #MAX_SLIDE_COLUMNS
	beq @reset_x

    ; Go to the next character
	jmp @border_loop

@reset_x:
	ldx #0
	lda #0
end:                                    ; End of second codeblock and start of the third codeblock
@border_loop:                           ; border_loop is now available within the third codeblock
	@border_hor 		= $09
	@left_corner		= temp_01
	@right_corner		= temp_02
	sta PPU_DATA
	inx

	cpx #MAX_SLIDE_COLUMNS
	beq @return

	cpx #2
	beq @load_top_left_corner

	cpx #3
	beq @load_border

	cpx #29
	beq @load_top_right_corner

	cpx #30
	bne @border_loop

	lda #0
	jmp @border_loop
@load_top_left_corner:
	lda @left_corner

	jmp @border_loop

@return:
	rts
.endproc
```