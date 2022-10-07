#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "Tsur_Log.h"
#pragma warning(disable:4996)

#define FOPEN_ERROR "File_OpenError.log"
char FileAddress[1010];

time_t timeForLog;

char currentTime(char arr[10000]) {

	time(&timeForLog);
	struct tm* timeStructForLog = localtime(&timeForLog);
	sprintf(arr, "%d/%d/%d:%d.%d.%d -", timeStructForLog->tm_year+1900, timeStructForLog->tm_mon+1, timeStructForLog->tm_mday, timeStructForLog->tm_hour,timeStructForLog->tm_min ,timeStructForLog->tm_sec);

	return arr;
}

// file name must be in specification (without file ending)
void Log_Init(char filename[1000]) {

	sprintf(FileAddress, "%s.log", filename);

	FILE* fileOpener = fopen(FileAddress, "a");
	if (!fileOpener) {

		FILE* fileOpenerError = fopen(FOPEN_ERROR, "a");
		char ERROR[100];
		currentTime(ERROR);
		sprintf(ERROR, "%s  ERROR - Error while trying to open log file with enterd filename in function: Log_Init\n",ERROR);
		fputs(ERROR, fileOpenerError);
		fclose(fileOpenerError);
	}
	else
	{
		char timeLog[100];
		currentTime(timeLog);
		sprintf(timeLog, "%s EVENT - Log file initialized\n", timeLog);
		fputs(timeLog, fileOpener);
		

	}
	fclose(fileOpener);
}

void Log_Error(char msg[1000]) {

   FILE* f = fopen(FileAddress,"a");
   if (!f) {

	   FILE* fileOpenerError = fopen(FOPEN_ERROR, "a");
	   char ERROR[100];
	   currentTime(ERROR);
	   sprintf(ERROR, "%s  ERROR - Error while trying to open log file in function: Log_Error\n", ERROR);
	   fputs(ERROR, fileOpenerError);
	   fclose(fileOpenerError);
   }
   else
   {

	   char FullMsg[1000];
	   currentTime(FullMsg);
	   sprintf(FullMsg, "%s  ERROR - %s\n", FullMsg, msg);
	   fputs(FullMsg, f);
	   
   }
   fclose(f);
   }
   
void Log_Warning(char msg[1000]) {

	FILE* f = fopen(FileAddress, "a");
	if (!f) {

		FILE* fileOpenerError = fopen(FOPEN_ERROR, "a");
		char ERROR[100];
		currentTime(ERROR);
		sprintf(ERROR, "%s  ERROR - Error while trying to open log file in function: Log_Warning\n", ERROR);
		fputs(ERROR, fileOpenerError);
		fclose(fileOpenerError);
	}
	else
	{

		char FullMsg[1000];
		currentTime(FullMsg);
		sprintf(FullMsg, "%s  WARNING - %s\n", FullMsg, msg);
		fputs(FullMsg, f);

	}
	fclose(f);
}

void Log_Event(char msg[1000]) {


	FILE* f = fopen(FileAddress, "a");
	if (!f) {

		FILE* fileOpenerError = fopen(FOPEN_ERROR, "a");
		char ERROR[100];
		currentTime(ERROR);
		sprintf(ERROR, "%s  ERROR - Error while trying to open log file in function: Log_Event\n", ERROR);
		fputs(ERROR, fileOpenerError);
		fclose(fileOpenerError);
	}
	else
	{

		char FullMsg[1000];
		currentTime(FullMsg);
		sprintf(FullMsg, "%s  EVENT - %s\n", FullMsg, msg);
		fputs(FullMsg, f);

	}
	fclose(f);
}

