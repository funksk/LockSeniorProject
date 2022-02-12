/*
test main program for senior project lock
written in c++

TODO:
*how to implement an overall timer into this
*program to constantly be counting down all of
the time until there is some input...
will have to figure this out 
*every main function will have a while loop inside of it which will
be testing for sleep condition.
*must be able to break out of sleep condition when button pressed
replace all cout with LCD out
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
//#include <ncurses.h>
//using namespace std;

//*********DEFINES************
#define WAITTIME 5
#define USERAMNT 50
#define CLRSCREEN() printf("\e[2J\e[H")


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
	oneUser[USERAMNT]
} users;	//quite silly, but this makes life easier between functions

//**********global variables***********
struct termios tmios;

//**********function definitions***********

//NOTE FOR EVERYBODY EDITING CODE:
//YOU ARE HIGHLY ENGOURAGED TO CHANGE FUNCTION PROTOTYPES FROM VOID
//AND PASSING PARAMETERS. NOTHING IS FINAL (PROBABLY EVER)!

//MAIN FUNCTION DEFINITIONS
void initialFunc();
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
void flipecho(int);

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

int main(int argc, char *argv[])
{
	//todo: INITILIZE PERIPHERALS
	//HAVE INDIVIDUAL FUNCTIONS FOR INITING
	//MAKE SOME GLOBAL VARS IF WE HAVE TO!!
	flipecho(1);
	printf("******LOCK PROGRAM PROOF OF CONCEPT C++*********\n");
	initialFunc(master, user);
	return 0;
}

//*******MAIN DELEGATION FUNCTIONS***********

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
		user = initUserData(user);	//init default user data
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
		switch(choice)
		{
			case 0:
				printf("unlock\n");
				break;
			case 1:
				printf("register\n");
				break;
			case 2:
				printf("listuser\n");
				break;
			case 3:
				printf("deluser\n");
				break;
			case 4:
				printf("sysoptions\n");
				break;
		}
		//TODO: all of this is command line shit... change
		//into embedded shits later...
		//add if pressed enter, enter function with user commands...
		//j = 0x6A, left, l = 0x6C, k = 0x6B
		//cout << "hello!\n";
		c = getchar();
		fflush(stdin);	//remove this garbage crap
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
	char curFignerData[1000];
	char c;
	printf("in Munlock\n");
	printf("scan fingerprint now\n");
	getFingerPrint(curFingerData);

}

//enter PIN
//enter name
//scan data
//make sure scanned data is good
//retry until done
void Mregister(mastUser master, users user[USERAMNT])
{
	printf("in Mregister\n");
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
	printf("MdelUser\n");
}

//enter PIN
//list all users that exist
void MlistUser(mastUser master, users user[USERAMNT])
{
	printf("MlistUser\n");
}

//authenticate master user
void MsysOptions(mastUser master, users user[USERAMNT])
{
	printf("MsysOptions\n");

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
	printf("in loadMasterData\n");
	//open file/folder with master data in it
	//grab them into m
}
users loadUserData()
{
	users u;
	printf("in loadUserData\n");
	//open file/folder with all user's data in it
	//grab them into u
}

//***********RE-USABLE GENERAL FUNCTIONS************

mastUser initMasterData()
{
	mastUser master;
	printf("enter master name\n");
	getUserName(master.name);
	printf("enter master pin\n");
	getPin(master.pin);
	printf("scan master fingerprint\n");
	getFingerPrint(master.fingprint);
	return master;
}

void getUserName(char *x)
{
	char c;
	printf("in getUserName");	//DEBUG
	c = getchar();	//DEBUG
}

void getPin(char *x)
{
	char c;
	printf("in getPin");	//DEBUG
	c = getchar();
}

void getFingerPrint(char *x)
{
	char c;
	printf("in getFingerPrint");	//DEBUG
	c = getchar();
}

//flip the echo out
//if the user passes anything other than 1 or 0,
//it just flips the echo
void flipecho(int x)
{
  if(tcgetattr(fileno(stdin),&tmios) != 0)	//check to see if we have an error
  {						//in the command line parameter get
    perror("tcgetattr() error");
    exit(2);
  }
  switch(x)	//switch for x
  {
    case(0):	//0 sets the echo bit
      tmios.c_lflag |= ECHO;	//we set the local echo bit
      tcsetattr(fileno(stdin),TCSANOW,&tmios);	//set the actual echo bit
      break;
    case(1):	//1 clears the echo bit
      tmios.c_lflag &= ~ECHO;	//clear the local echo bit
      tcsetattr(fileno(stdin),TCSANOW,&tmios);	//set the actual echo bit
      break;
    default:	//default just flips the echo bit
      tmios.c_lflag ^= ECHO;	//flip the local echo bit
      tcsetattr(fileno(stdin),TCSANOW,&tmios);	//set the actual echo bit
      break;
  }
}
