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


//generating uniq about me page 
void generateAboutMe(char* homePage)
{
	Log_Event("Called GenerateAboutMe");
	char* path;
	char signal = 0;
	char pageName[100];
	char lineToolArr[100];
	FILE* f;

	path = getPath();
	//get file name
	sprintf(pageName, "%s_AboutMe.html",snapshotHead->timeCreated);

	//user didnt change the path
	if ((signal = strcmp(path, "relative")) == 0)
	{
		f = fopen(pageName, "w");
	}
	//user did change the path
	else
	{
		sprintf(path, "%s\\%s", path, pageName);
		f = fopen(path, "w");
	}
	free(path);

	if (!f)
	{
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		
		fputs("<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='UTF-8'>\n<meta http-equiv='X-UA-Compatible' content='IE=edge'>\n", f);
		fputs("<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n<title>About Me</title>\n<link rel='stylesheet' href='stylesFolder/aboutMe.css'>\n", f);
		fputs("<link rel='preconnect' href='https://fonts.googleapis.com'>\n<link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>\n", f);
		fputs("<link href='https://fonts.googleapis.com/css2?family=Lato:wght@400;700&display=swap' rel='stylesheet'>\n</head>\n<body>\n<table class='navTable'>\n ", f);

		//entering the dynamic links
		sprintf(lineToolArr, "<td><a href='%s' class='home'>Home</a></td>\n", homePage);
		fputs(lineToolArr, f);

		sprintf(lineToolArr, "<td><a href='%s' class='about'>About Me</a></td>\n</table>\n", pageName);
		fputs(lineToolArr, f);
		// 

		fputs("<div class='profile'>\n<img src='Pictures\\me_modified.png' alt='my picture'>\n<div class='main'>\n<h2>Hello.</h2>\n<p>My name is Tsur <br> I'm 22 years old from Tiberias, Israel</p>\n</div>\n</div>\n", f);
		fputs("<div class='skills'>\n <div class='insideDiv'>\n<h3>Skills</h3>\n", f);
		fputs("<p> Currently learning and evolving in Full-stack development Bootcamp by Tzionet-Company,<br>I sit hours coding almost every day, Trying to improve and do my best, I also enjoy it(; </p>\n", f);
		fputs("</div>\n<img src='Pictures/skills_modified.png' alt='programming'>\n</div>\n<div class='Hobbies'>\n<img src='Pictures/hobbies.jpg' alt='sony_controllers'>\n", f);
		fputs("<div class='insideDiv'>\n<h3>Hobbies</h3>\n<p>Beside writing code of course..I love working out at the gym and play video games, <br> I also love football(Both playing and watching) I am a big fan of Manchester United football team. </p></div></div>\n", f);
		fputs("<div class='footer'>\n<h3> Contact Me</h3>\n<a href='https://github.com/TsurHazan'> <svg enable-background='new 0 0 512 512' id='Layer_1' version='1.1' viewBox='0 0 512 512' xml:space='preserve' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'><g><path d='M256.6,507.8C118.1,507.3,7.3,393.8,8.5,254.7C9.6,118.1,119.9,4.6,260.2,6.3   C397.3,7.9,507.1,121.1,505.5,260C504,396,394.7,507.7,256.6,507.8z M221.2,377.5c-1.6-0.3-2.3-0.4-3.1-0.5   c-19.1-2.7-37-8.4-53-19.8c-17.1-12.2-27.6-28.6-31.9-48.7c-4.4-20.5-2.7-41.2,0.5-61.7c2.2-14.1,7-27.4,18-37.5   c1.6-1.5,1.5-2.7,0.7-4.7c-6-16.6-5.3-33.3-0.3-50c1-3.3,2.6-4.7,6.1-3.4c4.2,1.5,8.5,2.8,12.4,5.1c10.7,6.3,18.9,15,26.1,24.9   c1.8,2.4,3,2.8,5.5,1.1c6.2-4.3,13.5-5.6,20.6-6.9c17.2-3.2,34.5-2.6,51.8-1.8c10.1,0.5,20.1,2.3,29.7,5.9c3,1.1,5.7,5,8.5,3.5   c2.8-1.4,4.5-5.2,6.7-7.8c8.8-10.6,18.9-19.4,32.5-23.7c4.4-1.4,6.4-0.7,7.9,4c5,16.3,5.7,32.4-0.6,48.4c-1,2.5-0.8,4.3,1.3,6.2   c8.3,7.7,13.1,17.6,15.6,28.5c4.3,18.6,5.4,37.6,4.2,56.6c-1.2,18.2-7.1,34.8-19.3,48.8c-16.4,18.8-37.8,28.1-61.9,32.2   c-2.8,0.5-5.7,1-8.7,1.5c7.1,11.1,10.5,22.6,10.6,35c0.1,14.3,0,28.7,0,43c0,9.3,0,18.6,0,28c15.2-1.5,43.6-11.6,63.4-22.4   c92.3-50.3,138.9-154.2,115.4-257.1C452.1,81.8,331,4.5,208.6,31C93,56.1,13,167.5,30.4,289.9c8.1,56.9,34.2,104.5,77.4,142.4   c28.5,25,61.5,41.7,98.5,50.3c2.9,0.7,4.2,0.5,4.1-3c-0.2-9.8-0.2-19.7,0-29.5c0-3.3-0.6-4.3-4.2-3.6c-6.5,1.3-13.2,2-19.9,1.6   c-21.2-1.1-38.4-9.5-50.5-27.5c-4.1-6.1-6.4-13.2-10.3-19.3c-6.9-10.7-13-22-24.5-28.9c-1.5-0.9-3.3-2.3-2.4-4.4   c0.8-2,3-1.7,4.8-1.9c12.8-1,23.3,3.8,32,13c4.6,4.9,7.5,11,11.5,16.3c13.3,17.7,38.7,25.3,59.5,17.8c3-1.1,3.9-2.6,4.3-5.7   C211.9,397,213.9,386.7,221.2,377.5z' fill='#120606'/></g></svg></a>\n", f);
		fputs("<a href='https://www.linkedin.com/in/tsur-hazan-772235254/'> <svg height='50px' version='1.1' viewBox='0 0 50 50' width='50px' xmlns='http://www.w3.org/2000/svg' xmlns:sketch='http://www.bohemiancoding.com/sketch/ns' xmlns:xlink='http://www.w3.org/1999/xlink'><title/><defs/><g fill='none' fill-rule='evenodd' id='Page-1' stroke='none' stroke-width='1'><g fill='#000000' id='LinkedIn'><path d='M25,50 C38.8071194,50 50,38.8071194 50,25 C50,11.1928806 38.8071194,0 25,0 C11.1928806,0 0,11.1928806 0,25 C0,38.8071194 11.1928806,50 25,50 Z M25,47 C37.1502651,47 47,37.1502651 47,25 C47,12.8497349 37.1502651,3 25,3 C12.8497349,3 3,12.8497349 3,25 C3,37.1502651 12.8497349,47 25,47 Z M14,20.1180479 L14,34.6581834 L18.7100851,34.6581834 L18.7100851,20.1180479 L14,20.1180479 Z M16.6646962,13 C15.0534058,13 14,14.0858611 14,15.5115122 C14,16.9076331 15.0222711,18.0247614 16.6035556,18.0247614 L16.6336556,18.0247614 C18.2759867,18.0247614 19.2988222,16.9076331 19.2988222,15.5115122 C19.2682519,14.0858611 18.2759867,13 16.6646962,13 Z M30.5769213,20.1180479 C28.076176,20.1180479 26.9565501,21.5293199 26.3314108,22.5193527 L26.3314108,20.4598644 L21.6207614,20.4598644 C21.6828427,21.8242356 21.6207614,35 21.6207614,35 L26.3314108,35 L26.3314108,26.8795887 C26.3314108,26.445032 26.3619812,26.0115368 26.4865199,25.7004084 C26.826932,24.83226 27.6020069,23.9334233 28.9032674,23.9334233 C30.6083381,23.9334233 31.2899149,25.2667202 31.2899149,27.2206333 L31.2899149,34.999614 L35.9998119,34.999614 L36,26.6627446 C36,22.1966439 33.6763743,20.1180479 30.5769213,20.1180479 Z M30.5769213,20.1180479' id='Oval-1'/></g></g></svg></a>\n", f);
		fputs("<a href='https://www.zion-net.co.il/'><img src='Pictures/tzionet.jpg' alt=''></a>\n</div>\n</body>\n</html>", f);
		fclose(f);
		Log_Event("successfully generated AboutMe page");
	}
}


//making a page with all the processes information including dll list
int GenerateSnapshotPage(snapshot* snapshotPtr,char* homePage)
{
	Log_Event("Called GenerateSnapshotPage");

	char* path;
	char signal = 0;
	char pageName[300];
	char currentTimeArr[50];
	char lineToolArr[300];
	snapshotProcess* processPtr=snapshotPtr->processHead;
	dLL_Process* dllPtr;
	FILE* f;

	path = getPath();
	//get file name
	sprintf(pageName,"%s_Snapshot%d.html",snapshotHead->timeCreated ,snapshotPtr->ID);

	//user didnt change the path
	if ((signal = strcmp(path, "relative")) == 0)
	{
		f = fopen(pageName, "w");
	}
	//user did change the path
	else
	{
		sprintf(path, "%s\\%s", path, pageName);
		f = fopen(path, "w");
	}
	free(path);
	 
	if(!f)
	{
		Log_Error(GetLastError());
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

		sprintf(lineToolArr, "<td><a href='%s_AboutMe.html' class='about'>About Me</a></td>\n</table>\n\n", snapshotHead->timeCreated);
		fputs(lineToolArr, f);

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

		Log_Event("SnapshotPage generated successfully");
		fclose(f);
	}
}

//get path to where the user want to generate the files
char* getPath()
{
	Log_Event("called getPath function");
	char* str;
	char fileContent[401];
	char* path;

	FILE* f = fopen("Configuration.txt", "r");
	if (!f)
	{
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		path = (char*)malloc(sizeof(char)*401);
		if (!path)
		{
			Log_Warning(" while trying to malloc in getPath");
			Log_Error(GetLastError());
			return 1;
		}

		fgets(fileContent, 400, f);
		str = strtok(fileContent, ":");
	    str = strtok(NULL, "\n");
		strcpy(path, str);

		fclose(f);
		return path;
	}
}

//generating the main page for all the snapshots
int GenerateHomePage(snapshot* snapshotHead)
{
	Log_Event("Called GenerateHomePage");
	char* path;
	char homePageName[450];
	char headLines[550];
	char fullLine[200];
	char signal = 0;
	snapshot* snpPtr = snapshotHead;
	FILE* f;

	//get file name
	 path = getPath();

	 //file name
	 sprintf(homePageName, "%s_HomePage.html", snapshotHead->timeCreated);

	 //user didnt change the path
	 if ((signal = strcmp(path, "relative")) == 0)
	 {
		 f = fopen(homePageName, "w");
	 }
	 //user did change the path
	 else
	 {
		 sprintf(path,"%s\\%s",path,homePageName);
		 f = fopen(path, "w");
	 }
	 free(path);

	if (!f)
	{
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		//apply html head 
		
		strcpy(headLines,"<!DOCTYPE html>\n<html lang = 'en'>\n<head>\n<meta charset = 'UTF-8'>\n<meta http-equiv= 'X-UA-Compatible' content='IE=edge'>\n<meta name = 'viewport' content = 'width=device-width,initial-scale=1.0'>\n<title>Tsur Project</title>\n<link rel ='stylesheet' href = 'stylesFolder/Home.css'>\n<link rel = 'preconnect' href='https://fonts.googleapis.com'>\n<link rel = 'preconnect' href = 'https://fonts.gstatic.com' crossorigin>\n<link href = 'https://fonts.googleapis.com/css2?family=Lato:wght@400;700&display=swap' rel = 'stylesheet'>\n</head>\n<body>\n",f);
		fputs(headLines, f);

		sprintf(fullLine, "<table class='navTable'>\n<td><a href = '%s'  class='home'>Home</a></td>\n",homePageName);
		fputs(fullLine, f);

		sprintf(fullLine, "<td><a href = '%s_AboutMe.html' class = 'about'>About Me</a></td>\n</table>\n<div class = 'container'>\n",snapshotHead->timeCreated);
		fputs(fullLine, f);


		//enter snapshot item block in html
		while (snpPtr!=NULL)
		{
			char itemHolder[200];
			strcpy(itemHolder, "<div class='item'>\n");
			fputs(itemHolder, f);
			sprintf(itemHolder, "<p>Snasphot: %d</p>\n", snpPtr->ID);
			fputs(itemHolder, f);
			sprintf(itemHolder, "<p>Processes: %d</p>\n", snpPtr->processTail->ProcessPlace);
			fputs(itemHolder, f);
			sprintf(itemHolder, "<p>Date:%s</p>\n", snpPtr->timeCreated);
			fputs(itemHolder, f);
			sprintf(itemHolder, "<a href='%s_Snapshot%d.html'>Show Snasphot </a>\n</div>\n",snapshotHead->timeCreated,snpPtr->ID);
			fputs(itemHolder, f);
			GenerateSnapshotPage(snpPtr, homePageName);
			snpPtr = snpPtr->next;
		}
		generateAboutMe(homePageName);
		fclose(f);
		Log_Event("GenerateHomePage finished successfully");
		return 0;
	}
}

int readFile()
{
	Log_Event("Called readFile function");
	char filename[1000];

	printf("\n\nWhat is your save file name?:");
	scanf(" %s", &filename);

	FILE* f = fopen(filename, "rb");
	if (!f)
	{
		Log_Error("there is no saved file or file name was enterd wrong");
		Log_Error(GetLastError());
		return 1;
	}
	else
	{
		
		header* headerPtr=(header*)malloc(sizeof(header));
		if (!headerPtr)
		{
			Log_Warning(" while trying to malloc for header in readFile");
			Log_Error(GetLastError());
			return 1;
		}

		fread(headerPtr, sizeof(header), 1, f);

		//read snapshots
		for (int i = 0; i < headerPtr->snapshotsCount; i++)
		{
		  snapshot* snapshotPtr = (snapshot*)malloc(sizeof(snapshot));
		  if (!snapshotPtr)
		  {
			  Log_Warning(" while trying to malloc for snapshot in readFile");
			  Log_Error(GetLastError());
			  return 1;
		  }

		 fread(snapshotPtr, sizeof(snapshot), 1, f);
		 snapshotPtr->processHead = NULL;

		  //read processes
		  for (int i = 0; i < snapshotPtr->processAmount; i++)
		  {

		  snapshotProcess* processptr=(snapshotProcess*)malloc(sizeof(snapshotProcess));
		  if (!processptr)
		  {
			  Log_Warning(" while trying to malloc for snapshotProcess in readFile");
			  Log_Error(GetLastError());
			  return 1;
		  }

		  fread(processptr, sizeof(snapshotProcess), 1, f);
		  processptr->DLLhead = NULL;

		    //read dlls
		    for (int i = 0; i < processptr->dllAmount; i++)
		    {

			 dLL_Process* dllPtr=(dLL_Process*)malloc(sizeof(dLL_Process));
			 if (!dllPtr)
			 {
				 Log_Warning(" while trying to malloc for dLL_Process in readFile");
				 Log_Error(GetLastError());
				 return 1;
			 }

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
		Log_Event("File loaded succesfully");
		printf("\n+File loaded succesfully");
	}
}

int saveToFile()
{

	Log_Event("called saveToFile function ");

    //if there is no snapshot
	if (snapshotHead == NULL)
	{
		Log_Error("Currently there is no existing list");
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
		Log_Event("Created and saved in new file");
		printf("\n+File saved");
	}
}
