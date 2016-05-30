// Rychard Guedes

#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int ncol = 4, nlin = 4;                               // Quantidade de linhas e colunas da matriz de teclas
const int col[] = {14, 15, 16, 17}, lin[] = {5, 4, 3, 2};   // Vetores de teclas

boolean neg, flt, show_msg, fim;
char tecla;
int coef_n, qtd_raizes, count_flt;
float num_f, coef[3] = {0, 0, 0}, x1, x2;
String num_s;
 

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
        delay(20);                                       // Estabilização
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
  neg = true; 
  flt = true; 
  show_msg = false; 
  fim = false;
  coef_n = 0;
  coef[0] = 0;
  coef[1] = 0;
  coef[2] = 0;
  count_flt = 0;
  num_s = "";
  
  for(int i = 0; i < ncol; i++){
    pinMode(col[i], INPUT);
    digitalWrite(col[i], HIGH);
  }
  for(int i = 0; i < nlin; i++)
    pinMode(lin[i], OUTPUT); 
  
  Serial.begin(9600);
  Serial.println("IFPB - Campus Joao Pessoa - Equacao 2 Grau");
  Serial.println("Rychard Guedes - 20122610037");
  Serial.println("==========================================");

  lcd.begin(16, 2);
  lcd.print("EQUACAO 2 GRAU");
  delay(800);
  lcd.clear();
  lcd.print("INSIRA A:");
  lcd.setCursor(0, 1);
  lcd.blink();
}

void loop() {
  tecla = getKey();

  if(tecla != 0){
    if(show_msg and (tecla == 'N' or tecla == '=')){
      setup();
    } else if (show_msg and tecla != 0){
      lcd.noDisplay();
      while(true);
    } else if (fim) {
      show_msg = true;
      lcd.clear();
      lcd.print("APERTE ENTER OU");
      lcd.setCursor(0,1);
      lcd.print("= PARA CONTINUAR");
      
    } else if(tecla == '=' or tecla == 'N'){
      
      if(num_s.equals(""))
        coef[coef_n] = 0;
      else
        coef[coef_n] = num_s.toFloat();
      coef_n++;
      num_s = "";

      if(coef_n == 1){
        lcd.clear();
        lcd.print("INSIRA B:");
        lcd.setCursor(0, 1);
      } else if (coef_n == 2){
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
    } else if (tecla == '+'){
      
    } else if (count_flt > 0){
       
    } else {
      num_s += tecla;
      lcd.print(tecla);
      if (!flt)
        count_flt++;
    } 
  }
  
  if (coef_n == 3){
    coef_n = 0;
    Serial.println(coef[0]);
    Serial.println(coef[1]);
    Serial.println(coef[2]);
    if(coef[0] == 0){
      lcd.clear();
      lcd.print("EQUACAO DE");
      lcd.setCursor(0,1);
      lcd.print("PRIMEIRO GRAU");
    } else {
      qtd_raizes = bhaskara(coef[0], coef[1], coef[2]);
      lcd.clear();
      if(qtd_raizes == 0){
        lcd.print("NAO EXISTEM");
        lcd.setCursor(0,1);
        lcd.print("RAIZES REAIS");
      } else {
        lcd.print("X1 = ");
        lcd.print(x1);
        lcd.setCursor(0,1);
        lcd.print("X2 = ");
        lcd.print(x2);
      }
    }
    fim = true;
  }
  
}
