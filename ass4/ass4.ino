// x1 é o mais significativo
const int data = 12, sclk = 13, ltch = 11, x1 = 14, x2 = 15, x3 = 16;
unsigned long t1, t2, t3, t4;
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

const byte btp[] = {B11111101, // 0
                    B01100001, // 1
                    B11011011, // 2
                    B11110011, // 3
                    B01100111, // 4
                    B10110111, // 5
                    B10111111, // 6
                    B11100001, // 7
                    B11111111, // 8
                    B11110111  // 9
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
      if(count < 999){
        write7seg(bt[count%10]);  
      } else {
        write7seg(bt[(count/10)%10]); 
      }
      ++mplx;
    } else if (mplx == 1) {
      digitalWrite(x1, HIGH);
      digitalWrite(x2, LOW);
      digitalWrite(x3, LOW);
      if(count < 999){
        write7seg(bt[(count/10)%10]);
      } else {
        write7seg(bt[(count/100)%10]);
      }
      ++mplx;
    } else {
      digitalWrite(x1, LOW);
      digitalWrite(x2, LOW);
      digitalWrite(x3, HIGH);
      if(count < 999){
        write7seg(bt[(count/100)]);
      } else {
        write7seg(btp[count/1000]);
      }
      mplx = 0;
    }
  }

  t4 = millis();
  if(t4 - t3 > 10){
    t3 = millis();
    count++;
    if(count == 9999)
      count = 0;
  }



}
