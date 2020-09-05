#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "memory.h"
#include "helper.h"
// #include "../../json-c/json_object.h"

#define MAX_LENGTH 256

void appendMemory(char* memory, char* note) {
	FILE *toWrite;
	toWrite = fopen(note, "a");
	fprintf(toWrite, "%s\n", memory);
	fclose(toWrite);
}


int changeMemory(char* charRow, char* memory) {
	char currentNoteName[MAX_LENGTH];
	char currentNotePath[MAX_LENGTH];
	getCurrentNote(currentNotePath, currentNoteName);
	int result = checkRow(currentNotePath, charRow);
	if (result == -1) return -1;
	
	int row = atoi(charRow);
	
	FILE* source;
	source = fopen(currentNotePath, "r");

	FILE* target;
	char dirName[] = "background";
	char noteName[] = "BRIEF";
	char notePath[MAX_LENGTH];
	getNotePath(dirName, noteName, notePath);
	target = fopen(notePath, "w");

	char temp[MAX_LENGTH];
	char line[MAX_LENGTH];
	int counter = 0;

	while (fgets(line, sizeof(line), source)) {
		if (counter + 1 == row) {
			strcpy(temp, line);
			counter++;
			continue;
		}
		fprintf(target, "%s", line);
		counter++;
	}
	
	// the following is slightly odd but seems to work	
	int sizeMemory = strlen(temp);
	strncpy(memory, temp, sizeMemory - 1);
	memory[sizeMemory - 1] = '\0';	

	fclose(source);
	fclose(target);

	remove(currentNotePath);
	rename(notePath, currentNotePath);

	//writeToNote(currentNotePath, lines, counter);
	return 0;	
	
}


void moveMemory(char* args[], int numArgs) {
	char note[MAX_LENGTH];
	parseSpecialArgs(note, args, numArgs);
	
	char dirName[] = "notes";
	char notePath[MAX_LENGTH];
	getNotePath(dirName, note, notePath);
	
	struct stat st = {0};
	if (stat(notePath, &st) == -1) {
		printf("The note you are trying to add to does not exist. Please try again.\n");
		return;
	}
	int result = checkDefault(note);
	if (result == -1) return;

	char memoryToMove[MAX_LENGTH];
	result = changeMemory(args[2], memoryToMove);
	if (result == -1) return;

	appendMemory(memoryToMove, notePath);
	printf("Moved '%s' to '%s'\n", memoryToMove, note);
}


void copyMemory(char* args[], int numArgs) {
	char note[MAX_LENGTH];
	parseSpecialArgs(note, args, numArgs);

	char currentNoteName[MAX_LENGTH];
	char currentNotePath[MAX_LENGTH];
	getCurrentNote(currentNotePath, currentNoteName);

	char dirName[] = "notes";
	char notePath[MAX_LENGTH];
	getNotePath(dirName, note, notePath);
	
	struct stat st = {0};
	if (stat(notePath, &st) == -1) {
		printf("The note you are trying to add to does not exist. Please try again.\n");
		return;
	}
	int result = checkDefault(note);
	if (result == -1) return;

	
	result = checkRow(currentNotePath, args[2]);
	if (result == -1) return; 
	
	int row = atoi(args[2]);

	FILE* source = fopen(currentNotePath, "r");
	int counter = 0;
	
	char line[MAX_LENGTH];
	char temp[MAX_LENGTH];
	while (fgets(line, sizeof(line), source)) {
		if (counter + 1 == row) {
			strcpy(temp, line);
			counter++;
			continue;
		}
		counter++;
	}

	fclose(source);

	char memoryToCopy[MAX_LENGTH];

	// the following is slightly odd but seems to work	
	int sizeMemory = strlen(temp);
	strncpy(memoryToCopy, temp, sizeMemory - 1);
	memoryToCopy[sizeMemory - 1] = '\0';	

	appendMemory(memoryToCopy, notePath);
	printf("Copied '%s' to '%s'\n", memoryToCopy, note);
}


void removeMemory(char* row) {
	char memoryToRemove[MAX_LENGTH];
	int result = changeMemory(row, memoryToRemove);
	if (result == -1) return;

	printf("Removed memory '%s'\n", memoryToRemove);
}


void clearMemories() {
	char currentNotePath[MAX_LENGTH];
	char note[MAX_LENGTH];
	getCurrentNote(currentNotePath, note);

	char prompt[] = "Are you sure you want to clear your memories on your current note? \033[1mThere is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		fclose(fopen(currentNotePath, "w"));
		printf("Memories cleared\n");
	} else printf("Memory clearing aborted\n");	
}


void addMemory(char* args[], int numArgs) {
	char note[MAX_LENGTH];
	char currentNotePath[MAX_LENGTH];
	getCurrentNote(note, currentNotePath);
	char sansFirstWord[MAX_LENGTH];
	int result = parseUnaryArgs(sansFirstWord, args, numArgs);
	if (result == 1) {
		appendMemory(args[1], note);
		printf("Remembered '%s'\n", args[1]);
	} else {
		char memory[MAX_LENGTH];
		// The following is because the program considers the first word after program call to be the 'command'
		// This word must be added back
		strcpy(memory, args[1]);
		strcat(memory, " ");
		strcat(memory, sansFirstWord);

		appendMemory(memory, note);
		printf("Remembered '%s'\n", memory);
	}
}


void listMemories() {
	char notePath[MAX_LENGTH];
	char noteName[MAX_LENGTH];
	getCurrentNote(notePath, noteName);

	if (access(notePath, F_OK) == -1) {
		printf("Hmmm. The current note (%s) doesn't seem to exist. How did we get here?\n", noteName);
		return;
	}	

	// get the number of lines in the file 
	int numLines = getFileSize(notePath);
	if (numLines == 0) {
		printf("You have no memories on this note\n");
		return;
	}
	printf("\033[1m\033[3mFound %d memories on '%s'\033[0m\n", numLines, noteName);

	FILE* toRead;
	toRead = fopen(notePath, "r");
	int counter = 1;
	char memory[MAX_LENGTH];

	while (fgets(memory, sizeof(memory), toRead)) {
		printf("\033[1m%d.\033[0m %s", counter, memory); 
		counter++;
	}	

	fclose(toRead);
}
	
