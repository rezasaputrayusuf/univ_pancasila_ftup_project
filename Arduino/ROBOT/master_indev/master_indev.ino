#include <i2c_t3.h>

// Command definitions
#define WRITE    0x10
#define READ     0x20
#define SETRATE  0x30

byte x = 0;
long previousMillis = 0; 
long interval = 500;

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);    // LED
    digitalWrite(LED_BUILTIN,LOW);  // LED off
    setupButton();
    Serial.begin(9600);
    // Setup for Master mode, pins 18/19, external pullups, 400kHz
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_INT, I2C_RATE_400);
}

void loop() { 
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis; 
        Write();
    }
    actionButton();   
}

void Write() {
    uint8_t target = 0x44; // slave addr

    digitalWrite(LED_BUILTIN,HIGH);
    
    Wire.beginTransmission(target);
    Wire.write(x);
    Wire.write("");
    Wire.endTransmission(); 

    digitalWrite(LED_BUILTIN,LOW);         // LED off
    Serial.print(x);
    x++;
    if(x==10) {
        x=0;
    }
}
