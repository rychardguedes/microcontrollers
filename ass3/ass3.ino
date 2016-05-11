// Rychard Guedes - 20122610037

#include "LedControl.h"

LedControl lc = LedControl(12,11,10,1);

const int dec = 7, inc = 6;
boolean sub1, sub2;
int num_vec[5] = {0,0,0,0,0};
long count;

void defineNumbers(){
  num_vec[0] = count/10000;
  num_vec[1] = (count%10000)/1000;
  num_vec[2] = ((count%10000)%1000)/100;
  num_vec[3] = (((count%10000)%1000)%100)/10;
  num_vec[4] = ((((count%10000)%1000)%100)%10);
}

void showSerial(){
  Serial.println();
  Serial.print("Count: ");
  Serial.println(count);
  Serial.print("Numero digitado por completo: ");
  Serial.print(num_vec[0]);
  Serial.print(num_vec[1]);
  Serial.print(num_vec[2]);
  Serial.print(num_vec[3]);
  Serial.print(num_vec[4]);
  Serial.println();
  Serial.println();
}

void setDisplay(){
  lc.clearDisplay(0);
  lc.setChar(0,0,num_vec[0],false);
  lc.setChar(0,1,num_vec[1],false);
  lc.setChar(0,2,num_vec[2],false);
  lc.setChar(0,3,num_vec[3],false);
  lc.setChar(0,4,num_vec[4],false);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Serial iniciada");
  Serial.println("---------------");
  lc.shutdown(0,false);     // Wake the lc up
  lc.setIntensity(0,8);     // Set the brightness to a medium values 
  lc.clearDisplay(0);       // and clear the display 
  count = 54500;
  sub1 = sub2 = false;
  defineNumbers();
  setDisplay();
}


void loop() {

  if(!digitalRead(dec)){
    sub1 = true;
  }
  if(digitalRead(dec) && sub1){
    sub1 = false;
    count -= 155;
    if(count < 0)
      count = 0;
    Serial.println("Decremento");
    defineNumbers();
    showSerial();
    setDisplay();
  }

  if(!digitalRead(inc)){
    sub2 = true;
  }
  if(digitalRead(inc) && sub2){
    sub2 = false;
    count += 205;
    if(count > 99999)
      count = 99999;
    Serial.println("Incremento");
    defineNumbers();
    showSerial();
    setDisplay();
  }
  
}


