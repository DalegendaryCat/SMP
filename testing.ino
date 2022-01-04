#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.34          //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;

#include <Servo.h>
Servo myservo; 

int acidorbase = 1; //remove =1 later

int pos = 0;  
int spin(int deg, int intvl) {
  if (pos <= deg){
    float spintime = intvl / int (deg - pos);
    for (pos = pos; pos<deg; pos += 1){
      myservo.write(pos);
      delay(spintime);
    }
  }
  else{
    float spintime = intvl / int (pos-deg);
    for (pos = pos; pos>deg; pos -= 1){
      myservo.write(pos);
      delay(spintime);
    }
  }
}


int IRSensor1 = 7; // connect ir sensor to arduino pin 7
int IRSensor2 = 8;
int drop =0;
float endPH = 69; //remove =69 later

void setup(void){
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("pH meter experiment!");    //Test the serial monitor
  alpha4.begin(0x70);  // pass in the address
  alpha4.clear();
  myservo.attach(9); 
  delay(10);
  
  pinMode (IRSensor1, INPUT); // sensor pin7 INPUT
  pinMode (IRSensor2, INPUT); // sensor pin8 INPUT

  /*Serial.print("Input your end point pH: "); //get user input of endpoint
  while (Serial.available() == 0) {
  }
  endPH = Serial.parseFloat();

  /*while(Serial.available()>0){
    Serial.read();
  }
  Serial.print("Your end pH is: ");
  Serial.print(endPH);
  Serial.print("\n"); 
  */
  
  /*Serial.print("Input solution in beaker, 1 for acid, 2 for base: "); //get user input of endpoint
  while (Serial.available() == 0) {
  }
  acidorbase = Serial.parseFloat();

  while(Serial.available()>0){
    Serial.read();
  }
  
  
  Serial.print("current solution in beaker is: ");
  if(acidorbase == 1){
    Serial.print("acid");
  }
  else{
    Serial.print("base");
  }
  Serial.print("\n");
  */ 

}


void loop(void){
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
    
  int statusSensor1 = digitalRead (IRSensor1); //Infrared sensors
  int statusSensor2 = digitalRead (IRSensor2);
  if(acidorbase == 1){
    if (statusSensor2 == 1 and pHValue < endPH){
       drop++;
       //Serial.print(drop);
       //Serial.print("\n");
       delay(100);
    }
  }
  
  else if (acidorbase == 2){
     if (statusSensor2 == 1 and pHValue > endPH){
       drop++;
       //Serial.print(drop);
       //Serial.print("\n");
       delay(100);
     }
  }
  
  if(millis()-samplingTime > samplingInterval){
  
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  
  if(millis() - printTime > printInterval){   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
    //Serial.print("pH value: ");
    Serial.print(pHValue,2);
    Serial.print(",");
    Serial.print(drop);
    Serial.print(",");
    Serial.println();
    digitalWrite(LED,digitalRead(LED)^1);
    printTime=millis();
  }

   int tens;
   int ones;
   int onedp;
   int twodp;
   int pHValueInt;
   int pHValueOneDp;
   int pHValueTwoDp;
   int pHValueOnes;
   int pHValueTens;
   alpha4.writeDisplay();

  
  if(acidorbase == 1){
    if (pHValue < endPH - 3){ //change to endph
      spin(160,1000);
      alpha4.writeDigitRaw(1, 0x4000);
      if (pHValue > 9.99) {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        pHValueTens = pHValueOnes / 10;
        tens = pHValueTens % 10;
        alpha4.writeDigitAscii(0, tens + '0');
    
      } 
    
      else {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        alpha4.writeDigitAscii(0, ' ');
      }
    }
    
    else if (pHValue < endPH){ //6
      spin(160,1000);
      alpha4.writeDigitRaw(1, 0x4000);
      if (pHValue > 9.99) {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        pHValueTens = pHValueOnes / 10;
        tens = pHValueTens % 10;
        alpha4.writeDigitAscii(0, tens + '0');
      
      } 
    
      else {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        alpha4.writeDigitAscii(0, ' ');
      }
    }
    
    else if (pHValue > endPH){ //6
      spin(90,1000);
      alpha4.writeDigitAscii(0, 'D');
      alpha4.writeDigitAscii(1, 'o');
      alpha4.writeDigitAscii(2, 'n');
      alpha4.writeDigitAscii(3, 'e');
     }
     
  }
  
  else if(acidorbase == 2){
    if (pHValue > endPH + 3){ //change to endph
      spin(160,1000);
      alpha4.writeDigitRaw(1, 0x4000);
      if (pHValue > 9.99) {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        pHValueTens = pHValueOnes / 10;
        tens = pHValueTens % 10;
        alpha4.writeDigitAscii(0, tens + '0');
      
      } 
    
      else {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        alpha4.writeDigitAscii(0, ' ');
      }
     }
    
    else if (pHValue > endPH){ //6
      spin(160,1000);
      alpha4.writeDigitRaw(1, 0x4000);
      if (pHValue > 9.99) {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        pHValueTens = pHValueOnes / 10;
        tens = pHValueTens % 10;
        alpha4.writeDigitAscii(0, tens + '0');
      
      } 
    
      else {
        pHValueInt = int(pHValue * 100);
        twodp = pHValueInt % 10;
        alpha4.writeDigitAscii(3, twodp + '0');
        pHValueOneDp = pHValueInt / 10;
        onedp = pHValueOneDp % 10;
        alpha4.writeDigitAscii(2, onedp + '0');
        pHValueOnes = pHValueOneDp / 10;
        ones = pHValueOnes % 10;
        alpha4.writeDigitAscii(1, ones + '0');
        alpha4.writeDigitAscii(0, ' ');
      }
    }
    
    else if (pHValue < endPH){ //6
      spin(90,1000);
      alpha4.writeDigitAscii(0, 'D');
      alpha4.writeDigitAscii(1, 'o');
      alpha4.writeDigitAscii(2, 'n');
      alpha4.writeDigitAscii(3, 'e');
     }
     
   
  }
  
}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }
  else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
