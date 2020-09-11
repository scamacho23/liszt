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


int checkSame(char* first, char* second) {
	char lowered[MAX_LENGTH];
	strcpy(lowered, first);
	int numChars = strlen(lowered);
	for (int i = 0; i < numChars; i++) {
		lowered[i] = tolower(lowered[i]);
	}
	if (strcmp(lowered, second) == 0) {
		printf("Sorry. '%s' is off limits.\n", second);
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


void overwriteFilenameToDataFile(char* filename, char* dirname) {
	// get path to data_file.json
	char dataFile[MAX_LENGTH];
	getDataFile(dataFile);

	cJSON* data = cJSON_CreateObject();
	cJSON* note = cJSON_CreateString(filename);
	cJSON_AddItemToObject(data, "current_note", note);

	cJSON* collection = cJSON_CreateString(dirname);
	cJSON_AddItemToObject(data, "current_collection", collection);
	
	char* stringJSON = cJSON_Print(data);

	FILE* toWrite;
	toWrite = fopen(dataFile, "w");
	fprintf(toWrite, "%s", stringJSON);
	fclose(toWrite);

	cJSON_Delete(data);

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
	

