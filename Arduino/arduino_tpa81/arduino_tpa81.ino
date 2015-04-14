/********************************************
*    arduino example for TPA81 and LCD03    *
*         TPA81 controlled by I2C           *
*        LCD03 controlled by serial         *
*                                           *
*         By James Henderson 2012           *
********************************************/

#include <Wire.h>
#include <SoftwareSerial.h>

#define ADDRESS             0x68                                   // Address of TPA81
#define SOFTREG             0x00                                   // Byte for software version
#define AMBIANT             0x01                                   // Byte for ambiant temperature

#define LCD_RX              0x02                                   // Pin for rx
#define LCD_TX              0x03                                   // Pin for tx
#define LCD03_HIDE_CUR      0x04
#define LCD03_CLEAR         0x0C
#define LCD03_SET_CUR       0x02
#define LCD03_RETURN        0x0D

SoftwareSerial lcd_03 = SoftwareSerial(LCD_RX, LCD_TX);  // Defines serial port for LCD03

int temperature[] = {0,0,0,0,0,0,0,0};                   // Array to hold temperature data

void setup(){
  Serial.begin(9600);                                    // Starts software serial port for LCD03
  Wire.begin();
  delay(100);                                            // Wait to make sure everything is powerd up
  
  Serial.write(LCD03_CLEAR);    
  Serial.write(LCD03_HIDE_CUR);
  byte software = getData(SOFTREG);                       // Get software version 
  Serial.print("TPA81 Example  V:");
  Serial.print(software);                                // Print software version to the screen
}
  
void loop(){
  for(int i = 0; i < 8; i++){                            // Loops and stores temperature data in array
  temperature[i] = getData(i+2);
  }
  
  Serial.write(LCD03_SET_CUR);                            
  Serial.write(21);                                      // Moves cursor to space 21

  for(int x = 0; x < 8; x++){                            // Loop prints each member of temperature to LCD03 followed by a space
    if(x==4)                                             // If x is 4 perform a carriage return to format the results on the LCD03 for easier reading
      Serial.write(LCD03_RETURN); 
    Serial.print(temperature[x]);
    Serial.print(" ");
    delay(50);                                           // Wait befor printing next value to give time for everything to be sent
  }
  
  Serial.write(LCD03_RETURN);                          
  int ambiantTemp = getData(AMBIANT);                    // Get reading of ambiant temperature and print to LCD03 screen
  Serial.print("Ambiant: ");
  Serial.print(ambiantTemp);
}

byte getData(byte reg){                                   // Function to receive one byte of data from TPA81
  Wire.beginTransmission(ADDRESS);                        // Begin communication with TPA81
    Wire.write(reg);                                      // Send reg to TPA81
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 1);                           // Request 1 byte
  while(Wire.available() < 1);                            // Wait for byte to arrive
  byte data = Wire.read();                                // Get byte
  return(data);                                           // return byte
}
