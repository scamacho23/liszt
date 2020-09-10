#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <wordexp.h>
#include "helper.h"
#include "install.h"
#include "cJSON.h"

#define MAX_LENGTH 256

/*
 * TO DO
 * readDirectory() --- requires array completion
 */


void sendErrorMessage(char* command) {
	printf("lst error: command '%s' not recognized. Please try again.\n", command);	
	printf("(hint: did you include the necessary arguments for this command? Run 'lst -h' to find out)\n");
	exit(1);
}


void checkInstallation() {
	struct stat st = {0};
	wordexp_t liszt;
	wordexp("~/.liszt", &liszt, 0);
	char* lisztPath = liszt.we_wordv[0];
	if (stat(liszt.we_wordv[0], &st) == -1) {
		// if ~/.liszt does not exist (e.g. user deleted it), create a new one
		int installation = install();
		// if installation fails again, hard quit
		if (installation == -1) {
			exit(1);
		}
	}
	wordfree(&liszt);
}


void printCurrentNoteName() {
	char currentNoteName[MAX_LENGTH];
	getCurrentNoteName(currentNoteName);
	printf("%s\n", currentNoteName);
}


void getCurrentNoteName(char* currentNoteName) {
	char currentNotePath[MAX_LENGTH];
	getCurrentNote(currentNotePath, currentNoteName);
}


void getCurrentNote(char* currentNotePath, char* currentNoteName) {
	getCurrentNotePath(currentNotePath);
	char slash = '/';
	char* lastSlash = strrchr(currentNotePath, slash);
	strcpy(currentNoteName, lastSlash + 1);
}	

void getCurrentNotePath(char* currentNotePath) {
	char dataFile[MAX_LENGTH];
	getDataFile(dataFile);

	FILE* toRead;
	toRead = fopen(dataFile, "r");
	char line[MAX_LENGTH];
	char dataStream[MAX_LENGTH];

	fgets(line, sizeof(line), toRead);
	strcpy(dataStream, line);
	while (fgets(line, sizeof(line), toRead)) {
		strcat(dataStream, line);
	}	
	fclose(toRead);

	cJSON* data = cJSON_Parse(dataStream);
	cJSON* currentNote = cJSON_GetObjectItem(data, "current_note");
	char* temp = cJSON_PrintUnformatted(currentNote);
	temp++;
	temp[strlen(temp) - 1] = '\0';
	strcpy(currentNotePath, temp);
	cJSON_Delete(data);
}


void getNotePath(char* dirName, char* noteName, char* notePath) {
	char* tilde = "~";	
	wordexp_t newNote;
	// expand tilde bc that is user specific
	wordexp(tilde, &newNote, 0);
	
	strcpy(notePath, newNote.we_wordv[0]);
	strcat(notePath, "/.liszt/");
	strcat(notePath, dirName);
	strcat(notePath, "/");
	strcat(notePath, noteName);

	wordfree(&newNote);	
}


void setToDefault() {
	wordexp_t defaultPath;
	wordexp("~/.liszt/main/default", &defaultPath, 0);
	writeFilenameToDataFile(defaultPath.we_wordv[0]);
	wordfree(&defaultPath);
}


void getDataFile(char* dataFile) {
	char* dirName = "background";
	char* data = "data_file.json";
	getNotePath(dirName, data, dataFile);
}


void copyFile(char* firstFile, char* secondFile) {
	FILE* source, * target;
	source = fopen(firstFile, "r");
	target = fopen(secondFile, "w");
	char filechar;
	while ((filechar = fgetc(source)) != EOF) {
		fputc(filechar, target);
	}
	fclose(source);
	fclose(target);
}


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


int checkDefault(char* note) {
	char loweredNote[MAX_LENGTH];
	strcpy(loweredNote, note);
	int numChars = strlen(loweredNote);
	for (int i = 0; i < numChars; i++) {
		loweredNote[i] = tolower(loweredNote[i]);
	}
	if (strcmp(loweredNote, "default") == 0) {
		printf("Sorry. 'default' is off limits.\n");
		return -1;
	}
	return 0;
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
		if (strcmp(shortName, " ") == 0) counter--; // decrement counter bc don't want to include default in the count
		if (!counter) {
			printf("You have no%snotes at the moment.\n", shortName);
			return;
		}
		printf("\033[1mFound %d%snotes\033[0m\n", counter, shortName);
		rewinddir(directory);
		int index = 1;
		while ((dir = readdir(directory)) != NULL) {
			if (dir->d_type == DT_REG && strcmp(dir->d_name, "default") != 0) {
				printf("\033[1m%d.\033[0m %s\n", index, dir->d_name);
				index++;
			}
		}
		closedir(directory);
	}
}  


int checkRow(char* filename, char* charRow) {
	int row = atoi(charRow);	
 	if (row <= 0) {
         	printf("You have entered in a faulty row number. Please choose an integer value.\n");
 		printf("hint: %s was not valid!\n", charRow);
 		return -1;
 	}

	int size = getFileSize(filename);

 	if (row > size) {
 		printf("You have entered in a faulty row number.\n");
 		return -1;
 	}

 	return 0;
}


void writeFilenameToDataFile(char* filename) {
	// get path to data_file.json
	char dataFile[MAX_LENGTH];
	getDataFile(dataFile);

	// open data_file and read contents into dataStream
	// should be decomposed
	FILE* toRead;
	toRead = fopen(dataFile, "r");
	char line[MAX_LENGTH];
	char dataStream[MAX_LENGTH];

	fgets(line, sizeof(line), toRead);
	strcpy(dataStream, line);
	while (fgets(line, sizeof(line), toRead)) {
		strcat(dataStream, line);
	}	
	fclose(toRead);

	// move dataStream into data as a true JSON object
	cJSON* data = cJSON_Parse(dataStream);

	// replace the existing current note with the given one
	cJSON* file = cJSON_CreateString(filename);
	cJSON_ReplaceItemInObjectCaseSensitive(data, "current_note", file);

	char* newStream = cJSON_Print(data);

	FILE* toWrite;
	toWrite = fopen(dataFile, "w");
	fprintf(toWrite, "%s", newStream);
	fclose(toWrite);

	cJSON_Delete(data);

}


void requestUserPermission(char* prompt, char* decision) {
	// do this once outside of the loop so that decision has a value pre-strcmp
	printf("%s", prompt);
	scanf("%99s", decision);
	while (strcmp(decision, "y") != 0 && strcmp(decision, "n") != 0) {
		printf("%s", prompt);
		scanf("%99s", decision);
	}
}
	

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


int makeNote(char* filePath) {
	if (access(filePath, F_OK) != -1) {
		printf("A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.\n");
		return -1;
	}
	FILE* toCreate;
	toCreate = fopen(filePath, "w");
	fclose(toCreate);
	return 0;
}

