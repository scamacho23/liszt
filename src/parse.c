#include <stdio.h>
#include <string.h>
#include "parse.h"


int parseSpecialArgs(char* filename, char* args[], int numArgs) {
	// start at 2 to avoid program invocation, command, and row (argv[0], argv[1], and argv[2])
	if (numArgs >= 4) strcpy(filename, args[3]);
	if (numArgs > 5) strcat(filename, " ");
	for (int i = 4; i < numArgs; i++) {
		strcat(filename, args[i]);	
		if (numArgs > i + 1) strcat(filename, " ");
	}
	return 0;
}


int parseUnaryArgs(char* word, char* args[], int numArgs) {
	if (numArgs == 2) return 1; // just exit if it's a single word
	// start at 2 to avoid program invocation and command (argv[0] and argv[1])
	if (numArgs > 2) strcpy(word, args[2]);
	if (numArgs >= 4) strcat(word, " ");
	for (int i = 3; i < numArgs; i++) {
		strcat(word, args[i]);	
		if (numArgs > i + 1) strcat(word, " ");
	}
	return 0;
}


int parseBinaryArgs(char* first, char* second, char* args[], int numArgs) {
	// start at 2 to avoid program invocation and command (argv[0] and argv[1])
	if (numArgs > 2) strcpy(first, args[2]);
	if (numArgs >= 4 && strcmp(args[3], "/") != 0) strcat(first, " ");
	// confirm user entered a first word
	if (strcmp(args[2], "/") == 0) {
		printf("You have not entered enough information. Please try again.\n");
		return -1;
	}
	int counter = 3;
	while (counter < numArgs && strcmp(args[counter], "/") != 0) {
		strcat(first, args[counter]);	
		// trying to strip the last space from the first arg... leading to some issues with finding the file
		if (numArgs > counter + 2 && strcmp(args[counter + 1], "/") != 0) strcat(first, " ");
		counter++;
	} 
	counter++;
	if (counter >= numArgs) {
		printf("You have not entered enough information. Please try again.\n");
		return -1;
	} else strcpy(second, args[counter]);
	if (numArgs > counter + 1) strcat(second, " ");
	counter++;
	while (counter < numArgs) {
		strcat(second, args[counter]);
		if (numArgs > counter + 1) strcat(second, " ");
		counter++;
	}	
	return 0;
}

