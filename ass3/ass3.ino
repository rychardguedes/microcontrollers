//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
const int dec = 7, inc = 6;
boolean sub1, sub2;
int num_vec[5] = {0,0,0,0,0};
unsigned long count;

void defineDisplay(unsigned long var){
  num_vec[0] = var/10000;
  num_vec[1] = (var%10000)/1000;
  num_vec[2] = (num_vec[1]%1000)/100;
  num_vec[3] = (num_vec[2]%100)/10;
  num_vec[4] = num_vec[3]%10;

  Serial.println();
  Serial.print("Count: ");
  Serial.println(var);
  Serial.print("Numero digitado por completo: ");
  Serial.print(num_vec[0]);
  Serial.print(num_vec[1]);
  Serial.print(num_vec[2]);
  Serial.print(num_vec[3]);
  Serial.print(num_vec[4]);
  Serial.println();
  Serial.println();
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
  defineDisplay(count);
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
    Serial.println("Incremento");
    defineDisplay(count);
  }

  if(!digitalRead(inc)){
    sub2 = true;
  }
  if(digitalRead(inc) && sub2){
    sub2 = false;
    count += 205;
    if(count > 99999)
      count = 99999;
    Serial.println("Decremento");
    defineDisplay(count);
  }
  
}


