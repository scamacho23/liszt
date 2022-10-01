#include <stdio.h>
#include <wordexp.h>
#include <sys/stat.h>
// The below are Liszt files
#include "install.h"
#include "util.h"

#define MAX_LENGTH 256


/* TODO: ADD MORE DETAIL TO THIS FILE 
 * AS IN, WHEN this is installing just have it write more stuff to console
 * so people know what is happening. Also, maybe this file should be called
 * configure? And maybe there should be a configure command? And maybe people
 * should get to configure Liszt a little bit to what they like (like change
 * display colors or something)
 */


int errorHelper(struct stat st, char pathString[]) {
	if (stat(pathString, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", pathString);
		printf("Please try again later.\n");
		return -1;	
	} else printf("Created ~/.liszt/main/default file\n");
	return 0;
}

int makeFiles() {
	FILE* toCreate;
	struct stat st = {0};
	wordexp_t liszt;
	char* tilde = "~";
	wordexp(tilde, &liszt, 0);
	tilde = liszt.we_wordv[0];

	// Make data_file.json
	char dataFilePath[MAX_LENGTH];
	str_append(dataFilePath, tilde, "/.liszt/background/data_file");
	toCreate = fopen(dataFilePath, "w");
	fclose(toCreate);
	if (errorHelper(st, dataFilePath) == -1) return -1;

	// Make default file
	char defaultFilePath[MAX_LENGTH];
	str_append(defaultFilePath, tilde, "/.liszt/main/default");
	toCreate = fopen(defaultFilePath, "w");
	fclose(toCreate);
	if (errorHelper(st, dataFilePath) == -1) return -1;

	char defaultCollectionPath[MAX_LENGTH];
	str_append(defaultCollectionPath, tilde, "/.liszt/main");	
	overwriteFilenameToDataFile(defaultFilePath, defaultCollectionPath);

	wordfree(&liszt);
	
	return 0;
}

void str_append(char* destination_str, char* str, char* appendant)
{
    strcpy(destination_str, str);
    strcat(destination_str, appendant);
}

int makeDir(char* tilde, char* dirname) {
	struct stat st = {0};
	char path[MAX_LENGTH];
	str_append(path, tilde, dirname);
	mkdir(path, 0777);	
	if (errorHelper(st, path) == -1) return -1;
	return 0;
}


int makeDirectories() {
	wordexp_t liszt;
	char* tilde = "~";
	wordexp(tilde, &liszt, 0);
	tilde = liszt.we_wordv[0];
	const char* dirnames[] = {"/.liszt", "/.liszt/background", "/.liszt/main", "/.liszt/archive"};
	
	for (int i = 0; i <= 3; i++) {
		char* dirname = dirnames[i];
		int result = makeDir(tilde, dirname);
		if (result == -1) return -1;
	};

	int result = makeFiles();
	if (result == -1) return -1;
	wordfree(&liszt);	
	return 0;
}


int install() {
	int result = makeDirectories();	
	if (result == -1) return -1;
	return 0;
}	
