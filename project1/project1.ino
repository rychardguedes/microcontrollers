#include "LedControl.h"

LedControl lc1 = LedControl(12,11,10,1);
LedControl lc2 = LedControl(9,7,8,1);
char num_vec[5] = {'a', 'p', ' ', '_', '-'};
float peso;
int teste, cont, total;

const int mapa_analog[4][4] = {
  {876,720,599,525},
  {441,398,358,330},
  {316,294,271,255},
  {240,227,213,203}
};

const char mapa_tecla[4][4] = {
  {'7','8','9','.'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};

void setDisplay(){
  lc1.clearDisplay(0);
  lc1.setChar(0, 0, 'P', false);
  lc1.setChar(0, 1, 'A', false);
  lc1.setChar(0, 2, '_', false);
  lc1.setChar(0, 3, '=', false);
  lc1.setChar(0, 4, ' ', false);
  lc1.setChar(0, 5, '1', false);
  lc1.setChar(0, 6, '2', false);
  lc1.setChar(0, 7, '3', false);
  //for (int i = 0; i < 5; i++)
  //  lc.setChar(0, i, num_vec[i], false);
}

void setDisplay2(){
  lc1.clearDisplay(0);
  lc1.setChar(0, 0, '0', false);
  lc1.setChar(0, 1, '1', false);
  lc1.setChar(0, 2, '2', false);
  lc1.setChar(0, 3, '3', false);
  lc1.setChar(0, 4, '4', false);
  lc1.setChar(0, 5, '5', false);
  lc1.setChar(0, 6, '6', false);
  lc1.setChar(0, 7, '7', false);
  //for (int i = 0; i < 5; i++)
  //  lc.setChar(0, i, num_vec[i], false);
}

void setAllShutdown(LedControl *lc){
  for(int index = 0; index < lc->getDeviceCount(); index++)
    lc->shutdown(index,false); 
}

char ler_tecla(int sel_dig, int sel_max){
  int tecla = leitura_analogica(sel_dig, sel_max);
  int i, leitura_mediana[10];
  for(i = 0; i < 10; i++){
    tecla = leitura_analogica(sel_dig, sel_max);
    delay(2);
    leitura_mediana[i] = tecla;
  }
  delay(150);
  return decodifica((leitura_mediana[4] + leitura_mediana[5])/2);  
}

int leitura_analogica(int sel_dig, int sel_max){
  int ler = 0;
  boolean pisca_bool = true;
  char pisca_char;
  unsigned long t1 = millis(), t2 = millis();
  while(1){ 
    
    t2 = millis();
    if(t2 - t1 > 500){
      t1 = millis();
      pisca_char = pisca_bool ? '_' : ' ';
      sel_max == 1 ? lc1.setChar(0, sel_dig, pisca_char, false) : lc2.setChar(0, sel_dig, pisca_char, false);
      pisca_bool = !pisca_bool;
    }
    ler = analogRead(A0);           // ler tensao analogica (ADC => 0 ... 1023)
    if (ler){                        // tensao > 0
      break;
    }
  }
  return ler;                       // retorna valor entre 0 ...1023
}

char decodifica(int analog){
  for(int i = 0 ; i < 4; i++)
    for(int j = 0; j < 4; j++)
      if((analog >= mapa_analog[i][j] - 5) && (analog <= mapa_analog[i][j] + 5))
        return mapa_tecla[i][j];
  return 'p';
}

void setup() {
  Serial.begin(9600);
  Serial.println("Ei mizera");
  setAllShutdown(&lc1);
  setAllShutdown(&lc2);
  lc1.setIntensity(0,8);
  lc1.clearDisplay(0);
  lc2.setIntensity(0,8);
  lc2.clearDisplay(0);
  analogReference(DEFAULT);
  
  //digitalWrite(A0, HIGH);  // set pullup on analog pin 0 
  pinMode(A0, INPUT);
}

void loop() {
  int i;
  char digito;
  String numero;
  lc1.setChar(0, 0, 'P', false);
  lc1.setChar(0, 1, '=', false);
  lc2.setChar(0, 0, 'A', false);
  lc2.setChar(0, 1, '=', false);
  
  for(i = 2; i < 8; i++){
    digito = ler_tecla(i, 1);
    numero += digito;
    lc1.setChar(0, i, digito, false);
  }
  

  for(i = 2; i < 8; i++){
    digito = ler_tecla(i, 2);
    numero += digito;
    lc2.setChar(0, i, digito, false);
  }
  delay(2000);
  lc1.clearDisplay(0);
  lc2.clearDisplay(0);
}
