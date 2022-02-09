/*
test main program for senior project lock
written in c++

TODO:
how to implement an overall timer into this
program to constantly be counting down all of
the time until there is some input...
will have to figure this out 
every main function will have a while loop inside of it which will
be testing for sleep condition.
must be able to break out of sleep condition when button pressed
replace all cout with LCD out


CODE PRACTICES:
we will not be including the BOOL type, as it just
defines 1 as True, and 0 as False from a short - 
just use a short with 1 or 0 dood.
Andrew does not know how c++ works, so this will be
a lot like C.
also, Andrew sucks at naming things. if that bugs you
then just change it, but make sure its for everything
master always precedes user. idk, it just makes sense
we will breaks... for loops... I'm sorry... I H8 flags
it makes shit more confusing

links:
https://aticleworld.com/state-machine-using-c/

*/

//*****INCLUDES********
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

//*********DEFINES************
#define WAITTIME 5
#define USERAMNT 50

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
} users;

//*********class definitions*************
/*
class MainState
{
public:
	void initial(Event const *e);	//INITIAL STATE

private:

};
*/
//**********function definitions***********

//NOTE FOR EVERYBODY EDITING CODE:
//YOU ARE HIGHLY ENGOURAGED TO CHANGE FUNCTION PROTOTYPES FROM VOID
//AND PASSING PARAMETERS. NOTHING IS FINAL (PROBABLY EVER)!

//MAIN FUNCTION DEFINITIONS
void initialFunc(mastUser, users[]);
//menu functions
void Mmain(mastUser, users[]);
void Mregister();
void Munlock();
void MdelUser();
void MlistUser();
void MsysOptions();
void Msleep();

void initMasterData(mastUser);

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
void saveUser();
void readUser();
//we don't need a compare, this will be dealt with by other things

int main(int argc, char *argv[])
{
	//TODO: make into state machine
	users user[USERAMNT];
	mastUser master;
	cout << "Initializing lock program TESTTESTTEST!!!V0.01" << endl;
	initialFunc(master, user);
	return 0;
}

//*******MAIN DELEGATION FUNCTIONS***********

//check if anything is initialized on SD card...
//if there is a master PIN at the front of the SD card,
//check if there is a master user, if there is,
//boot into the menu or sleep function.

void initialFunc(mastUser master, users user[USERAMNT])
{
	if(!checkfolder())	//if the folder doesn't exist 
		initMasterData(master);	//we init the data
	//if the master data exists, or we successfully entered it, continue
	Mmain(master, user);
}

//
void Mmain(mastUser master, users user[USERAMNT])
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
		switch(choice)
		{
			case 0:
				cout << "\runlock";
				break;
			case 1:
				cout << "\rregister";
				break;
			case 2:
				cout << "\rlistuser";
				break;
			case 3:
				cout << "\rdeluser";
				break;
			case 4:
				cout << "\rsysoptions";
				break;
		}
		//TODO: all of this is command line shit... change
		//into embedded shits later...
		//add if pressed enter, enter function with user commands...
		//j = 0x6A, left, l = 0x6C
		//cout << "hello!\n";
		c = getchar();
		fflush(stdin);	//remove this garbage crap
		switch(choice)
		{
			case 0:	
				switch(c)
				{
					case 0x6A:
						choice = 4;
						break;
					case 0x6C:
						choice = 1;
						break;
				}
				break;
			case 1:	
				switch(c)
				{
					case 0x6A:
						choice = 0;
						break;
					case 0x6C:
						choice = 2;
						break;
				}
				break;
			case 2:	
				switch(c)
				{
					case 0x6A:
						choice = 1;
						break;
					case 0x6C:
						choice = 3;
						break;
				}
				break;
			case 3:	
				switch(c)
				{
					case 0x6A:
						choice = 2;
						break;
					case 0x6C:
						choice = 4;
						break;
				}
				break;
			case 4:	
				switch(c)
				{
					case 0x6A:
						choice = 3;
						break;
					case 0x6C:
						choice = 0;
						break;
				}
				break;
		}
	}
}

//***********RE-USABLE MAIN FUNCTIONS***********
//TODO: fill with folder checking
int checkfolder()
{
	return 0;
}


//***********RE-USABLE GENERAL FUNCTIONS************
void initMasterData(mastUser master)
{
	cout << "\renter master name";
	getUserName(master.name);
	cout << "\renter master pin";
	getPin(master.pin);
	cout << "\rscan master fingerprint";
	getFingerPrint(master.fingprint);
}

void getUserName(char *x)
{
	char c;
	cout << "\rin getUserName";	//DEBUG
	c = getchar();	//DEBUG
}

void getPin(char *x)
{
	char c;
	cout << "\rin getPin";	//DEBUG
	c = getchar();
}

void getFingerPrint(char *x)
{
	char c;
	cout << "\rin getFingerPrint";	//DEBUG
	c = getchar();
}