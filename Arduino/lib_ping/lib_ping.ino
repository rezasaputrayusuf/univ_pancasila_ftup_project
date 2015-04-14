const int pingPin1 = 8;
const int pingPin2 = 9;

void setup() {
  Serial.begin(9600);
}

long duration1, duration2, inches, cm1, cm2;

void loop()
{
  long data1 = ping1();
  Serial.print(data1);
  Serial.print(" ");
  long data2 = ping2();
  Serial.println(data2);
//  if(data1 < data2){
//    Serial.println("kiri < kanan");
//  }else {
//    Serial.println("kanan < kiri");
//  }
//  delay(10);
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
    cm1 = microsecondsToCentimeters1(duration1);
    return cm1;
}

long ping2() {
    pinMode(pingPin2, OUTPUT);
    digitalWrite(pingPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin2, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin2, LOW);
    
    pinMode(pingPin2, INPUT);
    duration2 = pulseIn(pingPin2, HIGH);
    cm2 = microsecondsToCentimeters2(duration2);
    return cm2;
}

long microsecondsToCentimeters1(long microseconds1)
{
  return microseconds1 / 29 / 2;
}
long microsecondsToCentimeters2(long microseconds2)
{
  return microseconds2 / 29 / 2;
}
