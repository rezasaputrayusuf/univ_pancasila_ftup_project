const int pinButton = 4;
const int pinButton2 = 5;
const int pinLed = 7;
int buttonState = 0;
int buttonState2 = 0;

uint8_t target = 0x44;

void setupButton() {
    Serial.begin(9600);
    pinMode(pinButton, INPUT);
    pinMode(pinButton2, INPUT);
    pinMode(pinLed, OUTPUT);
}

void actionButton() {
    buttonState = digitalRead(pinButton);
    buttonState2 = digitalRead(pinButton2);
    if (buttonState==HIGH) {
        buttonState=1;
        Wire.beginTransmission(target);
        Wire.write(""); 
        Wire.write(1);
        Wire.endTransmission(); 
    } else {
        buttonState=0;
    }
    
    if (buttonState2==HIGH) {
        buttonState2=1;
        Wire.beginTransmission(target);
        Wire.write(""); 
        Wire.write(2);
        Wire.endTransmission(); 
    } else {
        buttonState2=0;
    }

    if (buttonState==1) {
        digitalWrite(pinLed, HIGH);
    } 
    
    else if (buttonState2==1) {
        digitalWrite(pinLed, LOW);
    }
    delay(500);
}
