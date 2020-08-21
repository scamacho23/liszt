#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "memory.h"
#include "helper_func.h"


int getFileSize(char* filename) {
	FILE* toRead;
	char newline;
	int numLines = 0;
	toRead = fopen(filename, "r");
	while ((newline = fgetc(toRead)) != EOF) {
		if (newline == '\n') numLines++;
	}
	fclose(toRead);
	return numLines;
}


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


void clearMemories(char* note);


void addMemory(char* note, char args[]);


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
	
		

