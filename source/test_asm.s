@Removes some of Mario's abilities

repl_02113520_ov_0A:
repl_02101610_ov_0A:
repl_021015E4_ov_0A:
repl_02101598_ov_0A:
repl_02101560_ov_0A: @Wall sliding, rest are wallkicks
LDR    R1, =0x02127900
BX     LR

repl_021062F0_ov_0A:
repl_021084C0_ov_0A:
repl_02113EE8_ov_0A:
repl_020FFCA0_ov_0A: @These 4 are for Groundpounds
LDR    R1, =0x02127C78
BX     LR

repl_020CF630_ov_08:
BX     LR

repl_02152868_ov_36: @TEMP REMOVE CRSIN
BX    LR

repl_0215E1DC_ov_36: @Stops rotation in HammerBroSpawnPoint_virt61 when colliding with enemy
BX    LR

repl_020D4848_ov_0A:
MOV     R1, #0x3D0 @Sets StarTimer to go for 16.2667 seconds.
BX      LR

repl_021162C4_ov_0A:
CMP     R7, #0x3000
BX      LR

repl_021162C8_ov_0A:
MOVLT   R7, #0x3000
BX      LR

@ 0x7F is 100%
#define PAUSE_MUSIC_VOLUME #0x2A


repl_020A28F0: @ Replacing pauseMusic upon opening the pause menu on world maps
STMFD   SP!, {R0-R12,LR}
LDR     R0, =#0x208FC08
LDR     R1, =#0xFFFF
MOV     R2, PAUSE_MUSIC_VOLUME
BLX     NNS_SndPlayerSetTrackVolume
LDMFD   SP!, {R0-R12,LR}
BX      LR


repl_020A2514: @ Replacing pauseMusic upon closing the pause menu on world maps
STMFD   SP!, {R0-R12,LR}
LDR     R0, =#0x208FC08
LDR     R1, =#0xFFFF
MOV     R2, #0x7F
BLX     NNS_SndPlayerSetTrackVolume
LDMFD   SP!, {R0-R12,LR}
BX      LR

repl_021763A0_ov_44: @Removes kicking and pickup from Buzzy Beetle when in shell.
repl_02176388_ov_44:
BX     LR

repl_020D2F9C_ov_08: @Disables the Bowser. Jr cutscene when starting a new game/world
B      0x020D3024

repl_020D2718_ov_09: @Disable Opening Cutscene
B      0x020D272C

repl_020D467C_ov_08: @Disable World Map Scrolling with L/R
repl_020D4628_ov_08:
BX     LR
