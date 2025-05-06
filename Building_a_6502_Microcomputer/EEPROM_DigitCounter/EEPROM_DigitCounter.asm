    .org $8000
reset:
    lda #$ff
    sta $6003

loop:
    clc
    adc #$01

    sta $6001

    jmp loop

    .org $fffc
    .word reset 
    .word $0000