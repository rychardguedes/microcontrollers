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

int uni, ten, i, j, t, del = 10;

void escreve(byte t){
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
  uni = 1;
  ten = 0;
  t = 0;
}

void loop()
{
  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  escreve(b1[uni]);
  delay(del);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  escreve(b1[ten]);
  delay(del);
  
  t++;
  if(t >= 10)
  {
      t = 0;
      uni++;
      if(uni == 10){
        uni = 0;
        ten++;
        if (ten == 10)
          ten = 0;
      }
  }

}
