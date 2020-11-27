#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "memory.h"
#include "util.h"

#define MAX_LENGTH 256

void appendMemory(char* memory, char* note) {
	FILE *toWrite;
	toWrite = fopen(note, "a");
	fprintf(toWrite, "%s\n", memory);
	fclose(toWrite);
}


int changeMemory(char* charRow, char* memory) {
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);
	long row = checkRow(current_note_path, charRow);
	if (row <= 0) return -1;
	
	FILE* source;
	source = fopen(current_note_path, "r");

	FILE* target;
	char dirName[] = "background";
	char note_name[] = "BRIEF";
	char *note_path = getNotePath(dirName, note_name);
	target = fopen(note_path, "w");

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

	remove(current_note_path);
	rename(note_path, current_note_path);

	//writeToNote(current_note_path, lines, counter);
	free(note_path);
	free(current_note_path);
	free(current_note_name);
	return 0;	
	
}


void moveMemory(char* args[], int numArgs) {
	char *note = parseSpecialArgs(args, numArgs);
	
	char dirName[] = "main";
	char *note_path = getNotePath(dirName, note);
	
	struct stat st = {0};
	if (stat(note_path, &st) == -1) {
		printf("The note you are trying to add to does not exist. Please try again.\n");
		return;
	}
	int result = checkDefault(note);
	if (result == -1) return;

	char memoryToMove[MAX_LENGTH];
	result = changeMemory(args[2], memoryToMove);
	if (result == -1) return;

	appendMemory(memoryToMove, note_path);
	printf("Moved '%s' to '%s'\n", memoryToMove, note);
	free(note_path);
	free(note);
}


void copyMemory(char* args[], int numArgs) {
	char *note = parseSpecialArgs(args, numArgs);

	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);

	char dirName[] = "main";
	char *note_path = getNotePath(dirName, note);
	
	struct stat st = {0};
	if (stat(note_path, &st) == -1) {
		printf("The note you are trying to add to does not exist. Please try again.\n");
		return;
	}
	int result = checkDefault(note);
	if (result == -1) return;

	
	long row = checkRow(current_note_path, args[2]);
	if (row == -1) return; 
	
	FILE* source = fopen(current_note_path, "r");
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

	appendMemory(memoryToCopy, note_path);
	printf("Copied '%s' to '%s'\n", memoryToCopy, note);
	free(note_path);
	free(note);
}


void removeMemory(char* row) {
	char memoryToRemove[MAX_LENGTH];
	int result = changeMemory(row, memoryToRemove);
	if (result == -1) return;

	printf("Removed memory '%s'\n", memoryToRemove);
}


void clearMemories() {
	char *current_note_path;
	char *note = getCurrentNote(&current_note_path);

	char prompt[] = "Are you sure you want to clear your memories on your current note? \033[1mThere is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (!strcmp(decision, "y")) {
		fclose(fopen(current_note_path, "w"));
		printf("Memories cleared\n");
	} else printf("Memory clearing aborted\n");	
	free(note);
	free(current_note_path);
}


void addMemory(char* args[], int numArgs) {
	char* current_note_path = getCurrentNotePath();
	char *sans_first_word = parseUnaryArgs(args, numArgs);
	if (sans_first_word == NULL) {
		appendMemory(args[1], current_note_path);
		printf("Remembered '%s'\n", args[1]);
	} else {
		char memory[MAX_LENGTH];
		// The following is because the program considers the first word after program call to be the 'command'
		// This word must be added back
		strcpy(memory, args[1]);
		strcat(memory, " ");
		strcat(memory, sans_first_word);

		appendMemory(memory, current_note_path);
		printf("Remembered '%s'\n", memory);
	}
	free(sans_first_word);
	free(current_note_path);
}


void listMemories() {
	char* note_path;
	char *note_name = getCurrentNote(&note_path);
	if (access(note_path, F_OK) == -1) {
		printf("Hmmm. The current note (%s) doesn't seem to exist. How did we get here?\n", note_name);
		return;
	}	

	// get the number of lines in the file 
	int numLines = getFileSize(note_path);
	if (numLines == 0) {
		printf("You have no memories on this note\n");
		free(note_path);
		free(note_name);
		return;
	}
	printf("\033[1m\033[3mFound %d memories on '%s'\033[0m\n", numLines, note_name);

	FILE* toRead;
	toRead = fopen(note_path, "r");
	int counter = 1;
	char memory[MAX_LENGTH];

	while (fgets(memory, sizeof(memory), toRead)) {
		printf("\033[1m%d.\033[0m %s", counter, memory); 
		counter++;
	}	

	fclose(toRead);
	free(note_path);
	free(note_name);
}
	
