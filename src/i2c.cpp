// Initialization for I2C and functions to send and receive data using I2C

#include <avr/io.h>
#include "i2c.h"



void initI2C() 
{
  // Wake up from power reduction: if the I2C is in power reduction mode (PRTWI bit is 1) 
  // then it needs to be restored by writing a zero to PRTWI
  PRR0 &= ~(1 << PRTWI);   
  
  // Generate a 10kHz clock rate
  // SCL freq = 16MHz / (16 + 2(TWBR)*Prescaler)
  // Prescaler value is 4 so TWPS0 = 1 and TWPS1 = 0 (TWPS = 01)
  TWSR = (1 << TWPS0);        

  // Bit rate generator for 10 kHz
  TWBR = 0xC6; 
  
  // Enable two wire interface
  TWCR |= (1<<TWINT)|(1 << TWEN); 


}



void StartI2C_Trans(unsigned char SLA)
{
    // Clear TWINT, initiate start condition, initiate enable
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // Wait for start to complete
    while (!(TWCR & (1<<TWINT)));

    // Load SLA and Write bit (0)
    TWDR = (SLA << 1) & 0xFE;

    // Trigger action: clear TWINT and initiate enable
    TWCR = (1<<TWINT)|(1<<TWEN);

    // Wait for completion
    while (!(TWCR & (1<<TWINT)));
}



void StopI2C_Trans()
{
    // Trigger action and stop condition
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}


void Write(unsigned char data)
{
    // Data Register equals data
    TWDR = data;

    // Trigger action
    TWCR = (1<<TWINT)|(1<<TWEN);

    // Wait for completion
    while (!(TWCR & (1<<TWINT)));
}



int8_t Read_from(unsigned char SLA, unsigned char MEMADDRESS)
{
    unsigned char data;

    // Start a transmission to the SLA (write mode)
    StartI2C_Trans(SLA);

    // Write the memory address
    Write(MEMADDRESS);

    // Repeated start for read phase
    // Clear TWINT, initiate start condition, initiate enable
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // Wait for completion
    while (!(TWCR & (1<<TWINT)));

    // Load SLA and Read bit (1)
    TWDR = (SLA << 1) | 0x01;

    // Trigger action: clear TWINT and initiate enable as well as ack
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);

    // Wait for completion
    while (!(TWCR & (1<<TWINT)));

    // Read byte without ACK (single–byte read uses NACK)
    TWCR = (1<<TWINT)|(1<<TWEN);

    // Wait for completion
    while (!(TWCR & (1<<TWINT)));

    // Store the received data
    data = TWDR;

    // Trigger action and stop condition
    StopI2C_Trans();

     return data;
}



unsigned char Read_data()
{
    // Return received data register
    return TWDR;
}



// void sendDataI2C(unsigned char address, unsigned char data)
// {
//     // Start write transmission
//     StartI2C_Trans(address);

//     // Send data byte
//     Write(data);

//     // End transmission
//     StopI2C_Trans();
// }
