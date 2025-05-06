This file contains the .asm file for the machine code in the 'Machine Code' folder

The following instructions detail how the assembler is downloaded and used
1. We need an assembler that supports the 6502 CPU with the oldstyle syntax format.

2. The VARM assembler supports oldstyle and 6502, we need to install that assembler

3. Go to http://www.compilers.de/vasm.html and download the src code (http://sun.hasenbraten.de/vasm/)

4. Navigate to the make files and execute "make CPU=6502 SYNTAX=oldstyle" to generate the vasm6502_oldstyle assembler
    - MAKE SURE: The assember is moved to the /usr/local/bin directory

5. You can now use the vasm6502_oldstyle command to assemble the .asm file by doing the following:
    "vasm6502_oldstyle -Fbin -dotdir -o output.bin EEPROM_DigitCounter.asm"
        - "-Fbin" : Format output file as binary
        - "-dotdir" : Allow the .org and .word commands to be used
        - "-o" : Specify output file to be named as the file following this flag
        - "EEPROM_DigitCounter.asm" : Specify the .asm folder
