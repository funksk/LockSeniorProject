/*
test main program for senior project lock
written in c++

TODO:
how to implement an overall timer into this
program to constantly be counting down all of
the time until there is some input...
will have to figure this out 


CODE PRACTICES:
we will not be including the BOOL type, as it just
defines 1 as True, and 0 as False from a short - 
just use a short with 1 or 0 dood.
Andrew does not know how c++ works, so this will be
a lot like C.
also, Andrew sucks at naming things. if that bugs you
then just change it, but make sure its for everything

links:
https://aticleworld.com/state-machine-using-c/

*/

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

//typedef init
typedef short Event;


//class definitions
/*
class MainState
{
public:
	void initial(Event const *e);	//INITIAL STATE

private:

};
*/
//function definitions

//NOTE FOR EVERYBODY EDITING CODE:
//YOU ARE HIGHLY ENGOURAGED TO CHANGE FUNCTION PROTOTYPES FROM VOID
//AND PASSING PARAMETERS. NOTHING IS FINAL (PROBABLY EVER)!

//MAIN FUNCTION DEFINITIONS
void initialFunc();
//menu functions
void Mmain();
void Mregister();
void Munlock();
void MdelUser();
void MlistUser();
void MsysOptions();
void Msleep();
//menu specific functions
//LCD

//keypad

//fingerprint sensor

//lock

//sd card

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
void getUserName();
void getMasterPin(char *pin);	//SAVE PIN AS STRING, WE'RE NOT DOING MATH TO IT!!
void setMasterPin();	//call this sob if you want to set the PIN
void cmpMasterPin();	

//fingerprint sensor
void getFingerPrint();
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
	initialFunc();
	cout << "hello" << endl;
	return 0;
}

/*
check if anything is initialized on SD card...
if there is a master PIN at the front of the SD card,
check if there is a master user, if there is,
boot into the menu or sleep function.
*/
void initialFunc()
{

}