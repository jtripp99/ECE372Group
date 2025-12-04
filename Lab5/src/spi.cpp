// spi.cpp
#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>

// ATmega2560 hardware SPI pin assignments:
// MOSI = PB2
// MISO = PB3
// SCK  = PB1
// SS   = PB0   <-- used for MAX7221 LOAD/CS

//SPI_DDR   DDRB
//SPI_PORT  PORTB
//PIN_SS    PB0     // CS/LOAD
//PIN_SCK   PB1
//PIN_MOSI  PB2
int smile[] =   {0b00111100,
                     0b01000010,
                     0b10100101,
                     0b10000001,
                     0b10100101,
                     0b10011001,
                     0b01000010,
                     0b00111100};

    int frown[] =   {0b00111100,
                     0b01000010,
                     0b10100101,
                     0b10000001,
                     0b10011001,
                     0b10100101,
                     0b01000010,
                     0b00111100};
// SPI Initialization (Mode 0, MSB first)
void SPI_Init()
{
    // Set MOSI, SCK, SS as outputs
    DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0);

    // Keep SS high (inactive)
    PORTB |= (1 << PB0);

    // Enable SPI in Master mode, fosc/16, Mode-0
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

// Send a single byte over SPI
void SPI_SendByte(int data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF))); // Wait for transfer complete
}

// Send register + data to MAX7221
void SPI_SendCommand(int reg, int value)
{
    PORTB &= ~(1 << PB0);  // CS LOW (begin)
    SPI_SendByte(reg);
    SPI_SendByte(value);
    PORTB |= (1 << PB0);   // CS HIGH (latch)
}


// Initialize MAX7221 for 8×8 LED matrix
void MAX7219_Init()
{
    SPI_SendCommand(MAX_REG_SCANLIMIT, 0x07); // Show all 8 rows
    SPI_SendCommand(MAX_REG_DECODE,    0x00); // Matrix mode
    SPI_SendCommand(MAX_REG_SHUTDOWN,  0x01); // Normal operation
    SPI_SendCommand(MAX_REG_TEST,      0x00); // No test mode
    SPI_SendCommand(MAX_REG_INTENSITY, 0x08); // Brightness (0–15)
}

// Display 8 bytes on matrix (1 byte = 1 row)
void MAX7219_DisplayBuffer(const int buffer[8])
{
    for (int row = 0; row < 8; row++)
    {
        SPI_SendCommand(row + 1, buffer[row]);
    }
}
void smileyFace(){
    MAX7219_DisplayBuffer(smile);
}
void frownyFace(){
    MAX7219_DisplayBuffer(frown);
}