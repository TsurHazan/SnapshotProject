#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <Psapi.h>
#include "Tsur_Log.h"
#pragma warning(disable:4996)

// DLL Struct
typedef struct DLL_Process
{
	char Name[MAX_PATH];
	int numberID;
	struct DLL_Process* next;
	struct DLL_Process* prev;
}dLL_Process;


//Process Struct
typedef struct SnapshotProcess
{
	char Name[MAX_PATH];
	int ID;
	PROCESS_MEMORY_COUNTERS ProcessInfo;
	dLL_Process* DLLhead;
	dLL_Process* DLLTail;
	struct SnapshotProcess* next;
	struct SnapshotProcess* prev;
}snapshotProcess;


// Snapshot Struct
typedef struct Snapshot {
	char timeCreated[100];
	unsigned int ID;
	snapshotProcess* processHead;
	snapshotProcess* processTail;
	struct Snapshot* next;
	struct Snapshot* prev;

}snapshot;

extern snapshot* snapshotHead;
extern snapshot* snapshotTail;

snapshot* addSnapshot();
snapshotProcess* addProcess(snapshot* snapshotPtr);
dLL_Process* addDLL(snapshotProcess* ProcessPtr);
snapshotProcess* getProcess(DWORD processID, snapshot* newSnapshot, snapshotProcess* currProcess);
void addProcesses(unsigned int SnapshotsCount, snapshot* newSnapshot, snapshotProcess* currProcess);
void printSnapshotProcesses(snapshot* snapshotPtr);