nsub_0218A354_ov_6F:
STMFD	SP!, {R4, LR}
LDR	R0, =0x51C
BL	allocFromGameHeap
MOVS	R4, R0
BEQ	Fireball_ctor_end
BL	EnemyActor_ctor
LDR	R0, =Fireball_vtable
STR	R0, [R4]

Fireball_ctor_end:
MOV	R0, R4
LDMFD	SP!, {R4, PC}

Fireball_null:
BX	LR

Fireball_beforeDraw:
B	enemyActor_beforeDraw
BX	LR

Fireball_init:
STMFD	SP!, {R4, LR}
MOV	R4, R0

LDR	R2, =mainHeapHandle
LDR	R2, [R2]
MOV	R1, #0x40
LDR	R3, [R0]
LDR	R3, [R3, #0x34]
BLX	R3

MOV	R0, R4
BL	Fireball_setup

MOV	R0, #1
LDMFD	SP!, {R4, PC}

Fireball_beforeDelete:
B	actor_beforeDelete

Fireball_delete:
B base_onDelete

Fireball_vtable:
	.long Fireball_init
	.long actor_beforeCreate
	.long actor_afterCreate
	.long Fireball_delete
	.long Fireball_beforeDelete
	.long actor_afterDelete
	.long Fireball_execute
	.long enemyActor_beforeExecute
	.long enemyActor_afterExecute
	.long Fireball_draw
	.long enemyActor_beforeDraw
	.long actor_afterDraw
	.long base_willBeDeleted
	.long base_moreHeapShit
	.long base_createHeap
	.long base_heapCreated
	.long 0x020D5894
	.long 0x020D58F0
	.long actor_getSomething
	.long actor_incrementSomething
	.long enemyActor_executeState0 @ r0=1 (blarg?)
	.long 0x0209AD1C
	.long enemyActor_executeState1
	.long enemyActor_executeState2
	.long enemyActor_executeState3
	.long enemyActor_executeState4
	.long enemyActor_executeState5
	.long enemyActor_executeState6
	.long enemyActor_executeState7
	.long enemyActor_executeState8
	.long enemyActor_executeState9
	.long Fireball_null
	.long 0x0209FAF4
	.long 0x0209FAAC
	.long 0x0209C974
	.long 0x020A012C
	.long 0x020A00AC
	.long 0x0209F574
	.long 0x0209F3D8
	.long 0x0209F354
	.long enemyActor_executeAllStates
	.long 0x0209D988
	.long 0x0209D920
	.long 0x0209D84C @Fireball Callback
	.long 0x0209D568
	.long 0x0209D43C
	.long 0x0209D2A0
	.long 0x0209D158
	.long 0x0209D014
	.long Fireball_null
	.long 0x0209CE08
	.long 0x0209CBF8
	.long 0x0209CAD0
	.long 0x02098F7C
	.long 0x02098E7C
	.long 0x0209CD3C
	.long 0x0209CAC4
	.long Fireball_null
	.long 0x02099168
	.long 0x02098A94
	.long Fireball_null
	.long 0x02098A10
	.long 0x0209C9D0
	.long 0x0209C994
	.long 0x020A0268
	.long 0x020A0240
	.long 0x0209A6D4
