# About this project
Created a WD65C02 CPU to create a microcontroller capable of handling basic I/O. Followed the 6502 vido series by Ben Eater on Youtube.
## Files and directories
Each file indicates a key milestone for the project, the contents of which are as follows:
1. ArduinoLogicAnalyzer
    - A logic analyzer program for an Arduion MEGA.
    - Output of the ArduinoLogicAnalyzer program after hardcoding the NOP instruction to the CPU (eaSerialMonitor.png).

2. EEPROM_Test
    - A C file used to generate a bin file full of NOP instructions.
    - A binary file (output.bin) containing instructions to flash the ROM chip.
    - A binary file of the ROM contents to read and verify the data (test_read.bin).
    - A verification that the CPU was reading NOP instructions (ROMallNOP.png).

    Note: Assume all binary files are the output of the C source files or assembly files

3. EEPROM_DigitCounter
    - Machine and assembly code for a program that counts from 0 to 255 in binary
    - "Machine Code" directory
        - A C file that writes machine code of the digit counter program.
    - "Assembly Code" directory
        - asm code for the digit counter program.
    - Directions for installing the assembler and what commands to use.

3. LCD_HelloWorld
    - Assembly code for a program that displays "Hello World" on an LCD display
    - LCD_HelloWorld_w_Subroutine
        - asm code for writing to the LCD using a subroutine
        - Serial monitor result to show behavior when there is no RAM
            - CPU jumps to zero page and cannot read data
    -LCD_HelloWorld_Final
        - Final asm code for wrting to the LCD

4. IRQs
(WIP)

| <ins>_Key Skills Exercised_</ins>  |
|:-------------:           |
|CPU Architecture          |
|6502 Assembly             |
|Memory Management         |
|Input/ Output             |
|IRQ Handling              |
