#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <Psapi.h>
#include "Tsur_Log.h"
#pragma warning(disable:4996)

extern struct Snapshot;
extern struct SnapshotProcess;
extern struct DLL_Process;


int GenerateHomePage(struct Snapshot* snapshotHead);
void GenerateSnapshotPage(struct Snapshot* snapshotPtr, char* homePage);
