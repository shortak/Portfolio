LCD_DATA = $6001
LCD_INST = $6000
DDRA = $6003
DDRB = $6002

RS = %00000001
RW = %00000010
E  = %00000100
 
    .org $8000
reset:
    ldx #$ff        ;Initialize stack pointer into x register
    txs             ;Transfer x to stack pointer register

    lda #%11111111  ;Load 11111111 to A
    sta DDRA        ;Push A to DDRA

    lda #%00000111  ;Load 00000111 to A (PB0, PB1, PB2)
    sta DDRB        ;Push A to DDRB 



    lda #%00111000  ;Set 8-bit mode and 2-line display with 5x8 font
    jsr send_inst
    
    lda #%00001110  ;Turn on display and cursor
    jsr send_inst

    lda #%00000110  ;Set mode to increment DDRAM address to the right for each character
    jsr send_inst

    lda #%00000001  ;Clear display
    jsr send_inst

    ;Start data writing...
    ldx #0   
print:       ;Initialize X register
    lda message, x  ;Load the message located at index x
    beq loop        ;If we loaded a zero in A, branch to loop
    jsr send_char
    inx           ;Increment value in X register
    jmp print

loop:
    jmp loop

message: .asciiz "Hello, world!" ; Full message, each character has its own address and can be indexed. Sticks in a 00 at the end

wait:
    pha            ;Store whatever was in A to stack
    lda #%00000000 ;Set PortA to input
    sta DDRA
busy:
    lda #RW        ;Set RW bit on
    sta LCD_INST
    lda #(RW | E)  ;Send instruction
    sta LCD_INST
    lda LCD_DATA    ;Load LCD Status (Top bit, PA7, is busy flag) into A
    and #%10000000  ;Bit-wise and... zero out everything except top bit in A
    bne busy        ;Branch to "wait" address if Z flag is not set

    lda #RW
    sta LCD_DATA
    lda #%11111111  ;Set PortA to output
    sta DDRA     
    pla             ;Pull off stack and place into A
    rts

send_char:
    jsr wait       ;Check if LCD busy
    sta LCD_DATA
    lda #RS        ;Set RS and clear RW and E
    sta LCD_INST
    lda #(RS | E)  ;A "bitwise OR", it combines RS and E (i.e. 10100000) and send instruction
    sta LCD_INST
    lda #RS        ;Clear E
    sta LCD_INST
    rts

send_inst:
    jsr wait       ;Check if LCD is busy
    sta LCD_DATA
    lda #0         ;Set R, RW, E to 0
    sta LCD_INST
    lda #E         ;Send instruction to LCD
    sta LCD_INST
    lda #0         ;Set E to 0 to setup for next instruction
    sta LCD_INST
    rts




    .org $fffc
    .word reset
    .word $0000
