nsub_0201F0F4_main:
nsub_0201F118_main:
nsub_0201F13C_main:
	MOV		R0, #0
	BX      LR

.globl MygetUnk1ForView
MygetUnk1ForView:
	STMFD   SP!, {LR}
	SUB     SP, SP, #4
	MOV     R1, #0
	BL      getPtrToViewById
	CMP     R0, #0
	LDRNEB  R0, [R0,#0xB]
	MOVEQ   R0, #0
	ADD     SP, SP, #4
	LDMFD   SP!, {PC}

.globl MygetUnk2ForView
MygetUnk2ForView:
	STMFD   SP!, {LR}
	SUB     SP, SP, #4
	MOV     R1, #0
	BL      getPtrToViewById
	CMP     R0, #0
	LDRNEB  R0, [R0,#0xC]
	MOVEQ   R0, #0
	ADD     SP, SP, #4
	LDMFD   SP!, {PC}

.globl MygetUnk3ForView
MygetUnk3ForView:
	STMFD   SP!, {LR}
	SUB     SP, SP, #4
	MOV     R1, #0
	BL      getPtrToViewById
	CMP     R0, #0
	LDRNEB  R0, [R0,#0xD]
	MOVEQ   R0, #0
	ADD     SP, SP, #4
	LDMFD   SP!, {PC}
