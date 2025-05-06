LCD_DATA = $6001
LCD_INST = $6000
DDRA = $6003
DDRB = $6002

;Dedicate dividend and remainder to RAM
value = $0200       ;Dividend
mod10 = $0202       ;Divisor (10)
message = $0204     ; 6 byte message

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

    ; Initialize message in RAM
    lda #0
    sta message
    ; Initialize value to be the number to convert
   lda number ;store the low byte of the target number into mem
   sta value
   lda number + 1   ; Store the high byte of the target number into mem
   sta value + 1

divide:
    ;Initialize remainder to be stored
   lda #0       
   sta mod10
   sta mod10 + 1    ;Keep in mind, you do not need to load A again to store the same number

    ldx #16  ;number of bits of number
divloop:
    ; Rotate quotient (value) and remainder (mod10)
   rol value
   rol value +1
   rol mod10
   rol mod10 + 1

    ; a,y = dividend - divisor
   sec ;Set carry bit
   lda mod10 ; Load low byte of the remainder
   sbc #10
   tay ; save low byte in Y
   lda mod10 + 1 ;Load high bute of the remainder
   sbc #0 ; Subtract 0 from high byte since #10 is a 5bit number
   bcc ignore_result    ; Branch if dividend < divisor
   sty mod10
   sta mod10 + 1

ignore_result:
    dex
    bne divloop
    rol value   ; Shift in the last bit of the quotient

    lda mod10
    clc
    adc #"0"
    jsr push_char

    ; If value != 0, then continue dividing
    lda value
    ora value + 1   ; Check if low and high bytes are all 0, if not, A will not be 0 after the bitwise or
    bne divide  ; Branch if A is not 0

    ldx #0   
print:       ;Initialize X register
    lda message, x  ;Load the message located at index x
    beq loop        ;If we loaded a zero in A, branch to loop
    jsr send_char
    inx           ;Increment value in X register
    jmp print

loop:
    jmp loop

number: .word 1729

; Add char in A register to the beginning of the null-terminated string 'message'
push_char:
    pha ; Push new first char onto stack
    ldy #0

char_loop:
    lda message,y   ; Get char on string and put into X
    tax
    pla
    sta message, y  ; Pull char off stack and add it to the string
    iny
    txa
    pha             ; Push char from string onto stack
    bne char_loop

    pla
    sta message, y  ; Pull the null off the stack and add to the end of the string

    rts

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

