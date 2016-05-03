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

bool inc = true;
int uni, ten, i, j;
const int del = 5;
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
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  uni = 0;
  ten = 0;
  t1 = millis();
  t2 = millis();
  t3 = millis();
  t4 = millis();
}

void loop()
{
  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  write7seg(b1[uni]);
  delay(del);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  write7seg(b1[ten]);
  delay(del);
  
  t2 = millis();
  if(t2 - t1 > 500)
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

  if(!digitalRead(4))
    while(!digitalRead(4))
      inc = !inc;
}
