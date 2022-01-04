int IRSensor1 = 7; // connect ir sensor to arduino pin 7
int IRSensor2 = 8;
int drop =0;

void setup() {
  pinMode (IRSensor1, INPUT); // sensor pin7 INPUT
  pinMode (IRSensor2, INPUT); // sensor pin8 INPUT
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop(){
  int statusSensor1 = digitalRead (IRSensor1);
  int statusSensor2 = digitalRead (IRSensor2);
  if (statusSensor2 == 1){
    drop++;
    Serial.print(drop);
    Serial.print("\n");
    delay(100);
  }
}
