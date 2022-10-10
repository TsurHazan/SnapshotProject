﻿#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <Psapi.h>
#include "Tsur_Log.h"
#include "DataStructureAndFunctions.h"
#pragma warning(disable:4996)

//Add snapshot function: create new snapshot struct and adding to a Snapshot Linked List 
snapshot* addSnapshot() {

	snapshot* newSnapshot = (snapshot*)malloc(sizeof(snapshot));
	currentTime(newSnapshot->timeCreated);
	newSnapshot->next = NULL;
	newSnapshot->processHead = NULL;
	newSnapshot->processTail = NULL;

	if (snapshotHead == NULL) {
		newSnapshot->prev = NULL;
		snapshotHead = newSnapshot;
		snapshotTail = newSnapshot;
		newSnapshot->ID = 1;
	}
	else
	{
		snapshotTail->next = newSnapshot;
		newSnapshot->prev = snapshotTail;
		newSnapshot->ID = snapshotTail->ID + 1;
		snapshotTail = newSnapshot;
	}
	return newSnapshot;
}

//Add Process function: create new process struct and adding to a Process Linked List 
snapshotProcess* addProcess(snapshot* snapshotPtr) {

	snapshotProcess* newProcess = (snapshotProcess*)malloc(sizeof(snapshotProcess));
	newProcess->next = NULL;
	newProcess->DLLhead = NULL;

	if (snapshotPtr->processHead == NULL) {
		newProcess->prev = NULL;
		snapshotPtr->processHead = newProcess;
		snapshotPtr->processTail = newProcess;
	}
	else
	{
		snapshotPtr->processTail->next = newProcess;
		newProcess->prev = snapshotPtr->processTail;
		snapshotPtr->processTail = newProcess;
	}

	newProcess->ProcessInfo.cb = 0;
	newProcess->ProcessInfo.PageFaultCount = 0;
	newProcess->ProcessInfo.PagefileUsage = 0;
	newProcess->ProcessInfo.PeakPagefileUsage = 0;
	newProcess->ProcessInfo.PeakWorkingSetSize = 0;
	newProcess->ProcessInfo.QuotaNonPagedPoolUsage = 0;
	newProcess->ProcessInfo.QuotaPagedPoolUsage = 0;
	newProcess->ProcessInfo.QuotaPeakNonPagedPoolUsage = 0;
	newProcess->ProcessInfo.QuotaPeakPagedPoolUsage = 0;
	newProcess->ProcessInfo.WorkingSetSize = 0;

	return newProcess;
}

//Add DLL function: create new DLL struct and adding to a DLL Linked List 
dLL_Process* addDLL(snapshotProcess* ProcessPtr) {

	dLL_Process* newDLL = (dLL_Process*)malloc(sizeof(dLL_Process));

	newDLL->next = NULL;
	if (ProcessPtr->DLLhead == NULL)
	{
		newDLL->numberID = 1;
		newDLL->prev = NULL;
		ProcessPtr->DLLhead = newDLL;
		ProcessPtr->DLLTail = newDLL;
	}
	else
	{
		ProcessPtr->DLLTail->next = newDLL;
		newDLL->prev = ProcessPtr->DLLTail;
		newDLL->numberID = newDLL->prev->numberID + 1;
		ProcessPtr->DLLTail = newDLL;
	}
	return newDLL;
}


void DllDealer(HANDLE hProcess,snapshotProcess* currentProcess)
{

	DWORD cbNeeded;
	HMODULE hMods[1024];
	dLL_Process* dllChecker = currentProcess->DLLhead;
	dLL_Process* newDLL;
	unsigned int dllCount = 1;
	char signal;

	// Get Dlls List
	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		TCHAR wDllName[MAX_PATH];

		//if its the first dll in the list
		if (dllChecker == NULL)
		{
			if (GetModuleFileNameEx(hProcess, hMods[0], wDllName, MAX_PATH))
			{
				// Convert to regular char array (string)
				char dllName[MAX_PATH];
				size_t numConverted;
				wcstombs_s(&numConverted, dllName, MAX_PATH, wDllName, MAX_PATH);
			
				newDLL = addDLL(currentProcess);
				strcpy(newDLL->Name, dllName);
			}

		}

		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			// Get the full path to the module's file.

			if (GetModuleFileNameEx(hProcess, hMods[i], wDllName, MAX_PATH))
			{
				dllCount = 1;
				dllChecker = currentProcess->DLLhead;
				// Convert to regular char array (string)
				char dllName[MAX_PATH];
				size_t numConverted;
				wcstombs_s(&numConverted, dllName, MAX_PATH, wDllName, MAX_PATH);

				// check if dll is in the list
				while (dllCount <= currentProcess->DLLTail->numberID)
				{

					//the dll isnt in the list so create new dll struct and add it to the current process dll linked list
					if (dllChecker == NULL)
					{
						newDLL = addDLL(currentProcess);
						strcpy(newDLL->Name, dllName);
						dllCount = newDLL->numberID + 1;
					}
					else if ((signal = strcmp(dllChecker->Name, dllName)) == 0) //found the dll in the dll list
					{
						signal = strcmp(dllChecker->Name, dllName);
						dllCount = currentProcess->DLLTail->numberID + 1;
						
					}
					else
					{
						dllChecker = dllChecker->next;
					}
					
				}
			}
		}
	}
}


// function to get a process information and insert it to current snapshot
snapshotProcess* getProcess(DWORD processID, snapshot* newSnapshot, snapshotProcess* currProcess)
{
	
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	TCHAR FoundProcessName[MAX_PATH];
	char ProcessPathName[MAX_PATH];

	// Open process in order to receive information
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
	{
		// Write to log a warning 
		return currProcess;
	}

	// Get Process Name
	if (GetModuleFileNameEx(hProcess, 0, FoundProcessName, MAX_PATH))
	{
		// Convert to regular char array (string)
		size_t numConverted;
		wcstombs_s(&numConverted, ProcessPathName, MAX_PATH, FoundProcessName, MAX_PATH);

		// check if we got a name or not(more then 0 chars)
		if (numConverted < 1)
		{
			// You better call GetLastError() here
		    // Write To log
			return currProcess;
		}
	}
	else
	{
		// You better call GetLastError() here
		// Write To log
	}

	//to check if its only one snapshot or a sum: "NULL" = 1snapshot\first time
	if(currProcess == NULL)
	{
	//if didnt returned meaning we can get all the information we want and function keep going
	snapshotProcess* newProcess = addProcess(newSnapshot);
	strcpy(newProcess->Name, ProcessPathName);
	
	//get the process information and add it to the current process in the snapshot
	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		newProcess->ProcessInfo.cb += pmc.cb;
		newProcess->ProcessInfo.PageFaultCount += pmc.PageFaultCount;
		newProcess->ProcessInfo.PagefileUsage += pmc.PagefileUsage;
		newProcess->ProcessInfo.PeakPagefileUsage += pmc.PeakPagefileUsage;
		newProcess->ProcessInfo.PeakWorkingSetSize += pmc.PeakWorkingSetSize;
		newProcess->ProcessInfo.QuotaNonPagedPoolUsage += pmc.QuotaNonPagedPoolUsage;
		newProcess->ProcessInfo.QuotaPagedPoolUsage += pmc.QuotaPagedPoolUsage;
		newProcess->ProcessInfo.QuotaPeakNonPagedPoolUsage += pmc.QuotaPeakNonPagedPoolUsage;
		newProcess->ProcessInfo.QuotaPeakPagedPoolUsage += pmc.QuotaPeakPagedPoolUsage;
		newProcess->ProcessInfo.WorkingSetSize += pmc.WorkingSetSize;
		newProcess->ID = processID;
	}

	//add the new process dll's list to the new process list
	DllDealer(hProcess ,newProcess);

	CloseHandle(hProcess);
	return newProcess;
	}
	
	// to add information to an existed process
	else
	{
		currProcess = newSnapshot->processHead;
		unsigned int processCount = 1;
		char signal;

		//to find the process in the snapshot
		while (processCount <= newSnapshot->processTail->ID)
		{
			
			// if the Process isnt in the snapshot then adding it to current snapshot
			if (currProcess == NULL)
			{
				getProcess(processID, newSnapshot, NULL);
				processCount = newSnapshot->processTail->ID + 1;
			}

			//found the process in the process list
			else if ((signal = strcmp(currProcess->Name, ProcessPathName)) == 0) 
			{

				//check for new dll's, if a DLL isnt in the Process list then adding it to current Process list
				DllDealer(hProcess, currProcess);

				if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
				{
					currProcess->ProcessInfo.cb += pmc.cb;
					currProcess->ProcessInfo.PageFaultCount += pmc.PageFaultCount;
					currProcess->ProcessInfo.PagefileUsage += pmc.PagefileUsage;
					currProcess->ProcessInfo.PeakPagefileUsage += pmc.PeakPagefileUsage;
					currProcess->ProcessInfo.PeakWorkingSetSize += pmc.PeakWorkingSetSize;
					currProcess->ProcessInfo.QuotaNonPagedPoolUsage += pmc.QuotaNonPagedPoolUsage;
					currProcess->ProcessInfo.QuotaPagedPoolUsage += pmc.QuotaPagedPoolUsage;
					currProcess->ProcessInfo.QuotaPeakNonPagedPoolUsage += pmc.QuotaPeakNonPagedPoolUsage;
					currProcess->ProcessInfo.QuotaPeakPagedPoolUsage += pmc.QuotaPeakPagedPoolUsage;
					currProcess->ProcessInfo.WorkingSetSize += pmc.WorkingSetSize;
					currProcess->ID = processID;
				}
				processCount = newSnapshot->processTail->ID + 1;
			}
			else
			{
				currProcess = currProcess->next;
			}
		}
	CloseHandle(hProcess);
	return currProcess;
	}
}

// function to get all the current procesess in the computer to a list and make a new snapshot
void addProcesses(unsigned int SnapshotsCount, snapshot* newSnapshot,snapshotProcess* currProcess) {

	// if count equal to zero meaning is finished the last sum
	if (SnapshotsCount == 0)
	{
		return 0;
	}

	// Get Processes
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	// * Receive all process ID and put in aProcesses Array
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		// Error. Write to log
		return 1;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the memory usage for each process
	// *Loop of all processes
	for (i = 0; i < cProcesses; i++)
	{
		// For each Process to get its Memory Information
		currProcess = getProcess(aProcesses[i], newSnapshot, currProcess);
	}

	//wait a second before each snapshot
	Sleep(1000);
	addProcesses(SnapshotsCount - 1, newSnapshot, currProcess);
}
