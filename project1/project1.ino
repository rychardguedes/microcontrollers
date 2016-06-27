#include "LedControl.h"

LedControl lc = LedControl(12,10,11,1);
char num_vec[5] = {'a', 'p', ' ', '_', '-'};


void setDisplay(){
  lc.clearDisplay(0);
  for (int i = 0; i < 5; i++)
    lc.setChar(0, i, num_vec[i], false);
}

void setup() {
  lc.shutdown(0,false);  
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  //setDisplay();
  lc.setChar(0, 0, 1, false);
}
