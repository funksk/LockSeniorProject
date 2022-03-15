#include <Keypad.h>
#include <stdio.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};


//   38    39    40    41    42    43    44
byte pin_rows[ROW_NUM] = {39,44,43,41}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {40,38,42}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

char cin[50];

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();
  while(keypad.isPressed(key) == false)
  	key = keypad.getKey();
  sprintf(cin, "%X",key);
  Serial.println(cin);

}
