**NAMING CONVENTIONS**
| Type       | Convention           |
|------------|----------------------|
| constants  | SCREAMING_SNAKE_CASE |
| labels     | snake_case           |
| macros     | SCREAMING_SNAKE_CASE |
| procedures | snake_case           |
| variables  | snake_case           |

**PREFIXES**
| Type            | Prefix |
|-----------------|--------|
| global variable | var_   |
| local variable  | temp_  |
| private macro   | __     |

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