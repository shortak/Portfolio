#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 0x8000  // 32KB for a 28C256 EEPROM

int main() {
    FILE *fp = fopen("output.bin", "wb");  // Write in binary mode
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return 1;
    }

    // Set rest of the array to 0xEA
    unsigned char data[SIZE];

    memset(data, 0xea, SIZE);

    // (1) Load  11111111 to A
    data[0x00] = 0xa9;
    data[0x01] = 0xff;

    // (2) Store A to DDRA
    data[0x02] = 0x8d;
    data[0x03] = 0x03;
    data[0x04] = 0x60;

    // (3) Clear A
    data[0x05] = 0xa9;
    data[0x06] = 0x00;

    // (4) Add 1 to A, use addr 0x800c
    data[0x07] = 0x18;
    data[0x08] = 0x6d;      
    data[0x09] = 0x0c;
    data[0x0a] = 0x80;

    // (6) Push to storage
    data[0x0b] = 0x8d;
    data[0x0c] = 0x01;
    data[0x0d] = 0x60;

    // (7) Jump to (5)
    data[0x0e] = 0x4c;
    data[0x0f] = 0x07;
    data[0x10] = 0x80;

    // Set reset vector
    data[0x7ffc] = 0x00;
    data[0x7ffd] = 0x80;


    // Write the entire buffer to the file
    size_t written = fwrite(data, 1, SIZE, fp);
    if (written != SIZE) {
        perror("Error writing data to file");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    printf("Successfully wrote %d bytes to output.bin\n", SIZE);
    return 0;
}
