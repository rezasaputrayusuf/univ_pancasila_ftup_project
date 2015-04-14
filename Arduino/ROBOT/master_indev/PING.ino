#include <Ping.h>

Ping ping = random(1, 100);

void Ping(){
  ping.fire();
  Serial.print("Centimeters: ");
  Serial.print(ping.centimeters());
  Serial.println();
}
