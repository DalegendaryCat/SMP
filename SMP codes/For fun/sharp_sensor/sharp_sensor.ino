#include <SharpIR.h>

/* Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
*/
SharpIR mySensor(SharpIR::GP2Y0A02YK0F, A0);
void setup() {
  Serial.begin(9600);
}

void loop() {
  int distance_cm = mySensor.getDistance();
  Serial.print("Mean distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  delay(1000);
}
