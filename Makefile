# Variables
TGT_NAME := NESlides
CFG_NAME := NESlides

CFG_DIR := cfg
SRC_DIR := src
ifndef OUT_DIR
	OUT_DIR := out
endif
OBJ_DIR := obj

ifndef CA65
	CA65 := ca65
endif
ifndef LD65
	LD65 := ld65
endif

#----------------------------------------------------------------

# Create the output and object directory if they don't exist yet
ifeq ($(OS),Windows_NT)
	MKDIR = mkdir
else
	MKDIR = mkdir -p
endif

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(OUT_DIR):
	$(MKDIR) $(OUT_DIR)

#----------------------------------------------------------------

# Assemble .s65 files to objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s65 $(OBJ_DIR)
	$(CA65) -t nes -g -o $@ $<

# Link the object files into an NES file
OBJ_FILES := $(patsubst $(SRC_DIR)/%.s65,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.s65))
BASE_TGT := $(OUT_DIR)/$(TGT_NAME)
TGT := $(BASE_TGT).nes
$(TGT): $(OBJ_FILES) $(OUT_DIR)
	$(LD65) -C ${CFG_DIR}/${CFG_NAME}.cfg --dbgfile $(BASE_TGT).dbg -o $@ $(OBJ_FILES)

#----------------------------------------------------------------

# Clean target
clean:
ifeq ($(OS),Windows_NT)
	cmd /c IF EXIST $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	cmd /c IF EXIST $(OUT_DIR) rmdir /S /Q $(OUT_DIR)
else
	rm -rf $(OBJ_DIR) $(OUT_DIR)
endif

# Default target
all: $(TGT)