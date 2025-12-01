// Initialization for I2C and a function sendatai2c that sends data using I2C
#include <avr/io.h>
#include "i2c.h"



void initI2C() 
{
  // wake up from power reduction: if the I2C is in power reduction mode (PRTWI bit is 1) 
  //then it needs to be restored by writing a zero to PRTWI.
  
PRR0 &= ~(1 << PRTWI);   
  
  // generate a 10kHz clock rate
  // SCL freq = 16Mhz/(16 + 2(TWBR)*4)
  // Table 24-7 Prescaler value is 4 so TWPS0 = 1 and TWPS1 = 0.
  TWSR |= (1 << TWPS0);
  TWSR &= ~(1 << TWPS1);
  TWBR = 0xC6; //bit rate generator = 10k  (TWBR = 18)

  TWCR |= (1 << TWINT | 1 << TWEN); // enable two wire interface
 

  
}

void StartI2C_Trans(unsigned char SLA)
{
    // Send START
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    // Load SLA and Write... 0
    TWDR = (SLA << 1) & 0xFE;

    // Clear flag and begin transmission
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void StopI2C_Trans()
{
    //stop write
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void Write(unsigned char data)
{
    //Data Register equals data
    TWDR = data;
    //set control register to start
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}


unsigned char Read_from(unsigned char SLA, unsigned char MEMADDRESS)
{
    //Write phase (pretty much what we have above)
    StartI2C_Trans(SLA);   // SLA and W
    Write(MEMADDRESS);

    //Repeated Start for read
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    // Load SLA amd Read... 1 
    TWDR = (SLA << 1) | 0x01;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    //Read byte without ACK (NACK)
    TWCR = (1<<TWINT)|(1<<TWEN); // no TWEA → NACK
    while (!(TWCR & (1<<TWINT)));

    //Stop
    StopI2C_Trans();

    return TWDR;
}

unsigned char Read_data()
{
    //return what we need to
    return TWDR;
}

void sendDataI2C(unsigned char address, unsigned char data)
{
    StartI2C_Trans(address);
    Write(data);
    StopI2C_Trans();
}