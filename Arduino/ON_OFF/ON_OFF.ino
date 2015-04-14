const int ledPin =  27;
int ledState = LOW; 
long previousMillis = 0;
long interval = 1000;


void setup() {
    pinMode(ledPin, OUTPUT);
    buttonsetup();
}

void loop() {

    buttonloop();
}

