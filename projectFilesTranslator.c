#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <Psapi.h>
#include "Tsur_Log.h"
#include "projectFilesTranslator.h"
#include "DataStructureAndFunctions.h"
#pragma warning(disable:4996)


int GenerateSnapshotPage(snapshot* snapshotPtr,char* homePage)
{

	char pageName[1000];
	char currentTimeArr[100];
	char lineToolArr[1000];
	snapshotProcess* processPtr=snapshotPtr->processHead;
	dLL_Process* dllPtr;


	//get file name
	sprintf(pageName,"Snapshot%d-%s", snapshotPtr->ID, homePage);
	FILE* f = fopen(pageName, "w");
	if(!f)
	{
		//log error
		//get last error
		return 1;
	}
	else
	{
		//get current Date
		ShortCurrentTime(currentTimeArr);

		//enter head lines
		fputs("<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='UTF-8'>\n<meta http-equiv='X-UA-Compatible' content='IE = edge'>\n", f);
		fputs("<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n", f);

		//get title name
		sprintf(lineToolArr, "<title>Snapshot %d</title>\n", snapshotPtr->ID);
		fputs(lineToolArr, f);

		fputs("<link rel='stylesheet' href='stylesFolder/snapshotStyle.css'>\n", f);
		fputs("<link rel='preconnect' href='https://fonts.googleapis.com'>\n", f);
		fputs("<link rel='preconnect' href='https://fonts.gstatic.com' crossorigin> \n", f);
		fputs("<link href='https://fonts.googleapis.com/css2?family=Lato:wght@400;700&display=swap' rel='stylesheet'> \n", f);
		fputs("</head>\n<body>\n", f);
		fputs("<table class='navTable'> \n", f);

		//get father snapshot for home button
		sprintf(lineToolArr,"<td><a href='%s' class='home'>Home</a></td>\n",homePage);
		fputs(lineToolArr, f);

		fputs("<td><a href='aboutMe.html' class='about'>About Me</a></td> \n", f);
		fputs("</table>\n\n", f);

		fputs("<table class='headTable'> \n", f);

		//enter h1 snapshot id
		sprintf(lineToolArr, "<tr>\n<td colspan='2'><h1>Snapshot: %d</h1></td>\n</tr>\n", snapshotPtr->ID);
		fputs(lineToolArr, f);

		//enter Date and process amount
		sprintf(lineToolArr,"<tr>\n<td><p> Date: %s</p></td>\n<td><p>Processes amount: %d</p></td>\n</tr>\n</table>\n<div class='tablesDiv'>\n",currentTimeArr,snapshotPtr->processTail->ProcessPlace);
		fputs(lineToolArr, f);

		while (processPtr!=NULL)
		{
            // table head row
			fputs("<table class='processTable'>\n<tr>\n<th>Process Place</th>\n<th>Process Name</th>\n<th>ID</th>\n<th>PageFaultCount</th>\n", f);
			fputs("<th>WorkingSetSize</th>\n<th>QuotaPagedPoolUsage</th>\n<th>QuotaPeakPagedPoolUsage</th>\n<th>PagefileUsage</th>\n<th>Dll amount</th>\n</tr>\n", f);

			//process info row
			
			sprintf(lineToolArr, "<tr>\n<td>%d</td>\n<td>%s</td>\n<td>%d</td>\n<td>%d</td>\n<td>%d</td>\n", processPtr->ProcessPlace, processPtr->Name, processPtr->ProcessID, processPtr->ProcessInfo.PageFaultCount, processPtr->ProcessInfo.WorkingSetSize);
			fputs(lineToolArr, f);
			sprintf(lineToolArr, "\n<td>%d</td>\n<td>%d</td>\n<td>%d</td>\n", processPtr->ProcessInfo.QuotaPagedPoolUsage, processPtr->ProcessInfo.QuotaPeakPagedPoolUsage, processPtr->ProcessInfo.PagefileUsage);
			fputs(lineToolArr, f);

			// if we got no permision to the dll list
			if (processPtr->DLLhead == NULL)
			{
				fputs("<td>Unknown</td>\n", f);
			}
			else
			{
				sprintf(lineToolArr, "<td>%d</td>\n", processPtr->DLLTail->numberID);
				fputs(lineToolArr, f);
			}
			fputs("</tr>\n", f);
			//dll list row

			sprintf(lineToolArr, "<tr>\n<td colspan='12'><a href='#target%d' id='target%d' class='target'>\n", processPtr->ProcessPlace, processPtr->ProcessPlace);
			fputs(lineToolArr, f);
			fputs("<p class='showList'>Show DLL List</p>\n", f);
			fputs("<span>\n<table class='dllList'>\n", f);
			sprintf(lineToolArr, "<tr><td><a class='closeList target' href='%s'>Close List</a></td></tr>\n", pageName);
			fputs(lineToolArr, f);

			dllPtr = processPtr->DLLhead;
			while (dllPtr!=NULL)
			{
				sprintf(lineToolArr, "<tr><td>%d  %s</td></tr>\n", dllPtr->numberID, dllPtr->Name);
				fputs(lineToolArr, f);
				dllPtr = dllPtr->next;
			}
			fputs("</table>\n</span>\n</a></td></tr>\n</table>\n", f);
			processPtr = processPtr->next;
		}
		fputs("</div>\n</body>\n</html>", f);
		fclose(f);
	}
}

int GenerateHomePage(snapshot* snapshotHead)
{
	
	char homePageName[1000];
	char headLines[1000];
	char fullLine[1000];
	int counter = 0;
	snapshot* snpPtr = snapshotHead;

	//get file name
	sprintf(homePageName, "%s_HomePage.html",snapshotHead->timeCreated);

	FILE* f = fopen(homePageName, "w");
	if (!f)
	{
		
		//log error
		return 1;
	}
	else
	{
		//apply html head 
		
		strcpy(headLines, "<!DOCTYPE html>\n<html lang = 'en'>\n<head>\n<meta charset = 'UTF-8'>\n<meta http-equiv= 'X-UA-Compatible' content='IE=edge'>\n<meta name = 'viewport' content = 'width=device-width,initial-scale=1.0'>\n<title>Tsur Project</title>\n<link rel ='stylesheet' href = 'stylesFolder/Home.css'>\n<link rel = 'preconnect' href='https://fonts.googleapis.com'>\n<link rel = 'preconnect' href = 'https://fonts.gstatic.com' crossorigin>\n<link href = 'https://fonts.googleapis.com/css2?family=Lato:wght@400;700&display=swap' rel = 'stylesheet'>\n</head>\n<body>\n");
        fputs(headLines,f);
		strcpy(fullLine, "<table class='navTable'>\n<td><a href = ");
		strcat(fullLine, homePageName);
		strcat(fullLine, " class='home'>Home</a></td>\n<td><a href = 'aboutMe.html' class = 'about'>About Me</a></td>\n</table>\n<div class = 'container'>\n");
		fputs(fullLine, f);


		//enter snapshot item block in html
		while (snpPtr!=NULL)
		{
			char itemHolder[1000];
			strcpy(itemHolder, "<div class='item'>\n");
			fputs(itemHolder, f);
			sprintf(itemHolder, "<p>Snasphot: %d</p>\n", snpPtr->ID);
			fputs(itemHolder, f);
			sprintf(itemHolder, "<p>Processes: %d</p>\n", snpPtr->processTail->ProcessPlace);
			fputs(itemHolder, f);
			sprintf(itemHolder, "<p>Date:%s</p>\n", snpPtr->timeCreated);
			fputs(itemHolder, f);
			sprintf(itemHolder, "<a href='Snapshot%d-%s'>Show Snasphot </a>\n</div>\n",snpPtr->ID,homePageName);
			fputs(itemHolder, f);
			GenerateSnapshotPage(snpPtr, homePageName);
			snpPtr = snpPtr->next;
		}

		fclose(f);
		return 0;
	}


}

int readFile()
{
	
	char filename[1000];

	printf("\n\nWhat is your save file name?:");
	scanf(" %s", &filename);

	FILE* f = fopen(filename, "rb");
	if (!f)
	{
		//log call last error
		return 1;
	}
	else
	{
		
		header* headerPtr=(header*)malloc(sizeof(header));
		fread(headerPtr, sizeof(header), 1, f);

		//read snapshots
		for (int i = 0; i < headerPtr->snapshotsCount; i++)
		{
		  snapshot* snapshotPtr = (snapshot*)malloc(sizeof(snapshot));
		 fread(snapshotPtr, sizeof(snapshot), 1, f);
		 snapshotPtr->processHead = NULL;

		  //read processes
		  for (int i = 0; i < snapshotPtr->processAmount; i++)
		  {

		  snapshotProcess* processptr=(snapshotProcess*)malloc(sizeof(snapshotProcess));
		  fread(processptr, sizeof(snapshotProcess), 1, f);
		  processptr->DLLhead = NULL;

		    //read dlls
		    for (int i = 0; i < processptr->dllAmount; i++)
		    {

			 dLL_Process* dllPtr=(dLL_Process*)malloc(sizeof(dLL_Process));
			 fread(dllPtr, sizeof(dLL_Process), 1, f);

			 if (processptr->DLLhead == NULL)
			 {
				 dllPtr->next = NULL;
				 dllPtr->prev = NULL;
				 processptr->DLLhead = dllPtr;
				 processptr->DLLTail = dllPtr;
			 }
			 else
			 {
				 dllPtr->next = NULL;
				 dllPtr->prev = processptr->DLLTail;
				 processptr->DLLTail->next = dllPtr;
				 processptr->DLLTail = dllPtr;
			 }
					        
		    }

			if (snapshotPtr->processHead == NULL)
			{
				processptr->prev = NULL;
				processptr->next = NULL;
				snapshotPtr->processHead = processptr;
				snapshotPtr->processTail = processptr;

			}
			else
			{
				processptr->next = NULL;
				processptr->prev = snapshotPtr->processTail;
				snapshotPtr->processTail->next = processptr;
				snapshotPtr->processTail = processptr;
			}

		  }
			if (snapshotHead == NULL)
			{
				snapshotPtr->prev = NULL;
				snapshotPtr->next = NULL;
				snapshotHead = snapshotPtr;
				snapshotTail = snapshotPtr;
				
			}
			else
			{
				snapshotTail->next = snapshotPtr;
				snapshotPtr->prev = snapshotTail;
				snapshotPtr->next = NULL;
				snapshotTail = snapshotPtr;
			}
		}
		printf("\n+File loaded succesfully");
	}
}

int saveToFile()
{
    //if there is no snapshot
	if (snapshotHead == NULL)
	{
		//write to log
		return 1;
	}

	char homePageName[1000];
	snapshot* snapshotptr=snapshotHead;
	snapshotProcess* processPtr;
	dLL_Process* dllPtr;

	//get file name
	sprintf(homePageName, "%s_Save.bin", snapshotHead->timeCreated);
	FILE* f = fopen(homePageName, "wb");
	if(!f) {
		//write to log
		//call last error
	}
	else
	{
		//make file header and write to file
		header* fileheader = (header*)malloc(sizeof(header));
		fileheader->snapshotsCount = snapshotTail->ID;
		fileheader->version = 1;
		fwrite(fileheader, sizeof(header), 1, f);
		free(fileheader);

		//go through all snapshots
		while (snapshotptr !=NULL)
		{
			fwrite(snapshotptr, sizeof(snapshot), 1, f);

			//go through all processes
			processPtr = snapshotptr->processHead;
			while (processPtr != NULL)
			{
				fwrite(processPtr, sizeof(snapshotProcess), 1, f);

				dllPtr = processPtr->DLLhead;
				//go through all dlls
				while (dllPtr!=NULL)
				{
					fwrite(dllPtr, sizeof(dLL_Process), 1, f);
					dllPtr = dllPtr->next;
				}
				processPtr = processPtr->next;
			}
			snapshotptr = snapshotptr->next;
		}
		fclose(f);
		printf("\n+File saved");
	}
}
