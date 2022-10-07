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

snapshot* snapshotHead = NULL;
snapshot* snapshotTail = NULL;

int main()
{

	snapshot* newSnapshot;
	char quit = 'M';
	unsigned int runCounter = 0;
	char runAction = 0;

	printf("\nPress 'A' to ADD 1 Snapshot \nPress 'B' to SUM 20 Snapshots\nPress 'X' to START a run of snapshots");
	printf("\nPress 'V' to END the run of snapshots\nPress 'G' to Generate all snapshots to html file\nPress 'R' to RESET the snapshots list");
	printf("\nPress 'S' to SAVE snapshots to file\nPress 'L' to LOAD snapshots list from file\nPress 'M' to Show menu\nPress 'Q' to quit the programm: ");

	//comfortable user response - no need to cap on\off **but keyboard must be on english
	while (quit != 'Q' && quit != 'q')
	{

		quit = getch();

		switch (quit)
		{

		case 'A':
		case 'a': 
			newSnapshot = addSnapshot();
			addProcesses(1, newSnapshot,NULL);
			printf("\nNew snapshot added");
			break;
			
		case 'B':
		case 'b':
			newSnapshot = addSnapshot();
			addProcesses(20, newSnapshot,NULL);
			printf("\n\nNew 20 processes sum snapshot added");
			break;

		case 'X':
		case 'x':
			printf("\n\nStrated a run");
			while (runAction <  1)
			{
				runCounter += 1;
				Sleep(1000);

				if (kbhit())
				{
					quit = getch();
					if (quit == 'v' || quit == 'V')
					{
						runAction = 2;
						newSnapshot = addSnapshot();
						addProcesses(runCounter, newSnapshot, NULL);
					}
				}
			}
			break;

		case 'V':
		case 'v':printf("\n\nThere is no working run right now");
			break;

		case 'G':
		case 'g':;
			break;

		case 'R':
		case 'r':;
			break;

		case 'S':
		case 's':;
			break;

		case 'L':
		case 'l':;
			break;

		case 'M':
		case 'm':
			printf("\n\nPress 'A' to ADD 1 Snapshot \nPress 'B' to SUM 20 Snapshots\nPress 'X' to START a run of snapshots");
			printf("\nPress 'V' to END the run of snapshots\nPress 'G' to Generate all snapshots to html file\nPress 'R' to RESET the snapshots list");
			printf("\nPress 'S' to SAVE snapshots to file\nPress 'L' to LOAD snapshots list from file\nPress 'M' to Show menu\nPress 'quit' to quitUIT the programm: ");
			break;

		case 'Q':
		case 'q': 
			printf("\n\n Goodbye!");
			quit = 'Q';
			break;

		default:
			printf("\n\nPlease enter a valid char\n\n");
			break;
		}
	}
	return 0;
}