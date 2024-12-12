;===================================================================================================
; Defines memory-mapped addresses for controlling and interfacing with the PPU.
;===================================================================================================
PPU_CONTROL = $2000
PPU_MASK    = $2001
PPU_STATUS  = $2002
OAM_ADDRESS = $2003
OAM_DATA    = $2004
PPU_SCROLL  = $2005
PPU_ADDRESS = $2006
PPU_DATA    = $2007
OAM_DMA     = $4014

PAL_ADDRESS = $3F00
NT1_ADDRESS = $2000
NT1_ATTR    = $23C0
NT2_ADDRESS = $2400
NT2_ATTR    = $27C0
NT3_ADDRESS = $2800
NT3_ATTR    = $2BC0
NT4_ADDRESS = $2C00
NT4_ATTR    = $2FC0
