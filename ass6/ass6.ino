//Rychard Guedes - 20122610037

#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int v2 = A1;
bool st, continua;
int ent;                                        // ent = 0, peso / ent = 1, altura
char tecla_continua;
float peso, altura, imc;                        
int tecla_mediana[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int mapa[4][4] = {                        // neste exemplo eh mostrado o mapa das teclas
  {876,720,599,525},
  {441,398,358,330},
  {316,294,271,255},
  {240,227,213,203}
};
const char tecla[4][4] = {
  {'7','8','9','.'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};

void displayPesoAltura(int num){
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  if (num == 0){
    lcd.print("PESO: ");
    Serial.print("Peso: ");
  } else {
    lcd.print("ALTURA: ");
    Serial.print("Altura: ");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("IFPB - Campus Joao Pessoa - Calculo IMC com teclado analogico e display LCD");
  Serial.println("Rychard Guedes - 20122610037");
  Serial.println("===========================================================================");
  lcd.begin(16,2);
  lcd.print("CALCULO DE IMC");
  ent = 0;
  continua = true;
}
      
void loop() {
  if(continua){
    displayPesoAltura(ent);
    peso = ler_num();
    Serial.println();
    
    ent++;
    
    displayPesoAltura(ent);
    altura = ler_num();
    Serial.println();
   
    imc = peso/((altura*altura)/10000);
  
    lcd.clear();
    lcd.home();
    if(imc < 17)
      lcd.print("MT ABAIXO PESO");
    else if (imc >= 17 and imc < 18.5)
      lcd.print("ABAIXO DO PESO");
    else if (imc >= 18.5 and imc < 25)
      lcd.print("PESO NORMAL");
    else if (imc >= 25 and imc < 30)
      lcd.print("ACIMA DO PESO");
    else if (imc >= 30 and imc < 35)
      lcd.print("OBESIDADE I");
    else if (imc >= 35 and imc < 40)
      lcd.print("OBESIDADE II");
    else if (imc >= 40)
      lcd.print("OBESIDADE III");
      
    lcd.setCursor(0,1);
    lcd.print("IMC: ");
    lcd.print(imc);
    Serial.print("IMC: ");
    Serial.println(imc);
    tecla_continua = ler_teclado();
    lcd.clear();
    lcd.print("APERTE ON/C PARA");
    lcd.setCursor(0,1);
    lcd.print("CONTINUAR");
    delay(200);
    tecla_continua = ler_teclado();
    if(tecla_continua != 'C')
      continua = false;
    else 
      setup();
  } else {
    lcd.clear();
    lcd.noDisplay();
  }
  
}

char ler_teclado(){
  int adc = 0;
  int cont;
  char r = 'M';
  
  cont = 0;
  ler_tecla();                        // normalmente a primeira leitura é descartada
  
  while(cont < 10 ){ 
    adc = ler_tecla();                // 0 ... 1023
    delay(2);
    tecla_mediana[cont] = adc;
    cont++;
  } 
  
  r = veja((tecla_mediana[4]+tecla_mediana[5])/2);

  if(r == 'w')
    return ler_teclado();
  else
    return r;
}

char veja(int r1){
  int st;
  char m = 'w';
  
  st = 0;
  for(int i = 0 ; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if((r1 >= mapa[i][j] - 5) && (r1 <= mapa[i][j] + 5)) {
        m = tecla[i][j];
        st = 1;
        break;
      } 
    }
    if(st)
      break;
  }
  return m;
}

int ler_tecla() {
  int ler = 0;
  
  while(1) { 
    ler = analogRead(v2);           // ler tensao analogica (ADC => 0 ... 1023)
    if (ler)                        // tensao > 0
      break;
  }
  return ler;                       // retorna valor entre 0 ...1023
}

float ler_num(){
  char tecla = 0;
  bool flt = true;
  String num_s = "";
  int count_flt = 0;
  
  while(tecla != 'C' or num_s.toFloat() <= 0){
    if (tecla == '.'){
      if(flt){
        Serial.print(tecla);
        lcd.print(tecla);
        num_s += tecla;
        flt = false;
      }
    } else if (tecla == 'x'){
      num_s = "";
      flt = true;
      Serial.println("Numero deletado");
      Serial.println("Numero novo: ");
      displayPesoAltura(ent);
    } else if (tecla == '+' or tecla == '=' or tecla == '-' or tecla == 'C'){
      
    } else if (count_flt > 0){
       
    } else if (tecla != 0){
      Serial.print(tecla);
      lcd.print(tecla);
      num_s += tecla;
      tecla = 0;
      if (!flt)
        count_flt++;
    }
    tecla = ler_teclado();
    delay(100);
  }
  return num_s.toFloat();
}

