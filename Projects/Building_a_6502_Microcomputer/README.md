# About this project
Created a WD65C02 CPU to create a microcontroller capable of handling basic I/O. Followed the 6502 vido series by Ben Eater on Youtube.
## Files and directories
Each file indicates a key milestone for the project:
1. ArduinoLogicAnalyzer
    - Contains the logic analyzer program for an Arduion MEGA.
    - Contains a png file that shows the output of the ArduinoLogicAnalyzer program after hardcoding the NOP instruction to the CPU.

2. EEPROM Test
    - Contains the C file used to generate a bin file full of NOP instructions
    - Wrote to a binary file (output.bin) and flashed the ROM chip
    - Extracted ROM content to read and verify the data (test_read.bin)
    - Used the logic analyzer to verify that the CPU was reading NOP instructions (ROMallNOP.png)

3. EEP


| <ins>_Key Skills Exercised_</ins>  |
|:-------------:           |
|CPU Architecture          |
|6502 Assembly             |
|Memory Management         |
|Input/ Output             |
|IRQ Handling              |
