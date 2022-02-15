#include <LiquidCrystal.h>

//        reset    enable   d4       d5       d6       d7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//const int rs = 24, en = 26, d4 = 31, d5 = 32, d6 = 33, d7 = 34; //make these different when we get the board... 

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);

  lcd.print("hello!!!");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);

  // print the number of seconds since reset:

  lcd.print(millis() / 1000);
}
