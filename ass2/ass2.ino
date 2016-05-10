//We always have to include the library
#include "LedControl.h"

LedControl lc = LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
char num_vec[5];
int on_vec[5];
int count, ch;
String srl, str;


void setup() {
  Serial.begin(9600);
  Serial.println("Serial iniciada");
  Serial.println("---------------");
  lc.shutdown(0,false);     // Wake the lc up
  lc.setIntensity(0,8);     // Set the brightness to a medium values 
  lc.clearDisplay(0);       // and clear the display 
  count = 0;
}


void loop() {

  if(Serial.available()){
    ch = Serial.read();
    num_vec[count] = char(ch);
    str = char(ch);
    Serial.print(str);
    count++;
    if(count == 5){
      Serial.println();
      Serial.print("Numero digitado por completo: ");
      Serial.print(num_vec[0]);
      Serial.print(num_vec[1]);
      Serial.print(num_vec[2]);
      Serial.print(num_vec[3]);
      Serial.print(num_vec[4]);
      Serial.println();
      Serial.println();
      boolean off = true;
      for(int i = 0; i < 4; i++){
        if(num_vec[i] != '0'){
          off = false;
        }
        if(off){
          on_vec[i] = 1; 
        } else {
          on_vec[i] = 0;
        }
      }
      on_vec[4] = 0;
      lc.clearDisplay(0);
      lc.setChar(on_vec[0],0,num_vec[0],false);
      lc.setChar(on_vec[1],1,num_vec[1],false);
      lc.setChar(on_vec[2],2,num_vec[2],false);
      lc.setChar(on_vec[3],3,num_vec[3],false);
      lc.setChar(on_vec[4],4,num_vec[4],false);
      count = 0;
    }
  }
}
