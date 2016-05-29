#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int ncol = 4, nlin = 4;                       // Quantidade de linhas e colunas da matriz de teclas
const int col[] = {14, 15, 16, 17}, lin[] = {5, 4, 3, 2};   // Vetores de teclas

boolean neg = true, flt = true, show_msg = true, fim = false;
char tecla;
int coef_n = 0, qtd_raizes;
float num_f, coef[3] = {0, 0, 0}, x1, x2;
String num_s = "";
 

const char keymap[4][4] =  // mapa das teclas
{
      { '7', '8', '9', '.' } ,
      { '4', '5', '6', 'D' } ,
      { '1', '2', '3', '-' } ,
      { 'N', '0', '=', '+' }
};

char getKey(){
  char key = 0;
  int st = 0;
  
  for(int i = 0; i < nlin and st == 0; i++){
    for(int j = 0; j < nlin; j++){                        // Seta um dos pinos como LOW
      if(i == j)
        digitalWrite(lin[j], LOW);
      else
        digitalWrite(lin[j], HIGH);
    }

    for(int j = 0; j < ncol; j++){                       // Varre os pinos para saber qual está LOW
      if (digitalRead(col[j]) == LOW){
        delay(20);                                    // Estabilização
        while(digitalRead(col[j]) == LOW);
        key = keymap[i][j];
        st = 1;
        break;
      }
    } 
  }
  return key;
}

int bhaskara(float a, float b, float c){

  float delta = b*b - 4*a*c;

  if(delta < 0)
    return 0;
  else if (delta == 0){
    x1 = x2 = -b/(2*a);
    return 1;
  } else {
    x1 = (-b + sqrt(delta))/(2*a);
    x2 = (-b - sqrt(delta))/(2*a);
    return 2;
  }
}

void setup() {
 
  for(int i = 0; i < ncol; i++){
    pinMode(col[i], INPUT);
    digitalWrite(col[i], HIGH);
  }
  for(int i = 0; i < nlin; i++)
    pinMode(lin[i], OUTPUT); 

  Serial.begin(9600);
  Serial.println("Pinos setados");

  lcd.begin(16, 2);
  lcd.print("EQUACAO 2 GRAU");
  delay(1000);
  lcd.clear();
  lcd.print("INSIRA A:");
  lcd.setCursor(0, 1);
  lcd.blink();
}

void loop() {
  tecla = getKey();

  if(tecla != 0){
    Serial.print(tecla);

    if(fim and tecla == 'D'){
      setup();
    }

      
    if(tecla == '='){
      
      coef[coef_n] = num_s.toFloat();
      Serial.println();
      Serial.print("Numero lido: ");
      Serial.println(coef[coef_n++]);
      Serial.println("coef_n: ");
      Serial.println(coef_n);
      num_s = "";

      if(coef_n == 1){
        Serial.print("Insira B: ");
        lcd.clear();
        lcd.print("INSIRA B:");
        lcd.setCursor(0, 1);
      } else if (coef_n == 2){
        Serial.print("Insira C: ");
        lcd.clear();
        lcd.print("INSIRA C:");
        lcd.setCursor(0, 1);
      }
        
        
      flt = true;
    } else if (tecla == '.'){
      if(flt){
        num_s += tecla;
        flt = false;
        lcd.print(".");
      }
    } else if (tecla == '-'){
      if (num_s.equals("")){
        num_s += tecla;
        lcd.print("-");
      }
    } else if (tecla == 'D'){
      num_s = "";
      flt = true;
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
    } else {
      num_s += tecla;
      lcd.print(tecla);
    } 
  }
  
  if (coef_n == 3){
    coef_n = 0;

    qtd_raizes = bhaskara(coef[0], coef[1], coef[2]);
    lcd.clear();
    if(qtd_raizes == 0){
      Serial.println("Não existem raizes reais");
      lcd.print("NAO EXISTEM");
      lcd.setCursor(0,1);
      lcd.print("RAIZES REAIS");
    } else {
      Serial.println("Existem raizes reais: ");
      Serial.println(x1);
      Serial.println(x2);
      lcd.print("X1 = ");
      lcd.print(x1);
      lcd.setCursor(0,1);
      lcd.print("X2 = ");
      lcd.print(x2);
    }
    Serial.println();
    delay(1000);
    setup();
  }
  
}
