#include <stdio.h>
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
	if (!newSnapshot)
	{
		Log_Warning(" while trying to malloc in addSnapshot");
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		Log_Event("Created snapshot");
	}

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
	if (!newProcess)
	{
		Log_Warning(" while trying to malloc in addProcess");
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		Log_Event("Created process");
	}

	newProcess->next = NULL;
	newProcess->DLLhead = NULL;

	if (snapshotPtr->processHead == NULL) {
		newProcess->prev = NULL;
		snapshotPtr->processHead = newProcess;
		snapshotPtr->processTail = newProcess;
		snapshotPtr->processAmount = 1;
	}
	else
	{
		snapshotPtr->processTail->next = newProcess;
		newProcess->prev = snapshotPtr->processTail;
		snapshotPtr->processTail = newProcess;
		snapshotPtr->processAmount +=1;

	}

	//initalize all information for next sums
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
	if (!newDLL)
	{
		Log_Warning(" while trying to malloc in addDLL");
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		Log_Event("Created dll");
	}

	newDLL->next = NULL;
	if (ProcessPtr->DLLhead == NULL)
	{
		newDLL->numberID = 1;
		newDLL->prev = NULL;
		ProcessPtr->DLLhead = newDLL;
		ProcessPtr->DLLTail = newDLL;
		ProcessPtr->dllAmount = 1;
	}
	else
	{
		ProcessPtr->DLLTail->next = newDLL;
		newDLL->prev = ProcessPtr->DLLTail;
		newDLL->numberID = newDLL->prev->numberID + 1;
		ProcessPtr->DLLTail = newDLL;
		ProcessPtr->dllAmount = newDLL->numberID;
	}
	return newDLL;
}

// function to get a process information and insert it to current snapshot
snapshotProcess* getProcess(DWORD processID, snapshot* newSnapshot, snapshotProcess* currProcess)
{
	
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	TCHAR FoundProcessName[MAX_PATH];
	TCHAR wDllName[MAX_PATH];
	DWORD cbNeeded;
	HMODULE hMods[1024];
	dLL_Process* dllChecker;
	dLL_Process* newDLL;
	char ProcessPathName[MAX_PATH];
	char shortProcessName[MAX_PATH];
	char* ptrShortName;
	unsigned int dllCount = 1;
	char signal;
	char errorMsg[100];

	// Open process in order to receive information
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
	{
		Log_Warning("access denied while trying to reach process");
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
			Log_Warning("access denied while trying to reach process name");
			return currProcess;
		}

		//get only the process name
		ptrShortName = strtok(ProcessPathName, "\\");
		while (ptrShortName != NULL)
		{
			strcpy(shortProcessName, ptrShortName);
			ptrShortName = strtok(NULL, "\\");
		}
	}
	else
	{
		Log_Warning("Found problem with name");
	}

	//to check if its only one snapshot or a sum: "NULL" = 1snapshot\first time
	if(currProcess == NULL)
	{
	 //create new process and add it to the snapshot process list
	  snapshotProcess* newProcess = addProcess(newSnapshot);
	  
	  strcpy(newProcess->Name, shortProcessName);
	
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
		newProcess->ProcessID = processID;
	  }

	  //add the new process dll's list to the new process list
	  // Get Dlls List
	  if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	  {
		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			// Get the full path to the module's file.

			if (GetModuleFileNameEx(hProcess, hMods[i], wDllName, MAX_PATH))
			{

				// Convert to regular char array (string)
				char dllName[MAX_PATH];
				size_t numConverted;
				wcstombs_s(&numConverted, dllName, MAX_PATH, wDllName, MAX_PATH);
				dLL_Process* tempDll = addDLL(newProcess); 
				strcpy(tempDll->Name, dllName);

				if (tempDll->numberID > 1)
				{
					tempDll->numberID = tempDll->prev->numberID + 1;
				}
			}
			
		}
	  CloseHandle(hProcess);
	  return newProcess;
	}
}
	
	// to add information to an existed process
	else
	{
		currProcess = newSnapshot->processHead;
		unsigned int processCount = 1;
		char signal;

		//to find the process in the snapshot
		while (processCount <= newSnapshot->processTail->ProcessPlace)
		{
			
			// if the Process isnt in the snapshot then adding it to current snapshot
			if (currProcess == NULL)
			{
				getProcess(processID, newSnapshot, NULL);
				processCount = newSnapshot->processTail->ProcessPlace + 1;
			}

			//found the process in the process list
			else if ((signal = strcmp(currProcess->Name, shortProcessName)) == 0)
			{

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
					currProcess->ProcessID = processID;
				}

				// Get Dlls List
				if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
				{
					for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
					{
						// Get the full path to the module's file.

						if (GetModuleFileNameEx(hProcess, hMods[i], wDllName, MAX_PATH))
						{
							dllCount = 1;
							dllChecker = currProcess->DLLhead;
							// Convert to regular char array (string)
							char dllName[MAX_PATH];
							size_t numConverted;
							wcstombs_s(&numConverted, dllName, MAX_PATH, wDllName, MAX_PATH);

							// check if dll is in the list
							while (dllCount <= currProcess->DLLTail->numberID)
							{

								//the dll isnt in the list so create new dll struct and add it to the current process dll linked list
								if (dllChecker == NULL)
								{
									newDLL = addDLL(currProcess);
									strcpy(newDLL->Name, dllName);
									dllCount = newDLL->numberID + 1;
								}
								//found the dll in the dll list
								else if ((signal = strcmp(dllChecker->Name, dllName)) == 0) 
								{
									signal = strcmp(dllChecker->Name, dllName);
									dllCount = currProcess->DLLTail->numberID + 1;
								}
								else
								{
									dllChecker = dllChecker->next;
								}
							}
						}
					}
				}
				processCount = newSnapshot->processTail->ProcessPlace + 1;
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
void StartSnapshotCreation(unsigned int SnapshotsCount, snapshot* newSnapshot,snapshotProcess* currProcess) {

	// if count equal to zero meaning is finished the last sum and we can sort the snapshot
	if (SnapshotsCount == 0)
	{
		Log_Event("Finished snapshot creation");
		sortProcesses(newSnapshot);
		return 0;
	}

	// Get Processes
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	// * Receive all process ID and put in aProcesses Array
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		Log_Error(GetLastError());
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
	StartSnapshotCreation(SnapshotsCount - 1, newSnapshot, currProcess);
}

//bubble sort algorithem
void sortProcesses(snapshot* snaphotPtr)
{
	
	snapshotProcess* processPtr;
	int signal = 1;
	int place;

	Log_Event("Started sorting processes");

	// for knowing there was no replace in the whole loop meaning its sorted
	while (signal != 0)
	{
		signal = 0;
		place = 1;
		processPtr = snaphotPtr->processHead;

		//keep going through all the list
		while (processPtr != NULL)
		{
			//ptr is the last valueable in the list
			if (processPtr->next == NULL) {

			}
			//if next process have less dll than switching with him    **equal=do nothing keep going.
			else if (processPtr->dllAmount > processPtr->next->dllAmount)
			{
				// head and tail need special actions 
				 if (processPtr == snaphotPtr->processHead) {

					 processPtr->prev = processPtr->next;
					 processPtr->next = processPtr->next->next;
					 processPtr->prev->next = processPtr;
					 processPtr->prev->prev = NULL;
					 processPtr->next->prev = processPtr;

					 snaphotPtr->processHead = processPtr->prev;
				 }
				 else if (processPtr->next == snaphotPtr->processTail)
				 {
					 processPtr->prev->next = processPtr->next;
					 processPtr->next->prev = processPtr->prev;
					 processPtr->next->next = processPtr;
					 processPtr->prev = processPtr->next;
					 processPtr->next = NULL;

					 snaphotPtr->processTail = processPtr;
				 }

				 //regular switch in the list
				 else
				 {
					 processPtr->prev->next = processPtr->next;
					 processPtr->next->prev = processPtr->prev;
					 processPtr->next->next->prev = processPtr;
					 processPtr->prev = processPtr->next;
					 processPtr->next = processPtr->next->next;
					 processPtr->prev->next = processPtr;
				 }
				signal++;
			}

			processPtr->ProcessPlace = place;
			place++;
			processPtr = processPtr->next;
		}
	}
	Log_Event("Finished sorting");
}

//free and reset all snapshots from bottom (dll) to top (the snapshot itself)
void ResetSnapshots()
{

    snapshot* snapshotPtr;
	snapshotProcess* processPtr;
	dLL_Process* dllPtr;

	Log_Event("ResetSnapshots function called");

	while (snapshotTail != NULL)
	{
		snapshotPtr = snapshotTail;
		snapshotTail = snapshotTail->prev;

		while (snapshotPtr->processTail != NULL)
		{
			processPtr = snapshotPtr->processTail;
			snapshotPtr->processTail = snapshotPtr->processTail->prev;

			while (processPtr->DLLTail != NULL)
			{
				if (processPtr->DLLhead==NULL)
				{
                 // cant free because there is no dll list
					processPtr->DLLTail = NULL;
				}
				else
				{
					dllPtr = processPtr->DLLTail;
					processPtr->DLLTail = processPtr->DLLTail->prev;
					free(dllPtr);
				}
			}
			free(processPtr);
		}
		free(snapshotPtr);
	}
	snapshotHead = NULL;
	Log_Event("ResetSnapshots function finished succesfully");
}