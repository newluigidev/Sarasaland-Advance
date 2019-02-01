nsub_02010094_main:            @ Remove control from player
    LDR        R1, =ControlLock
    LDRB    R1, [R1]
    CMP        R1, #0
    BXNE    LR
    STMFD   SP!, {R4,LR}
    B        0x2010098
