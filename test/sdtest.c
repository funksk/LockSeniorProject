#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define WRKDIR "./LOCKDATA/"

//******STRUCTS********

struct stat st = {0};

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
void saveMastData(mastUser);
void saveUser();
void readUser();
//individual file functions
int chkMasterData();

mastUser initMasterData();
users initUserData();


int main(int argv, char *argv[])
{
	mastUser master;
	users user;
	//initSD();
	if(chkMasterData())
		loadMasterData();
	else
		initMasterData();
	
	return 0;
}

void saveMastData(mastUser m)
{
	FILE *f;
	mkdir(WRKDIR, 0700);
	f = fopen(strcat(WRKDIR, "mast.txt"), "w")
	fprintf(f, "%s\n",m.name);
	fprintf(f, "%s\n",m.pin);
	fprintf(f, "%s",m.fingprint);
}

mastUser initMasterData()
{
	mastUser master;
	master.name = "buttman jenkins";
	master.pin = "1234";
	saveMastData(master);
	return master;
}

mastUser loadMasterData()
{
	FILE *f;
	mastUser m;
	f = fopen(strcat(WRKDIR, "mast.txt"), "r");
	fgets(m.name, 50, f);
	fgets(m.pin, 15, f);
	fgets(m.fingprint, 1000, f);
	return m;
}

//return 0 if there is no dir
//return 1 if there is a dir
int chkMasterData()
{
	if(stat(WRKDIR, &st) == -1)	//if the dir does not exist
		return 0;
	return 1;
}