const int leds[] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte b1[] = {B11111100, // 0
                   B01100000, // 1
                   B11011010, // 2
                   B11110010, // 3
                   B01100110, // 4
                   B10110110, // 5
                   B10111110, // 6
                   B11100000, // 7
                   B11111110, // 8
                   B11110110  // 9
};

bool inc, sub1, sub2, mplx;
int uni, ten, i, j;
const int del = 5, up = 14, down = 15, m1 = 3, m2 = 4;
unsigned long t1, t2, t3, t4;

void write7seg(byte t){
  for(i = 0; i < 8; i++){
    digitalWrite(leds[i], bitRead(t,7-i));
  }
}

void setup()
{
  for (int j = 0; j < 8; j++)
    pinMode(leds[j], OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  uni = 0;
  ten = 0;
  t1 = millis();
  t2 = millis();
  t3 = millis();
  t4 = millis();
  sub1 = false;
  sub2 = false;
  inc = true;
  mplx = true;
  Serial.begin(9600);
  Serial.println("IFPB - Campus Joao Pessoa - Contador (incremento/decremento) 0 - 99");
  Serial.println("Aluno: Rychard Guedes - 20122610037");
}

void loop()
{

  t4 = millis();
  if(t4 - t3 > 5)
  {
    t3 = millis();
    if(mplx){
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      write7seg(b1[ten]);
      mplx = false;
    } else {
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      write7seg(b1[uni]);
      mplx = true;
    }
  }
  
  t2 = millis();
  if(t2 - t1 > 1000)
  {
    t1 = millis();
    
    if(inc){
      uni++;
      if(uni == 10){
        uni = 0;
        ten++;
        
        if (ten == 10)
          ten = 0;
      }
    } else {
      uni--;
      if(uni == -1){
        uni = 9;
        ten--;
        
        if (ten == -1)
          ten = 9;
      }
    }
  }

  if(!digitalRead(up)){
    sub1 = true;
  }
  if(digitalRead(up) && sub1){
    sub1 = false;
    inc = true;
    Serial.println("Botao de incrementar");
  }

  if(!digitalRead(down)){
    sub2 = true;
  }
  if(digitalRead(down) && sub2){
    sub2 = false;
    inc = false;
    Serial.println("Botao de decrementar");
  }
  
}
