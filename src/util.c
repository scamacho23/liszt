#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <wordexp.h>
#include "util.h"
#include "install.h"
#include "cJSON.h"

#define MAX_LENGTH 256
#define FAIL 1


void sendErrorMessage(char *command) {
	printf("lst: command '%s' not recognized. Please try again. Run 'lst -h' to confirm that you included all necessary arguments.\n", command);
	exit(FAIL);
}


void checkInstallation() {
	struct stat st = {0};
	wordexp_t liszt;
	wordexp("~/.liszt", &liszt, 0);
	char *lisztPath = liszt.we_wordv[0];
	if (stat(liszt.we_wordv[0], &st) == -1) {
		// if ~/.liszt does not exist (e.g. user deleted it), create a new one
		int installation = install();
		// if installation fails again, hard quit
		if (installation == -1) {
			exit(FAIL);
		}
	}
	wordfree(&liszt);
}


void printCurrentNoteName() {
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);
	printf("%s\n", current_note_name);
	free(current_note_name);
	free(current_note_path);
}


char *getCurrentNote(char **current_note_path) {
	*current_note_path = getCurrentNotePath();
	char slash = '/';
	char *current_note_name = malloc(MAX_LENGTH * sizeof(char));
	if (*current_note_path != NULL && *current_note_path[0] != '\0') {
		strcpy(current_note_name, strrchr(*current_note_path, '/') + 1);
	}
	return current_note_name;
}	


char *getCurrentNotePath() {
	char *current_note_path = calloc(1, sizeof(char));
	char *data_file = getDataFile();

	FILE *to_read;
	to_read = fopen(data_file, "r");

	if (to_read) {
		//char dataStream[MAX_LENGTH];

		//fgets(line, sizeof(line), toRead);
		//strcpy(dataStream, line);
		char line[MAX_LENGTH];
		char *res = fgets(line, MAX_LENGTH * sizeof(char), to_read);
		if (res != NULL) {
			free(current_note_path);
			current_note_path = strdup(res);
			/*
			while (fgets(line, MAX_LENGTH * sizeof(char), toRead)) {
				strcat(dataStream, line);
			}
			fclose(toRead);

			cJSON *data = cJSON_Parse(dataStream);
			cJSON *currentNote = cJSON_GetObjectItem(data, "current_note");
			char *current_note_path = cJSON_PrintUnformatted(currentNote);
			*/
			current_note_path[strlen(current_note_path)] = '\0'; // to get rid of the newline
			//cJSON_Delete(data);
		}
	}
	free(data_file);
	fclose(to_read);
	return current_note_path;
}


char *getNotePath(char *dirName, char *noteName) {
	char *tilde = "~";	
	wordexp_t newNote;
	// expand tilde bc that is user specific
	wordexp(tilde, &newNote, 0);

	char *note_path = malloc(PATH_MAX * sizeof(char));
	strcpy(note_path, newNote.we_wordv[0]);
	strcat(note_path, "/.liszt/");
	strcat(note_path, dirName);
	strcat(note_path, "/");
	strcat(note_path, noteName);

	wordfree(&newNote);	
	return note_path;
}


void setToDefault() {
	wordexp_t defaultPath;
	wordexp("~/.liszt/main/default", &defaultPath, 0);
	writeFilenameToDataFile(defaultPath.we_wordv[0]);
	wordfree(&defaultPath);
}


char *getDataFile() {
	return getNotePath("background", "data_file");
}


void copyFile(char *first_file, char *second_file) {
	FILE *source, *target;
	source = fopen(first_file, "r");
	target = fopen(second_file, "w");
	char line[MAX_LENGTH];
	while (fgets(line, MAX_LENGTH * sizeof(char), source) != NULL) {
		fprintf(target, "%s", line);
	}
	fclose(source);
	fclose(target);
}


int getFileSize(char *filename) {
	FILE *toRead;
	char line[MAX_LENGTH];
	int num_lines = 0;
	toRead = fopen(filename, "r");
	while (fgets(line, MAX_LENGTH * sizeof(char), toRead) != NULL) {
		num_lines++;
	}
	fclose(toRead);
	return num_lines;
}


int checkDefault(char *note) {
	char lowered_note[strlen(note) + 1];
	strcpy(lowered_note, note);
	size_t num_chars = strlen(lowered_note);
	for (int i = 0; i < num_chars; i++) {
		lowered_note[i] = tolower(lowered_note[i]);
	}
	if (!strcmp(lowered_note, "default")) {
		printf("Sorry. 'default' is off limits.\n");
		return -1;
	}
	return 0;
}


int filter_entries(const struct dirent *entry) {
	const char *name = entry->d_name;
	if (strspn(name, ".")) {
		return 0;	
	}
	if (!strcmp(name, "default")) {
		return 0;
	}
	return 1;
}


void printDirectory(char *dirName, char *shortName) {
	struct dirent **entries;
	int numEntries = scandir(dirName, &entries, filter_entries, NULL);
	if (numEntries < 0) {
		printf("\033[1mLiszt\033[0m wasn\'t able to complete your request at this time.\n");
		printf("Please try again later.\n");
		return;
	}
	if (!numEntries) {
		printf("You have no%snotes at the moment.\n", shortName);
		return;	
	}
	printf("\033[1mFound %d%snotes\033[0m\n", numEntries, shortName);
	for (int i = 0; i < numEntries; i++) {
		struct dirent* entry = entries[i];
		printf("\033[1m%d.\033[0m %s\n", i + 1, entry->d_name);
		free(entry);
	}
	free(entries);
}  


long checkRow(char *filename, char *char_row) {
	long row = strtol(char_row, NULL, 10);
 	if (row <= 0) {
         	printf("You have entered in a faulty row number. Please choose an integer value.\n");
 		printf("hint: %s was not valid!\n", char_row);
 		return -1;
 	}

	int size = getFileSize(filename);

 	if (row > size) {
 		printf("You have entered in a faulty row number.\n");
 		return -1;
 	}

 	return row;
}

// the following this screwed up (intentionally)
// needs to be fixed for the purpose of adding collections
void overwriteFilenameToDataFile(char *filename, char *dirname) {
	// get path to data_file.json
	char *data_file = getDataFile();

	//cJSON *data = cJSON_CreateObject();
	//cJSON *note = cJSON_CreateString(filename);
	//cJSON_AddItemToObject(data, "current_note", note);

	//cJSON *collection = cJSON_CreateString(dirname);
	//cJSON_AddItemToObject(data, "current_collection", collection);
	
	//char *stringJSON = cJSON_Print(data);

	FILE *toWrite;
	toWrite = fopen(data_file, "w");
	fprintf(toWrite, "%s", filename);
	fclose(toWrite);

	//cJSON_Delete(data);
	free(data_file);

}


void writeFilenameToDataFile(char *filename) {
	// get path to data_file.json
	char *data_file = getDataFile();

	// open data_file and read contents into dataStream
	// should be decomposed
/*
	FILE *toRead;
	toRead = fopen(data_file, "r");
	char line[MAX_LENGTH];
	char dataStream[MAX_LENGTH];

	fgets(line, sizeof(line), toRead);
	strcpy(dataStream, line);
	while (fgets(line, sizeof(line), toRead)) {
		strcat(dataStream, line);
	}	
	fclose(toRead);

	// move dataStream into data as a true JSON object
	cJSON *data = cJSON_Parse(dataStream);

	// replace the existing current note with the given one
	cJSON *file = cJSON_CreateString(filename);
	cJSON_ReplaceItemInObjectCaseSensitive(data, "current_note", file);

	char *newStream = cJSON_Print(data);
*/

	FILE *toWrite;
	toWrite = fopen(data_file, "w");
	fprintf(toWrite, "%s", filename);
	fclose(toWrite);

//	cJSON_Delete(data);
	free(data_file);
}


void requestUserPermission(char *prompt, char *decision) {
	// do this once outside of the loop so that decision has a value pre-strcmp
	printf("%s", prompt);
	// set to 49 to match allocation to decision[50]
	scanf("%49s", decision);
	while (strcmp(decision, "y") != 0 && strcmp(decision, "n") != 0) {
		printf("%s", prompt);
		scanf("%49s", decision);
	}
}
	

char *parseSpecialArgs(char *args[], int numArgs) {
	char *filename = malloc(MAX_LENGTH * sizeof(char));
	// start at 2 to avoid program invocation, command, and row (argv[0], argv[1], and argv[2])
	if (numArgs >= 4) strcpy(filename, args[3]);
	if (numArgs > 5) strcat(filename, " ");
	for (int i = 4; i < numArgs; i++) {
		strcat(filename, args[i]);	
		if (numArgs > i + 1) strcat(filename, " ");
	}
	return filename;
}


char *parseUnaryArgs(char *args[], int numArgs) {
	if (numArgs == 2) {
		return NULL; // just exit if it's a single word
	}
	char *word = malloc(MAX_LENGTH * sizeof(char));
	// start at 2 to avoid program invocation and command (argv[0] and argv[1])
	if (numArgs > 2) strcpy(word, args[2]);
	if (numArgs >= 4) strcat(word, " ");
	for (int i = 3; i < numArgs; i++) {
		strcat(word, args[i]);	
		if (numArgs > i + 1) strcat(word, " ");
	}
	return word;
}


int parseBinaryArgs(pair_t *notes, char *args[], int numArgs) {
	char first[MAX_LENGTH];
	char second[MAX_LENGTH];
	// NEW IMPLEMENTATION
	// start at 2 to avoid program invocation and command (argv[0] and argv[1])
	/*
	char *temp = " ";
	for (int i = 2; i < numArgs; i++) {
		strcat
			
	}
	*/

	// OLD IMPLEMENTATION
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
	notes->first = strdup(first);
	notes->second = strdup(first);
	return 0;
}


int makeNote(char *filePath) {
	if (access(filePath, F_OK) != -1) {
		printf("A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.\n");
		return -1;
	}
	FILE *toCreate = fopen(filePath, "w");
	fclose(toCreate);
	return 0;
}

