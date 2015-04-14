const int id = 1;
int recived_id, recived_value;

void setup(){
  Serial.begin(9600);
}

void loop() {
    read_data();
    if(recived_id == id) { 
        do_motor_step(recived_value);
    }
}
