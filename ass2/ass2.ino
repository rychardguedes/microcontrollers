#include "LedControl.h"

LedControl lc = LedControl(12,11,10,1);

char num_vec[5];
int on_vec[5] = {0, 0, 0, 0, 0}, count, ch;
String srl, str;

void showSerial(){
  Serial.println();
  Serial.print("Numero digitado por completo: ");
  for (int i = 0; i < 5; i++)
    Serial.print(num_vec[i]);
  Serial.println();
  Serial.println();
}

void setDisplay(){
  lc.clearDisplay(0);
  for (int i = 0; i < 5; i++)
    lc.setChar(on_vec[i],i,num_vec[i],false);
}

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
      for(i = 4; i > -1 and count > -1; num_vec[i--] = num_vec[count--]);
      for(i; i > -1; num_vec[i--] = '0');
      count = 5;
    } else {
      num_vec[count] = char(ch);
      str = char(ch);
      Serial.print(str);
      count++;
    }
    if(count == 5){
      boolean off = true;
      for(int i = 0; i < 4; i++){
        if(num_vec[i] != '0')
          off = false;
        if(off)
          on_vec[i] = 1; 
        else
          on_vec[i] = 0;
      }
      showSerial();
      setDisplay();
      count = 0;
    }
  }
}
