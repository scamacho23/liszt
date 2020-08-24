#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "memory.h"
#include "helper_func.h"
// #include "../../json-c/json_object.h"

/*
 * TO DO
 * changeMemory()
 * moveMemory()
 * 
 */


void appendMemory(char* memory, char* note) {
	FILE *toWrite;
	toWrite = fopen(note, "a");
	fprintf(toWrite, "%s\n", memory);
	fclose(toWrite);
}


char* changeMemory(char* currentNote, char* row) {
	return currentNote;	
}


void moveMemory(char* currentNote, char* row, char args[]);


void copyMemory(char* currentNote, char* row, char args[]);


void removeMemory(char* note, char* row);


void clearMemories(char* note) {
	char prompt[] = "Are you sure you want to clear your memories on your current note? \033[1mThere is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		FILE* toClear;
		toClear = fopen(note, "w");
		fclose(toClear);
		printf("Memories cleared\n");
	} else printf("Memory clearing aborted\n");	
}


void addMemory(char* note, char* args[], int numArgs) {
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


void listMemories(char* notePath, char* noteName) {
	if (access(notePath, F_OK) == -1) {
		printf("Hmmm. The current note (%s) doesn't seem to be working. Please try again later.\n", noteName);
		printf("If the current note continues to fail to open, please submit a help ticket by emailing us at quicknote.v1@gmail.com\n");
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
	
