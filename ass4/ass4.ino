// Rychard Guedes - 20122610037

unsigned long t1, t2, t3, t4;
boolean sub1, sub2, inc;
int count, mplx;

const byte bt[] = {B11111100, // 0
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

void write7seg(byte b){
  for(int i = 0; i < 8; i++){
    digitalWrite(data, bitRead(b, i));
    digitalWrite(sclk, LOW);
    digitalWrite(sclk, HIGH);
  }
  digitalWrite(ltch, LOW);
  digitalWrite(ltch, HIGH);
  digitalWrite(ltch, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.println("IFPB - Campus Joao Pessoa - Contador com serial-paralelo");
  Serial.println("Aluno: Rychard Guedes - 20122610037");
  Serial.println("-------------------------------------------------------------");
  
  pinMode(x1, OUTPUT);
  pinMode(x2, OUTPUT);
  pinMode(x3, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(ltch, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(x1, HIGH);
  digitalWrite(x2, LOW);
  digitalWrite(x3, LOW);

  t1 = millis();
  t2 = millis();
  t3 = millis();
  t4 = millis();

  count = 0;
  sub1 = sub2 = false;
  inc = true;
  mplx = 0;
}

void loop() {
  
  t2 = millis();
  if(t2 - t1 > 5)
  {
    t1 = millis();
    if(mplx == 0){
      digitalWrite(x1, LOW);
      digitalWrite(x2, HIGH);
      digitalWrite(x3, LOW);
      if(count < 999)
        write7seg(bt[count%10]);  
      else
        write7seg(bt[(count/10)%10]); 
      ++mplx;
    } else if (mplx == 1) {
      digitalWrite(x1, HIGH);
      digitalWrite(x2, LOW);
      digitalWrite(x3, LOW);
      if(count < 999)
        write7seg(bt[(count/10)%10]);
      else
        write7seg(bt[(count/100)%10]);
      ++mplx;
    } else {
      digitalWrite(x1, LOW);
      digitalWrite(x2, LOW);
      digitalWrite(x3, HIGH);
      if(count < 999)
        write7seg(bt[(count/100)]);
<<<<<<< HEAD
      } else {
        write7seg(bt[count/1000]|1);
      }
=======
      else
        write7seg(bt[count/1000]|1);
>>>>>>> d144b76247735ab9f6d6e9414e35d443b5b1c87f
      mplx = 0;
    }
  }

  t4 = millis();
  if(t4 - t3 > 10){
    t3 = millis();
    if(inc){
      count++;
      if(count == 9999)
        count = 0;  
    } else {
      count--;
      if(count == -1)
        count = 9999;
    }
    if(count%500 == 0){
      Serial.println(count);
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
