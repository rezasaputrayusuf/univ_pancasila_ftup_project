#include <Ping.h>

Ping ping1 = Ping(8);
Ping ping2 = Ping(10);
Ping ping3 = Ping(7);
Ping ping4 = Ping(11);
Ping ping5 = Ping(12);
Ping ping6 = Ping(13);
Ping ping7 = Ping(14);
//Ping ping8 = Ping(15);

long previousMillis = 0;
long interval = 100; 

void setup(){
  Serial.begin(9600);
}

void loop(){
   unsigned long currentMillis = millis();
   if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      bacaping();
  }
  
}

void bacaping() {
    ping1.fire();
    ping2.fire();
    //ping3.fire();
    ping4.fire();
    ping5.fire();
    ping6.fire();
    ping7.fire();
    
    Serial.print(ping1.centimeters());
    Serial.print("  ");
    Serial.print(ping2.centimeters());
    Serial.print("  ");
   // Serial.print(ping3.centimeters());
    Serial.print("  ");
    Serial.print(ping4.centimeters());
    Serial.print("  ");
    Serial.print(ping5.centimeters());
    Serial.print("  ");
    Serial.print(ping6.centimeters());
    Serial.print("  ");
    Serial.print(ping7.centimeters());
    Serial.println();
}
