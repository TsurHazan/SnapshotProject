#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <Psapi.h>
#include "Tsur_Log.h"
#pragma warning(disable:4996)

//header struct
typedef struct ProjectHeader
{
	int version;
	int snapshotsCount;
	char reserve[100];
}header;

extern struct Snapshot;
extern struct SnapshotProcess;
extern struct DLL_Process;


int GenerateHomePage(struct Snapshot* snapshotHead);
int GenerateSnapshotPage(struct Snapshot* snapshotPtr, char* homePage);
int saveToFile();
int readFile();