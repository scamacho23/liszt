#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "thought.h"
#include "helper.h"
// #include "../../json-c/json_object.h"

#define MAX_LENGTH 256

void appendThought(char* thought, char* note) {
	FILE *toWrite;
	toWrite = fopen(note, "a");
	fprintf(toWrite, "%s\n", thought);
	fclose(toWrite);
}


int changeThought(char* charRow, char* thought) {
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
	int sizeThought = strlen(temp);
	strncpy(thought, temp, sizeThought - 1);
	thought[sizeThought - 1] = '\0';	

	fclose(source);
	fclose(target);

	remove(currentNotePath);
	rename(notePath, currentNotePath);

	//writeToNote(currentNotePath, lines, counter);
	return 0;	
	
}


void moveThought(char* args[], int numArgs) {
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

	char thoughtToMove[MAX_LENGTH];
	result = changeThought(args[2], thoughtToMove);
	if (result == -1) return;

	appendThought(thoughtToMove, notePath);
	printf("Moved '%s' to '%s'\n", thoughtToMove, note);
}


void copyThought(char* args[], int numArgs) {
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

	char thoughtToCopy[MAX_LENGTH];

	// the following is slightly odd but seems to work	
	int sizeThought = strlen(temp);
	strncpy(thoughtToCopy, temp, sizeThought - 1);
	thoughtToCopy[sizeThought - 1] = '\0';	

	appendThought(thoughtToCopy, notePath);
	printf("Copied '%s' to '%s'\n", thoughtToCopy, note);
}


void removeThought(char* row) {
	char thoughtToRemove[MAX_LENGTH];
	int result = changeThought(row, thoughtToRemove);
	if (result == -1) return;

	printf("Removed thought '%s'\n", thoughtToRemove);
}


void clearThoughts() {
	char currentNotePath[MAX_LENGTH];
	char note[MAX_LENGTH];
	getCurrentNote(currentNotePath, note);

	char prompt[] = "Are you sure you want to clear your thoughts on your current note? \033[1mThere is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		fclose(fopen(currentNotePath, "w"));
		printf("Thoughts cleared\n");
	} else printf("Thought clearing aborted\n");	
}


void addThought(char* args[], int numArgs) {
	char note[MAX_LENGTH];
	char currentNotePath[MAX_LENGTH];
	getCurrentNote(note, currentNotePath);
	char sansFirstWord[MAX_LENGTH];
	int result = parseUnaryArgs(sansFirstWord, args, numArgs);
	if (result == 1) {
		appendThought(args[1], note);
		printf("Remembered '%s'\n", args[1]);
	} else {
		char thought[MAX_LENGTH];
		// The following is because the program considers the first word after program call to be the 'command'
		// This word must be added back
		strcpy(thought, args[1]);
		strcat(thought, " ");
		strcat(thought, sansFirstWord);

		appendThought(thought, note);
		printf("Remembered '%s'\n", thought);
	}
}


void listThoughts() {
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
		printf("You have no thoughts on this note\n");
		return;
	}
	printf("\033[1m\033[3mFound %d thoughts on '%s'\033[0m\n", numLines, noteName);

	FILE* toRead;
	toRead = fopen(notePath, "r");
	int counter = 1;
	char thought[MAX_LENGTH];

	while (fgets(thought, sizeof(thought), toRead)) {
		printf("\033[1m%d.\033[0m %s", counter, thought); 
		counter++;
	}	

	fclose(toRead);
}
	
