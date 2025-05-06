LCD_DATA = $6001
LCD_INST = $6000

RS = %00000001
RW = %00000010
E  = %00000100
 
    .org $8000
reset:
    lda #$ff        ;Load 11111111 to A
    sta $6003       ;Send A to DDRA

    lda #%00000111  ;Load 00000111 to A (PB0, PB1, PB2)
    sta $6002       ;Push A to DDRB   

loop:
    lda #%00111000  ;Set 8-bit mode and 2-line display with 5x8 font
    sta LCD_DATA

    lda #0         ;Set R, RW, E to 0
    sta LCD_INST

    lda #E          ;Send instruction to LCD
    sta LCD_INST

    lda #0         ;Set E to 0 to setup for next instruction
    sta LCD_INST

    lda #%00001110  ;Turn on display and cursor
    sta LCD_DATA

    lda #0         ;Set R, RW, E to 0
    sta LCD_INST

    lda #E          ;Send instruction to LCD
    sta LCD_INST

    lda #0         ;Set E to 0 to setup for next instruction
    sta LCD_INST

    lda #%00000110  ;Set mode to increment DDRAM address to the right for each character
    sta LCD_DATA

    lda #0         ;Set R, RW, E to 0
    sta LCD_INST

    lda #E          ;Send instruction to LCD
    sta LCD_INST

    lda #0         ;Set E to 0 to setup for next instruction
    sta LCD_INST

    ;Start data writing...
    lda #"H"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"e"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"l"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"l"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"o"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #","
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #" "
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"w"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"o"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"r"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"l"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"d"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    lda #"!"
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;Combine RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST

    ;jmp loop

    .org $fffc
    .word reset
    .word $0000
