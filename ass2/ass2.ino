#include "LedControl.h"

LedControl lc = LedControl(12,11,10,1);

char num_vec[5];
int on_vec[5];
int count, ch;
String srl, str;

void setup() {
  Serial.begin(9600);
  Serial.println("IFPB - Campus Joao Pessoa - Le da serial e escreve no display");
  Serial.println("Aluno: Rychard Guedes - 20122610037");
  Serial.println("-------------------------------------------------------------");
  lc.shutdown(0,false);  
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  count = 0;
}

void loop() {

  if(Serial.available()){
    ch = Serial.read();
    
    if(ch == 13){
      int i;
      count--;
      for(i = 4; i > -1 and count > -1; i--, count--)
        num_vec[i] = num_vec[count];
      for(i; i > -1; i--)
        num_vec[i] = '0';
      count = 5;
    } else {
      num_vec[count] = char(ch);
      str = char(ch);
      Serial.print(str);
      count++;
    }
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
