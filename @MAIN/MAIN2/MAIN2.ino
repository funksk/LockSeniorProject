/*
CSC 492
BIOMETRIC LOCK PROGRAM
By
Ryan Lemmon, Shane Riggar, Luke Tingley, and Andrew Yankovich
Emails:
LEM8289@calu.edu, RIG6382@calu.edu, TIN2093@calu.edu, YAN6326@calu.edu
This is the main code funciton for the Biometric Lock Senior Project
This document was initially created on 24-1-22.

THINGS TO KEEP IN MIND:
~comment literally everything
~leave no stone unturned. make this readable code (except when prototyping of course)

TODO:
*how to implement an overall timer into this
*program to constantly be counting down all of
the time until there is some input...
will have to figure this out 
*every main function may have to have a while loop inside of it which will
be testing for sleep condition.
*must be able to break out of sleep condition when button pressed
*make all of the get and set functions be able to return
acknowledgement of passing or failing
*make sure data flow is good, so we don't have to mess with it later

CODE PRACTICES:
we will not be including the BOOL type, as it just
defines 1 as True, and 0 as False from a short - 
just use a short with 1 or 0 dood.
Andrew does not know how c++ works, so this will be
a lot like C.
also, Andrew sucks at naming things. if that bugs you
then just change it, but make sure its for everything
master always precedes user. idk, it just makes sense
we will user breaks for loops... I'm sorry... I H8 flags
it makes shit more confusing

links:
https://aticleworld.com/state-machine-using-c/

*/

//*****INCLUDES********
//system master includes

//LCD includes
#include <LiquidCrystal.h>
//Keypad includes
#include <Keypad.h>
//fingerprint sensor includes
//this one's external and must be included. not sure how to yet tho.

//lock includes

//sd card slot includes
#include <SPI.h>
#include <SD.h>
//misc includes


//*********DEFINES************
#define WAITTIME 5
#define USERAMNT 2

#define ISLCD 1
#define ISSD 1
#define ISFPRINT 0
#define ISKEYPAD 0
#define ISSLEEP 0
#define ISLOCK 0


//*********typedef init*************

typedef struct
{
	char pin[10];
	char name[50];
	char fingprint[1000];	//I don't know what we're gonna store this as....
							//should do a bit more research
} mastUser;

typedef struct 
{
	char name[50];
	char fingprint[1000];
} oneUser;

typedef struct
{
	oneUser user[USERAMNT];
} users;	//quite silly, but this makes life easier between functions

//**********global variables***********


//**********function definitions***********

//NOTE FOR EVERYBODY EDITING CODE:
//YOU ARE HIGHLY ENGOURAGED TO CHANGE FUNCTION PROTOTYPES FROM VOID
//AND PASSING PARAMETERS. NOTHING IS FINAL (PROBABLY EVER)!

//MAIN FUNCTION DEFINITIONS
void initialFunc();
void initPorts();


mastUser initMasterData();
users initUserData();

//menu specific functions
//LCD

//keypad

//fingerprint sensor

//lock

//sd card
int checkfolder();
//re-used menu functions
//LCD

//keypad

//fingerprint sensor

//lock

//sd card

//DEBUG COMPUTER FUNCTIONS

//RE-USABLE FUNCTION DEFINITIONS
//note: if a function does something related to a perripheral
//just list it under the perripheral
//LCD
void printLCD(char*);

//keypad
void getUserName(char*);
void getPin(char*);
void setMasterPin();	//call this sob if you want to set the PIN
void cmpMasterPin();	

//fingerprint sensor
void getFingerPrint(char*);
void setFingerPrint();
short cmpFingerPrint();

//lock
//these should (probably?) be the only lock functions
void unlock();
void lock();

//sd card
//most likely, these functions will be from a library
//I'll define a few that may just roll shit up from a 
//library into a nice and neat function
mastUser loadMasterData();
users loadUserData();
void saveUser();
void readUser();
//we don't need a compare, this will be dealt with by other things

//menu functions

void Munlock(mastUser, users);
void Mregister(mastUser, users);
void MdelUser(mastUser, users);
void MlistUser(mastUser, users);
void MsysOptions(mastUser, users);
void Msleep(mastUser, users);

void Mmain(mastUser, users);


//******peripheral global vars and classes******
//LCD
//        reset    enable   d4       d5       d6       d7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//Keypad
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
//so COL2, ROW1, COL1, ROW4, COL3, ROW3, ROW2
//   38    39    40    41    42    43    44
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte pin_rows[ROW_NUM] = {39,44,43,41}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {40,38,42}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
//SD card

//fingerprint

//lock

void loop() {
  // This will never get called. that's okay!
	return;
}

//********entry point of program!!**********
void setup()
{
	//todo: INITILIZE PERIPHERALS
	//HAVE INDIVIDUAL FUNCTIONS FOR INITING
	//MAKE SOME GLOBAL VARS IF WE HAVE TO!!
	Serial.print("******LOCK PROGRAM V0.1*********\n");
	initPorts();
	initialFunc();
}

//*******MAIN DELEGATION FUNCTIONS***********

void initPorts()
{
	//DEBUG serial
	Serial.begin(9600);
	//LCD
	lcd.begin(16,2);
	lcd.print("Welcome to lock program");
}

//check if anything is initialized on SD card...
//if there is a master PIN at the front of the SD card,
//check if there is a master user, if there is,
//boot into the menu or sleep function.
void initialFunc()
{
	mastUser master;
	users user;
	if(!checkfolder())	//if the folder doesn't exist 
	{
		master = initMasterData();	//we init the data
		user = initUserData();	//init default user data
	}
	else
	{
		master = loadMasterData();
		user = loadUserData();
	}
	
	//if the master data exists, or we successfully entered it, continue
	Mmain(master, user);
}

//**********MAIN MENU LOOP**********
void Mmain(mastUser master, users user)
{
	int choice = 0;
	char c;
	//output the shits to the screen... wait for input
	//if no input (for certain time), clear screen and chill...
	//this is our forever loop, get used to it
	while(1)
	{
		//0 = unlock
		//1 = register
		//2 = listuser
		//3 = deluser
		//4 = sysoptions
		//TODO: make better, not cout
		lcd.setCursor(0,1);
		lcd.print(c);
		switch(choice)
		{
			case 0:
				printLCD("Unlock");
				break;
			case 1:
				printLCD("Register");
				break;
			case 2:
				printLCD("ListUser");
				break;
			case 3:
				printLCD("DelUser");
				break;
			case 4:
				printLCD("SysOptions");
				break;
		}
		
		//get input here
		
		c = keypad.getKey();
		while(keypad.isPressed(c) == false)
			c = keypad.getKey();

		//TODO: CHANGE GETTING STUFF!!!!
		switch(choice)
		{
			case 0:		//unlock
				switch(c)
				{
					case '#':
						choice = 4;
						break;
					case '*':
						choice = 1;
						break;
					case 0x30:
						Munlock(master, user);
						break;
				}
				break;
			case 1:		//register
				switch(c)
				{
					case '#':
						choice = 0;
						break;
					case '*':
						choice = 2;
						break;
					case 0x30:
						Mregister(master, user);
						break;
				}
				break;
			case 2:		//listuser
				switch(c)
				{
					case '#':
						choice = 1;
						break;
					case '*':
						choice = 3;
						break;
					case 0x30:
						MlistUser(master, user);
						break;
				}
				break;
			case 3:		//deluser
				switch(c)
				{
					case '#':
						choice = 2;
						break;
					case '*':
						choice = 4;
						break;
					case 0x30:
						MdelUser(master, user);
						break;
				}
				break;
			case 4:		//sysoptions
				switch(c)
				{
					case '#':
						choice = 3;
						break;
					case '*':
						choice = 0;
						break;
					case 0x30:
						MsysOptions(master, user);
						break;
				}
				break;
		}

	}
}

//****************MENU ITEMS!!*****************
//scan data
//did they scan correct data?
//	yes: continue
//	no: dump back to menu
//does it match anything in our system?
//	yes: unlock door for a few secs
//	no: dump back to menu
void Munlock(mastUser master, users user)
{
	int choice = 0;
	char curFingerData[1000];
	char c;
	Serial.print("in Munlock\n");
	Serial.print("scan fingerprint now\n");
	getFingerPrint(curFingerData);
	printLCD('fartts!!');
	delay(5000);

}

//enter PIN
//enter name
//scan data
//make sure scanned data is good
//retry until done
void Mregister(mastUser master, users user)
{
	Serial.print("in Mregister\n");
}

//enter PIN
//enter username of deleting user
//scan data
//is user's data correct?
//	yes: delete user, goto menu
//	no: goto menu
//give a few tries here
void MdelUser(mastUser master, users user)
{
	Serial.print("MdelUser\n");
}

//enter PIN
//list all users that exist
void MlistUser(mastUser master, users user)
{
	Serial.print("MlistUser\n");
}

//authenticate master user
void MsysOptions(mastUser master, users user)
{
	Serial.print("MsysOptions\n");

}


//***********RE-USABLE MAIN FUNCTIONS***********
//TODO: fill with folder checking
int checkfolder()
{
	return 0;
}

mastUser loadMasterData()
{
	mastUser m;
	Serial.print("in loadMasterData\n");
	//open file/folder with master data in it
	//grab them into m
}

users loadUserData()
{
	users u;
	Serial.print("in loadUserData\n");
	//open file/folder with all user's data in it
	//grab them into u
}

//***********RE-USABLE GENERAL FUNCTIONS************

mastUser initMasterData()
{
	mastUser master;
	Serial.print("enter master name\n");
	getUserName(master.name);
	Serial.print("enter master pin\n");
	getPin(master.pin);
	Serial.print("scan master fingerprint\n");
	getFingerPrint(master.fingprint);
	return master;
}

users initUserData()
{

}

void getUserName(char *x)
{
	char c;
	Serial.print("in getUserName");	//DEBUG
}

//should we make it 4 or more numbers? yes...
void getPin(char *x)
{
	char c;
	char pin[4] = "";
	int num = 0, enter = 0;
	Serial.print("in getPin");	//DEBUG
	printLCD("Enter PIN");
	while(enter == 0)
	{
		c = keypad.getKey();
		while(keypad.isPressed(c) == false)
			c = keypad.getKey();
		if(c == '*')	//backspace
		{
			//get rid of pin from number
			lcd.setCursor(1,num);
			lcd.write(' ');
			num--;
		}
		else if(c == '#')	//enter
		{
			if(num > 3)	//if at least 4 nums has been entered
				enter = 1;
		}
		else	//number
		{	//TODO don't echo the pin out to the user
			strcat(pin,c);
			lcd.setCursor(1,num);
			lcd.write(c);
			num++;
		}
	}
	strcpy(x,pin);
}

void getFingerPrint(char *x)
{
	char c;
	Serial.print("in getFingerPrint");	//DEBUG
	c = getchar();
}


//********RE-USABLE PERIPHERAL PHUNCTIONS**********

void printLCD(char* x)
{
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(x);
}