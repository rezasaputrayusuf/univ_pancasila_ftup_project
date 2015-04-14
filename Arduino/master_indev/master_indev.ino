// -------------------------------------------------------------------------------------------
// Teensy3.0/3.1 I2C Master
// 08Mar13 Brian (nox771 at gmail.com)
// -------------------------------------------------------------------------------------------
//
// This creates an I2C master device which talks to the simple I2C slave device given in the
// i2c_t3/slave sketch.
//
// This code assumes the slave config has 256byte memory and I2C addr is 0x44.
// The various tests are started by pulling one of the control pins low.
//
// This example code is in the public domain.
//
// -------------------------------------------------------------------------------------------
// Slave protocol is as follows:
// -------------------------------------------------------------------------------------------
// WRITE - The I2C Master can write to the device by transmitting the WRITE command,
//         a memory address to store to, and a sequence of data to store.
//         The command sequence is:
//
// START|I2CADDR+W|WRITE|MEMADDR|DATA0|DATA1|DATA2|...|STOP
//
// where START     = I2C START sequence
//       I2CADDR+W = I2C Slave address + I2C write flag
//       WRITE     = WRITE command
//       MEMADDR   = memory address to store data to
//       DATAx     = data byte to store, multiple bytes are stored to increasing address
//       STOP      = I2C STOP sequence
// -------------------------------------------------------------------------------------------
// READ - The I2C Master can read data from the device by transmitting the READ command,
//        a memory address to read from, and then issuing a STOP/START or Repeated-START,
//        followed by reading the data.  The command sequence is:
//
// START|I2CADDR+W|READ|MEMADDR|REPSTART|I2CADDR+R|DATA0|DATA1|DATA2|...|STOP
//
// where START     = I2C START sequence
//       I2CADDR+W = I2C Slave address + I2C write flag
//       READ      = READ command
//       MEMADDR   = memory address to read data from
//       REPSTART  = I2C Repeated-START sequence (or STOP/START if single Master)
//       I2CADDR+R = I2C Slave address + I2C read flag
//       DATAx     = data byte read by Master, multiple bytes are read from increasing address
//       STOP      = I2C STOP sequence
// -------------------------------------------------------------------------------------------
// SETRATE - The I2C Master can adjust the Slave configured I2C rate with this command
//           The command sequence is:
//
// START|I2CADDR+W|SETRATE|RATE|STOP
//
// where START     = I2C START sequence
//       I2CADDR+W = I2C Slave address + I2C write flag
//       SETRATE   = SETRATE command
//       RATE      = I2C RATE to use (must be from i2c_rate enum list, eg. I2C_RATE_xxxx)
// -------------------------------------------------------------------------------------------

#include <i2c_t3.h>

// Command definitions
#define WRITE    0x10
#define READ     0x20
#define SETRATE  0x30

// Function prototypes
void print_i2c_status(void);
void test_rate(uint8_t target, i2c_rate rate);

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);    // LED
    digitalWrite(LED_BUILTIN,LOW);  // LED off
    pinMode(12,INPUT_PULLUP);       // Control for Test1
    pinMode(11,INPUT_PULLUP);       // Control for Test2
    pinMode(10,INPUT_PULLUP);       // Control for Test3
    pinMode(9,INPUT_PULLUP);        // Control for Test4
    pinMode(8,INPUT_PULLUP);        // Control for Test5

    Serial.begin(9600);

    // Setup for Master mode, pins 18/19, external pullups, 400kHz
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_INT, I2C_RATE_400);
}
byte x = 0;
void loop()
{
    size_t addr, len;
    uint8_t databuf[256];
    uint8_t target = 0x44; // slave addr
    uint32_t count;

    digitalWrite(LED_BUILTIN,HIGH);
    
    Wire.beginTransmission(target);
    Wire.write("x is "); 
    Wire.write(x);
    Wire.endTransmission(); 

    digitalWrite(LED_BUILTIN,LOW);         // LED off
    Serial.print(x);
    x++;
    if(x==10) {
        x=0;
    }
    delay(500);        
}


//
// print I2C status
//
void print_i2c_status(void)
{
    switch(Wire.status())
    {
    case I2C_WAITING:  Serial.print("I2C waiting, no errors\n"); break;
    case I2C_ADDR_NAK: Serial.print("Slave addr not acknowledged\n"); break;
    case I2C_DATA_NAK: Serial.print("Slave data not acknowledged\n"); break;
    case I2C_ARB_LOST: Serial.print("Bus Error: Arbitration Lost\n"); break;
    default:           Serial.print("I2C busy\n"); break;
    }
}


//
// test rate
//
void test_rate(uint8_t target, i2c_rate rate)
{
    // Change Slave rate
    Wire.beginTransmission(target); // slave addr
    Wire.write(SETRATE);            // SETRATE command
    Wire.write((uint8_t)rate);      // rate
    Wire.endTransmission();         // blocking write

    // Change Master rate
    Wire.setRate(F_BUS,rate);

    // Setup write buffer
    Wire.beginTransmission(target); // slave addr
    Wire.write(WRITE);              // WRITE command
    Wire.write(0);                  // memory address
    for(uint8_t len = 0; len < 128; len++)  // write 128 byte block
        Wire.write(len);

    // Write to Slave
    elapsedMicros deltaT;
    Wire.endTransmission();         // blocking write
    uint32_t deltatime = deltaT;

    // Print result
    Serial.print("128 byte transfer at ");
    switch(rate)
    {
    case I2C_RATE_100: Serial.print("I2C_RATE_100"); break;
    case I2C_RATE_200: Serial.print("I2C_RATE_200"); break;
    case I2C_RATE_300: Serial.print("I2C_RATE_300"); break;
    case I2C_RATE_400: Serial.print("I2C_RATE_400"); break;
    case I2C_RATE_600: Serial.print("I2C_RATE_600"); break;
    case I2C_RATE_800: Serial.print("I2C_RATE_800"); break;
    case I2C_RATE_1000: Serial.print("I2C_RATE_1000"); break;
    case I2C_RATE_1200: Serial.print("I2C_RATE_1200"); break;
    case I2C_RATE_1500: Serial.print("I2C_RATE_1500"); break;
    case I2C_RATE_1800: Serial.print("I2C_RATE_1800"); break;
    case I2C_RATE_2000: Serial.print("I2C_RATE_2000"); break;
    case I2C_RATE_2400: Serial.print("I2C_RATE_2400"); break;
    case I2C_RATE_2800: Serial.print("I2C_RATE_2800"); break;
    case I2C_RATE_3000: Serial.print("I2C_RATE_3000"); break;
    }
    Serial.printf(" : %d us\n",deltatime);
}
