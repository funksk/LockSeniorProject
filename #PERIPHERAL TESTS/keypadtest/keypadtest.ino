#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//left to right with our keypad
//COL2, ROW1, COL1, ROW4, COL3, ROW3, ROW2
//on our board, we go from right to left, 44-38
//so ROW2, ROW3, COL3, ROW4, COL1, ROW1, COL2
//NOTE: THIS IS WRONG
//TODO: FIX!!!
//   38    39    40    41    42    43    44
byte pin_rows[ROW_NUM] = {43,38,39,41}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {42,44,40}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
  }
}
