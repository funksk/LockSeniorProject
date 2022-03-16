#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WRKDIR "./LOCKDATA"

//******STRUCTS********
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

//FUNCTION DEFS

//file functions
mastUser loadMasterData();
users loadUserData();
void saveUser();
void readUser();
//individual file functions
int chkMasterData();

mastUser initMasterData();
users initUserData();


int main(int argv, char *argv[])
{

	//initSD();
	if(chkMasterData())
		loadMasterData();
	else
		initMasterData();

	return 0;
}

int chkMasterData()
{
	FILE *f;
	if(`)

	return 0;
}