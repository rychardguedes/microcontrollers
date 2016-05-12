// Rychard Guedes - 20122610037

#include "LedControl.h"

LedControl lc = LedControl(12,11,10,1);

const int dec = 7, inc = 6;
boolean sub1, sub2, off;
int num_vec[5] = {0,0,0,0,0}, on_vec[5] = {0,0,0,0,0};
long count;

void defineNumbers(){
  num_vec[0] = count/10000;
  num_vec[1] = (count%10000)/1000;
  num_vec[2] = ((count%10000)%1000)/100;
  num_vec[3] = (((count%10000)%1000)%100)/10;
  num_vec[4] = ((((count%10000)%1000)%100)%10);

  boolean off = true;
  for(int i = 0; i < 4; i++){
    if(num_vec[i] != 0){
      off = false;
    }
    if(off){
      on_vec[i] = 1; 
    } else {
      on_vec[i] = 0;
    }
  }
}

void showSerial(){
  Serial.print("Novo numero: ");
  Serial.println(count);
  Serial.println();
}

void setDisplay(){
  lc.clearDisplay(0);
  for(int i = 0; i < 5; i++)
    lc.setChar(on_vec[i],i,num_vec[i],false);
}

void setup() {
  Serial.begin(9600);
  Serial.println("IFPB - Campus Joao Pessoa - Contador (incremento/decremento) 0 - 99999");
  Serial.println("Aluno: Rychard Guedes - 20122610037");
  Serial.println("----------------------------------------------------------------------");
  lc.shutdown(0,false);     // Wake the lc up
  lc.setIntensity(0,8);     // Set the brightness to a medium values 
  lc.clearDisplay(0);       // and clear the display 
  count = 500;
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


