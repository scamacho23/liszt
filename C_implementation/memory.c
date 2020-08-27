#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "memory.h"
#include "helper_func.h"
#include "note.h"
// #include "../../json-c/json_object.h"

void appendMemory(char* memory, char* note) {
	FILE *toWrite;
	toWrite = fopen(note, "a");
	fprintf(toWrite, "%s\n", memory);
	fclose(toWrite);
}


int changeMemory(char* charRow, char* memory) {
	char currentNoteName[256];
	char currentNotePath[256];
	getCurrentNote(currentNotePath, currentNoteName);
	int result = checkRow(currentNotePath, charRow);
	if (result == -1) return -1;
	
	int row = atoi(charRow);
	
	FILE* source;
	source = fopen(currentNotePath, "r");

	FILE* target;
	char dirName[] = "background";
	char noteName[] = "BRIEF";
	char notePath[256];
	getNotePath(dirName, noteName, notePath);
	target = fopen(notePath, "w");

	char temp[256];
	char line[256];
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
	char note[256];
	parseSpecialArgs(note, args, numArgs);
	
	char dirName[] = "notes";
	char notePath[256];
	getNotePath(dirName, note, notePath);
	
	struct stat st = {0};
	if (stat(notePath, &st) == -1) {
		printf("The note you are trying to add to does not exist. Please try again.\n");
		return;
	}
	int result = checkDefault(note);
	if (result == -1) return;

	char memoryToMove[256];
	result = changeMemory(args[2], memoryToMove);
	if (result == -1) return;

	appendMemory(memoryToMove, notePath);
	printf("Moved '%s' to '%s'\n", memoryToMove, note);
}


void copyMemory(char* args[], int numArgs) {
	char note[256];
	parseSpecialArgs(note, args, numArgs);

	char currentNoteName[256];
	char currentNotePath[256];
	getCurrentNote(currentNotePath, currentNoteName);

	char dirName[] = "notes";
	char notePath[256];
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
	
	char line[256];
	char temp[256];
	while (fgets(line, sizeof(line), source)) {
		if (counter + 1 == row) {
			strcpy(temp, line);
			counter++;
			continue;
		}
		counter++;
	}

	fclose(source);

	char memoryToCopy[256];

	// the following is slightly odd but seems to work	
	int sizeMemory = strlen(temp);
	strncpy(memoryToCopy, temp, sizeMemory - 1);
	memoryToCopy[sizeMemory - 1] = '\0';	

	appendMemory(memoryToCopy, notePath);
	printf("Copied '%s' to '%s'\n", memoryToCopy, note);
}


void removeMemory(char* row) {
	char memoryToRemove[256];
	int result = changeMemory(row, memoryToRemove);
	if (result == -1) return;

	printf("Removed memory '%s'\n", memoryToRemove);
}


void clearMemories() {
	char currentNotePath[256];
	char note[256];
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
	char note[256];
	char currentNotePath[256];
	getCurrentNote(note, currentNotePath);
	char sansFirstWord[256];
	int result = parseUnaryArgs(sansFirstWord, args, numArgs);
	if (result == 1) {
		appendMemory(args[1], note);
		printf("Remembered '%s'\n", args[1]);
	} else {
		char memory[256];
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
	char notePath[256];
	char noteName[256];
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
	char memory[256];

	while (fgets(memory, sizeof(memory), toRead)) {
		printf("\033[1m%d.\033[0m %s", counter, memory); 
		counter++;
	}	

	fclose(toRead);
}
	
