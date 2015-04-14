// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
const int pingPin1 = 7;

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;
long duration1,cm1;

void loop()
{
  long data1 = ping1();
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(data1);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(100);
}

long ping1() {
    pinMode(pingPin1, OUTPUT);
    digitalWrite(pingPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin1, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin1, LOW);
    
    pinMode(pingPin1, INPUT);
    duration1 = pulseIn(pingPin1, HIGH);
    cm1 = microsecondsToCentimeters(duration1);
    return cm1;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
