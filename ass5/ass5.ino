const int ncol = 4, nlin = 4;                       // Quantidade de linhas e colunas da matriz de teclas
const int col[] = {A0, A1, A2, 7}, lin[] = {11, 10, A4, A5};   // Vetores de teclas

boolean neg = true, flt = true;
char tecla;
int coef_n = 0;
float num_f, coef[3] = {0, 0, 0};
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

String getNum(){
  
  

  
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
  
}

void loop() {
  tecla = getKey();

  if(tecla != 0){
    Serial.print(tecla);
    if(tecla == '='){
      coef[coef_n] = num_s.toFloat();
      Serial.println();
      Serial.print("Numero lido: ");
      Serial.println(coef[coef_n++]);
      num_s = "";
      flt = true; 
    } else if (tecla == '.'){
      if(flt){
        num_s += tecla;
        flt = false;
      }
    } else if (tecla == '-'){
      if (num_s.equals(""))
        num_s += tecla;
    } else if (tecla == 'D'){
      num_s = "";
      flt = true;
    } else {
      num_s += tecla;
    } 
  }
  if (coef_n == 3)
    coef_n = 0;
  /*(tecla = getNum(); //getKey();

  if(tecla != 0){
    Serial.print("Tecla lida: ");
    Serial.println(tecla);
  }*/
  
}
