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
| non-reusable variable    | var_   |         | var_gamepad     |
| reusable variable        | temp_  |         | temp_00         |
| private macro            | __     |         | __PLAY_MUSIC    |
| 2 bytes pointer          |        | _ptr    | temp_00_ptr     |
| 2 bytes non-pointer      |        | _long   |                 |
| 2+ bytes array           |        | _arr    | var_bullets_arr |
| 2+ bytes temporary array |        | _arr    | temp_64_arr     |

**COMMENTS**
```
;=================================================================================================== (100 columns)
; Description
; Variable name with its usage
; References
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