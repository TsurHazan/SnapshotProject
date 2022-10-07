#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

char currentTime(char arr[10000]);

void Log_Init(char filename[1000]);

void Log_Error(char msg[1000]);

void Log_Warning(char msg[1000]);

void Log_Event(char msg[1000]);

