#include <LiquidCrystal.h>
#include <ArduinoTimer.h>   //install MegunoLink for timer$$$$$$$$$$$$


//        reset    enable   d4       d5       d6       d7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, Backlight = 10, buttonPin1 = 7, buttonPin2 = 8;

//Button 1 = scanner AFTER MENU SELECTIONS
//Button 2 = keypad AFTER MENU SELECTIONS
int buttonState1 = 0;
int buttonState2 = 0;
bool k = true;

ArduinoTimer MenuTimer;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);




void setup() {
  lcd.begin(16,2);
}

void ResetMenuTimer(){
  MenuTimer.Reset();    //Reset Screen sleep timer
}


void ScreenSleep(){
  lcd.clear();
  analogWrite(Backlight, 0);    //Makes LCD go dark
  buttonWait(7,8);
}


void Wake(){
  lcd.clear();
  analogWrite(Backlight, 200);    //Turn LCD screen brightness on max
  lcd.setCursor(0, 0);
  lcd.print("Waking");
  delay(2000);
  ResetMenuTimer();
}





void buttonWait(int buttonPin1,int buttonPin2){       //wait until button is pressed function
  int buttonState1 = 0;
  int buttonState2 = 0;
  while(1){
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    if ((buttonState1 == HIGH) || (buttonState2 == HIGH)){
      return;
    }
  }
}

void TimedButtonWait(int buttonPin1, int buttonPin2){       //wait until button with setback timer 
  int buttonState1 = 0;
  int buttonState2 = 0;
  while(MenuTimer.EllapsedSeconds() <= 12){
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    if ((buttonState1 == HIGH) || (buttonState2 == HIGH)) {
      return;
    }
  }
}

void FingerPrintWait(int buttonPin1){       //wait until button with setback timer 
  int buttonState1 = 0;
  while(MenuTimer.EllapsedSeconds() <= 12){
    buttonState1 = digitalRead(buttonPin1);
    if (buttonState1 == HIGH) {
      return;
    }
  }
}

void UserNameWait(int buttonPin2){       //wait until button with setback timer 
  int buttonState2 = 0;
  while(MenuTimer.EllapsedSeconds() <= 12){
    buttonState1 = digitalRead(buttonPin2);
    if (buttonState1 == HIGH) {
      return;
    }
  }
}







void Menu1(){
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Unlock Mode");
    lcd.setCursor(4, 1);
    lcd.print("Selected");
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press finger to");
    lcd.setCursor(0, 1);
    lcd.print("scanner now...");
    ResetMenuTimer();
    FingerPrintWait(7);                 //Button 1 is representing a fingerprint scanned in from sensor

    //This is where if fingerprint is accepted, screen says accepted or denied$$$$$$$$$$$$$$$$$$$$$$$$$$$
    if((buttonState1 == HIGH)&&(MenuTimer.EllapsedSeconds() < 12)){
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Access");
      lcd.setCursor(5, 1);
      lcd.print("Granted");
      delay(5000);
    }
    
    lcd.clear();
    ResetMenuTimer();
}








void Menu2(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Register New");
    lcd.setCursor(0, 1);
    lcd.print("User Selected");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter User");
    lcd.setCursor(0, 1);
    lcd.print("Name");
    ResetMenuTimer();
    UserNameWait(8);                //Button 2 in pin 8 is representing an input from the keypad for user name
    if((buttonState2 == HIGH)&&(MenuTimer.EllapsedSeconds() < 12)){
      ResetMenuTimer();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Now Enter User");
      lcd.setCursor(0, 1);
      lcd.print("Fingerprint Data");
      FingerPrintWait(7);
    }
    if((buttonState1 == HIGH)&&(MenuTimer.EllapsedSeconds() < 12)){
      ResetMenuTimer();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fingerprint");
      lcd.setCursor(0, 1);
      lcd.print("Entered");
      delay(2000);
    }

    lcd.clear();
    ResetMenuTimer();
}


void MainMenu(){
  analogWrite(Backlight, 200);    //Turn LCD screen brightness on max
  lcd.setCursor(0, 0);
  lcd.print("Main Menu");
  lcd.setCursor(14,0);
  lcd.print(MenuTimer.EllapsedSeconds());   //timer for showing active time, when hits 60, screen sleeps. TESTING PURPOSES ONLY******************
  lcd.setCursor(0,1);
  lcd.print("Enter 0-4");
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  //Clears screen after 1 minute--------------------------
  //Stays in this loop until button is pressed
  if(MenuTimer.EllapsedSeconds() == 10){
      ScreenSleep();
  }

//This is where a branch would be made into a second menu------------------------
  if((buttonState1 == HIGH)&&(MenuTimer.EllapsedSeconds() < 10)){
    ResetMenuTimer();
    Menu1();
  }   

  if((buttonState2 == HIGH)&&(MenuTimer.EllapsedSeconds() < 10)){
    ResetMenuTimer();
    Menu2();
  }

  if(((buttonState1 == HIGH) || (buttonState2 == HIGH))&&(MenuTimer.EllapsedSeconds() >= 10)){
    Wake();
  }
}



//CODE THAT RUNS ON ARDUINO--------------------------------------------------------------
void loop() {
  MainMenu();
}
