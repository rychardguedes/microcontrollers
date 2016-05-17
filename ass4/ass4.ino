// x1 é o mais significativo
const int data = 12, nclk = 8, rclk = 13, clr = 10, x1 = 14, x2 = 15, x3 = 16;
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

void write7seg(byte b){
  for(int i = 0; i < 8; i++){
    digitalWrite(rclk, LOW);
    digitalWrite(data, bitRead(b, i));
    digitalWrite(nclk, LOW);
    digitalWrite(nclk, HIGH);
  }
  digitalWrite(rclk, LOW);
  digitalWrite(rclk, HIGH);
}

void setup() {
  pinMode(x1, OUTPUT);
  pinMode(x2, OUTPUT);
  pinMode(x3, OUTPUT);
  pinMode(clr, OUTPUT);
  pinMode(nclk, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(x1, HIGH);
  digitalWrite(x2, LOW);
  digitalWrite(x3, LOW);
  digitalWrite(clr, HIGH);

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
      digitalWrite(x2, LOW);
      digitalWrite(x3, HIGH);
      write7seg(bt[count%10]);
      ++mplx;
    } else if (mplx == 1) {
      digitalWrite(x1, LOW);
      digitalWrite(x2, HIGH);
      digitalWrite(x3, LOW);
      write7seg(bt[(count/10)%10]);
      ++mplx;
    } else {
      digitalWrite(x1, HIGH);
      digitalWrite(x2, LOW);
      digitalWrite(x3, LOW);
      write7seg(bt[(count/100)]);
      mplx = 0;
      
    }
  }

  t4 = millis();
  if(t4 - t3 > 20){
    t3 = millis();
    count++;
    if(count == 1000)
      count = 0;
  }



}
