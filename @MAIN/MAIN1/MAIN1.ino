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
//#include <Keypad.h>
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

#define ISLCD 0
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
//menu functions
void Mmain(mastUser, users);

void Munlock(mastUser, users);
void Mregister(mastUser, users);
void MdelUser(mastUser, users);
void MlistUser(mastUser, users);
void MsysOptions(mastUser, users);
void Msleep(mastUser, users);

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
//these functions will probably be built-into a library
//if we want to do a cute lock animation, do it here lol

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

//check if anything is initialized on SD card...
//if there is a master PIN at the front of the SD card,
//check if there is a master user, if there is,
//boot into the menu or sleep function.
void initPorts()
{

}

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
#if ISLCD

#else
		switch(choice)
		{
			case 0:
				Serial.print("unlock\n");
				break;
			case 1:
				Serial.print("register\n");
				break;
			case 2:
				Serial.print("listuser\n");
				break;
			case 3:
				Serial.print("deluser\n");
				break;
			case 4:
				Serial.print("sysoptions\n");
				break;
		}
#endif
		//get input here
		digitalRead();

		//TODO: CHANGE GETTING STUFF!!!!
#if ISKEYPAD
		switch(choice)
		{
			case 0:		//unlock
				switch(c)
				{
					case 0x6A:
						choice = 4;
						break;
					case 0x6C:
						choice = 1;
						break;
					case 0x6B:
						Munlock(master, user);
						break;
				}
				break;
			case 1:		//register
				switch(c)
				{
					case 0x6A:
						choice = 0;
						break;
					case 0x6C:
						choice = 2;
						break;
					case 0x6B:
						Mregister(master, user);
						break;
				}
				break;
			case 2:		//listuser
				switch(c)
				{
					case 0x6A:
						choice = 1;
						break;
					case 0x6C:
						choice = 3;
						break;
					case 0x6B:
						MlistUser(master, user);
						break;
				}
				break;
			case 3:		//deluser
				switch(c)
				{
					case 0x6A:
						choice = 2;
						break;
					case 0x6C:
						choice = 4;
						break;
					case 0x6B:
						MdelUser(master, user);
						break;
				}
				break;
			case 4:		//sysoptions
				switch(c)
				{
					case 0x6A:
						choice = 3;
						break;
					case 0x6C:
						choice = 0;
						break;
					case 0x6B:
						MsysOptions(master, user);
						break;
				}
				break;
		}
#else

#endif
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
void Munlock(mastUser master, users user[USERAMNT])
{
	int choice = 0;
	char curFingerData[1000];
	char c;
	Serial.print("in Munlock\n");
	Serial.print("scan fingerprint now\n");
	getFingerPrint(curFingerData);

}

//enter PIN
//enter name
//scan data
//make sure scanned data is good
//retry until done
void Mregister(mastUser master, users user[USERAMNT])
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
void MdelUser(mastUser master, users user[USERAMNT])
{
	Serial.print("MdelUser\n");
}

//enter PIN
//list all users that exist
void MlistUser(mastUser master, users user[USERAMNT])
{
	Serial.print("MlistUser\n");
}

//authenticate master user
void MsysOptions(mastUser master, users user[USERAMNT])
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
	c = getchar();	//DEBUG
}

void getPin(char *x)
{
	char c;
	Serial.print("in getPin");	//DEBUG
	c = getchar();
}

void getFingerPrint(char *x)
{
	char c;
	Serial.print("in getFingerPrint");	//DEBUG
	c = getchar();
}


