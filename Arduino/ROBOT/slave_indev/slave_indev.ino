#include <i2c_t3.h>
#include <LiquidCrystal.h>


// Command definitions
#define WRITE    0x10
#define READ     0x20
#define SETRATE  0x30
// Function prototypes
void receiveEvent(size_t len);

//
// Setup
//
void setup() {
    pinMode(LED_BUILTIN,OUTPUT); // LED

    // Setup for Slave mode, address 0x44, pins 18/19, external pullups, 400kHz
    Wire.begin(I2C_SLAVE, 0x44, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

    // register events
    Wire.onReceive(receiveEvent);
    Serial.begin(9600); 
    setupLCD();
    printLCD("ENGINE STANDBY...", 0, 0);
}

void loop() {
    digitalWrite(LED_BUILTIN,HIGH); // double pulse LED while waiting for I2C requests
    delay(10);                      // if the LED stops the slave is probably stuck in an ISR
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
    delay(880);
}

void receiveEvent(size_t len) {
    while(1 < Wire.available()) {
        char c = Wire.read(); 
        Serial.print(c);  
    }
    int x = Wire.read(); 
    if(x==2){  
      char string[] = {'E', 'N', 'G', 'I', 'N', 'E', ' ', 'S', 'T', 'A', 'N', 'D', 'B', 'Y', '.', '.'};
      clear();
      int a = sizeof(string);
       for(int i=0; i<a; i++){
        printLCD(string[i], 1, 1);
        delay(100);
       }
    } else if(x==1){
      clear();
      printLCD("ENGINE STARTED !!", 1, 1);
    } 
}

