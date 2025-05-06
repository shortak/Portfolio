#include <stdio.h>
#include <stdlib.h>

#define SIZE 0x8000  // 32KB for a 28C256 EEPROM

int main() {
    FILE *fp = fopen("output.bin", "wb");  // Write in binary mode
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return 1;
    }

    // Create an array filled with 0xEA
    unsigned char data[SIZE];
    for (int i = 0; i < SIZE; i++) {
        data[i] = 0xEA;
    }

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
