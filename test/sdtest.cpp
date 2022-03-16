//*****INCLUDES********
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <filesystem>

#define OGDIR "./LOCKDATA/"

using namespace std;
namespace fs = std::filesystem;

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


int main(int argv, char *argv[])
{

}