#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "helper_func.h"

/*
 * TO DO:
 * readDirectory() --- requires array completion
 * checkRow() --- requires array completion
 * writeToDataFile() --- requires JSON completion 
 */


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


void printDefaultError() {
	printf("Sorry. 'default' is off limits.\n");
}


void readDirectory(char* dirName, char* files[], int* numFiles) {
	DIR* directory;
	struct dirent* dir;
	directory = opendir(dirName);
	if (directory) {
		while ((dir = readdir(directory)) != NULL) {
			char* filename = dir->d_name;
			if (dir->d_type == DT_REG) {
				files[*numFiles] = filename;	
				(*numFiles)++;
			}
		}
		closedir(directory);
	}
}


void printDirectory(char* dirName, char* shortName) {
	DIR* directory;
	struct dirent* dir;
	directory = opendir(dirName);
	if (directory) {
		int counter = 0; // for counting the number of files
		while ((dir = readdir(directory)) != NULL) {
			if (dir->d_type == DT_REG) {
				counter++;
			}
		}
		if (!counter) {
			printf("You have no notes at the moment.\n");
			return;
		}
		printf("\033[1mFound %d%snotes\033[0m\n", counter, shortName);
		rewinddir(directory);
		int index = 1;
		while ((dir = readdir(directory)) != NULL) {
			if (dir->d_type == DT_REG) {
				printf("\033[1m%d.\033[0m %s\n", index, dir->d_name);
				index++;
			}
		}
		closedir(directory);
	}
}  


// int checkRow(char* filename, char* charRow, char*** memories, int* numMemories) {
// 	int row = atoi(charRow);	
// 	if (row <= 0) {
//         	printf("You have entered in a faulty row number. Please choose an integer value.\n");
// 		printf("hint: %s was not valid!\n", charRow);
// 		return 0;
// 	}

// 	FILE* toRead = fopen(filename, "r");
// 	int i = 0;
// 	while (fgets(&memories[i], sizeof(memories[i]), toRead)) {
// 		printf("Size of Memory: %lu\n", sizeof(memories[i]));
// 		i++;
// 	}
// 	*numMemories = i;
// 	if (row > *numMemories) {
// 		printf("You have entered in a faulty row number.\n");
// 		return 0;
// 	}
// 	fclose(toRead);
	
// 	for (int i = 0; i < *numMemories; i++) {
// 		printf("%s\n", memories[i]);
// 	}

// 	return 1;
// }

void writeToDataFile(char* dataFile, char* filename) {
	// The below is a stand-in until json-c has been figured out
	FILE* toWrite;
	toWrite = fopen(dataFile, "w");
	fprintf(toWrite, "%s", filename);
	fclose(toWrite);
}


void requestUserPermission(char* prompt, char* decision) {
	while (strcmp(decision, "y") != 0 && strcmp(decision, "n") != 0) {
		printf("%s", prompt);
		scanf("%s", decision);
	}
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
	if (numArgs >= 4) strcat(first, " ");
	if (strcmp(args[2], "/") == 0) {
		printf("You have not entered enough information. Please try again.\n");
		return -1;
	}
	int counter = 3;
	while (counter < numArgs && strcmp(args[counter], "/") != 0) {
		strcat(first, args[counter]);	
		if (numArgs > counter + 1) strcat(first, " ");
		counter++;
	} 
	if (counter == numArgs) {
		printf("You have not entered enough infomration. Please try again.\n");
		return -1;
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


int makeNote(char* filePath) {
	if (access(filePath, F_OK) != -1) {
		printf("A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.");
		return -1;
	}
	FILE* toCreate;
	toCreate = fopen(filePath, "w");
	fclose(toCreate);
	return 0;
}

