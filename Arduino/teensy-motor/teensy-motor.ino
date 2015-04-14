//motor B connected between B01 and B02
int STBY = 10; //standby
int STBY1 = 17; //standby
//Right Motor Driver
//Motor A
int PWMAR = 3; //Speed control 
int AIN1R = 9; //Direction
int AIN2R = 8; //Direction
//Motor B
int PWMBR = 4; //Speed control
int BIN1R = 11; //Direction
int BIN2R = 12; //Direction

//Left Motor Driver
//Motor A
int PWMAL = 5; //Speed control 
int AIN1L = 13; //Direction
int AIN2L = 14; //Direction
//Motor B
int PWMBL = 6; //Speed control
int BIN1L = 15; //Direction
int BIN2L = 16; //Direction

void setup(){
  pinMode(STBY, OUTPUT);
  pinMode(STBY1, OUTPUT);

  pinMode(PWMAR, OUTPUT);
  pinMode(AIN1R, OUTPUT);
  pinMode(AIN2R, OUTPUT);

  pinMode(PWMBR, OUTPUT);
  pinMode(BIN1R, OUTPUT);
  pinMode(BIN2R, OUTPUT);
  
  pinMode(PWMAL, OUTPUT);
  pinMode(AIN1L, OUTPUT);
  pinMode(AIN2L, OUTPUT);

  pinMode(PWMBL, OUTPUT);
  pinMode(BIN1L, OUTPUT);
  pinMode(BIN2L, OUTPUT);
  Serial.begin(9600);
}

unsigned char c;

int pwm = 200;

void loop(){
   if (Serial.available() > 0) {
       c = Serial.read();
   }
   if(c == 'q') { pwm = 0; }
   if(c == 'w') { pwm = 50; }
   if(c == 'e') { pwm = 100; }
   if(c == 'r') { pwm = 150; }
   if(c == 't') { pwm = 200; }
   if(c == 'y') { pwm = 250; }
   if(c == 'u') { pwm = 255; }
   maju();
}

 

void maju(){
  moveR(1, pwm, 1); //motor 1, full speed, left
  moveR(2, pwm, 1); //motor 2, full speed, left
  moveL(1, pwm, 1); //motor 1, full speed, left
  moveL(2, pwm, 1); //motor 2, full speed, left
}

void mundur(){
  moveR(1, 128, 0); //motor 1, half speed, right
  moveR(2, 128, 0); //motor 2, half speed, right
  moveL(1, 128, 0); //motor 1, half speed, right
  moveL(2, 128, 0); //motor 2, half speed, right

}

void kanan(){
  moveR(1, 255, 0); //motor 1, full speed, left
  moveR(2, 255, 0); //motor 2, full speed, left
  moveL(1, 255, 1); //motor 1, full speed, left
  moveL(2, 255, 1); //motor 2, full speed, left

}

void kiri(){
  moveR(1, 255, 1); //motor 1, full speed, left
  moveR(2, 255, 1); //motor 2, full speed, left
  moveL(1, 255, 0); //motor 1, full speed, left
  moveL(2, 255, 0); //motor 2, full speed, left

}

  
void moveR(int motor, int speed, int direction){

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1R, inPin1);
    digitalWrite(AIN2R, inPin2);
    analogWrite(PWMAR, speed);
  }else{
    digitalWrite(BIN1R, inPin1);
    digitalWrite(BIN2R, inPin2);
    analogWrite(PWMBR, speed);
  }
}

void moveL(int motor, int speed, int direction){

  digitalWrite(STBY1, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1L, inPin1);
    digitalWrite(AIN2L, inPin2);
    analogWrite(PWMAL, speed);
  }else{
    digitalWrite(BIN1L, inPin1);
    digitalWrite(BIN2L, inPin2);
    analogWrite(PWMBL, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
  digitalWrite(STBY1, LOW); 
}

