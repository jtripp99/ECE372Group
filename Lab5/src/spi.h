// spi.h
#ifndef SPI_H
#define SPI_H


// MAX7221 Register Addresses
#define MAX_REG_NOOP       0x00
#define MAX_REG_DIGIT0     0x01
#define MAX_REG_DIGIT1     0x02
#define MAX_REG_DIGIT2     0x03
#define MAX_REG_DIGIT3     0x04
#define MAX_REG_DIGIT4     0x05
#define MAX_REG_DIGIT5     0x06
#define MAX_REG_DIGIT6     0x07
#define MAX_REG_DIGIT7     0x08
#define MAX_REG_DECODE     0x09
#define MAX_REG_INTENSITY  0x0A
#define MAX_REG_SCANLIMIT  0x0B
#define MAX_REG_SHUTDOWN   0x0C
#define MAX_REG_TEST       0x0F

// SPI Functions
void SPI_Init();
void SPI_SendByte(int data);
void SPI_SendCommand(int reg,int value);
void smileyFace();
void frownyFace();
// LED matrix helpers
void MAX7219_Init();
void MAX7219_DisplayBuffer(const int buffer[8]);

#endif