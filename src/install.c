#include <stdio.h>
#include <wordexp.h>
#include <sys/stat.h>
// The below are Liszt files
#include "install.h"
#include "helper.h"

#define MAX_LENGTH 256


/* TODO: ADD MORE DETAIL TO THIS FILE 
 * AS IN, WHEN this is installing just have it write more stuff to console
 * so people know what is happening. Also, maybe this file should be called
 * configure? And maybe there should be a configure command? And maybe people
 * should get to configure Liszt a little bit to what they like (like change
 * display colors or something)
 */


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


int makeFiles() {
	FILE* toCreate;
	struct stat st = {0};
	wordexp_t liszt;
	char* tilde = "~";
	wordexp(tilde, &liszt, 0);
	tilde = liszt.we_wordv[0];

	// Make data_file.json
	char dataFilePath[MAX_LENGTH];
	strcpy(dataFilePath, tilde);
	strcat(dataFilePath, "/.liszt/background/data_file.json");
	toCreate = fopen(dataFilePath, "w");
	fclose(toCreate);
	if (stat(dataFilePath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", dataFilePath);
		printf("Please try again later.\n");
		return -1;	
	} else printf("Created ~/.liszt/background/data_file.json file\n");

	// Make default file
	char defaultFilePath[MAX_LENGTH];
	strcpy(defaultFilePath, tilde);
	strcat(defaultFilePath, "/.liszt/main/default");
	toCreate = fopen(defaultFilePath, "w");
	fclose(toCreate);
	if (stat(defaultFilePath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", defaultFilePath);
		printf("Please try again later.\n");
		return -1;	
	} else printf("Created ~/.liszt/main/default file\n");

	char defaultCollectionPath[MAX_LENGTH];
	strcpy(defaultCollectionPath, tilde);
	strcat(defaultCollectionPath, "/.liszt/main");	
	overwriteFilenameToDataFile(defaultFilePath, defaultCollectionPath);

	wordfree(&liszt);
	
	return 0;
}	


int makeDir(char* tilde, char* dirname) {
	struct stat st = {0};
	char path[MAX_LENGTH];
	strcpy(path, tilde);
	strcat(path, dirname);
	mkdir(path, 0777);	
	if (stat(path, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", path);
		printf("Please try again later.\n");
		return -1;	
	} else printf("Created %s directory\n", path);
	return 0;
}


int makeDirectories() {
	wordexp_t liszt;
	char* tilde = "~";
	wordexp(tilde, &liszt, 0);
	tilde = liszt.we_wordv[0];
	
	// Make root .liszt directory
	char* dirname = "/.liszt";
	int result = makeDir(tilde, dirname);
	if (result == -1) return -1;
	
	// Make background directory
	dirname = "/.liszt/background";
	result = makeDir(tilde, dirname);
	if (result == -1) return -1;

	// Make main directory
	dirname = "/.liszt/main";
	result = makeDir(tilde, dirname);
	if (result == -1) return -1;

	// Make archive directory
	dirname = "/.liszt/archive";
	result = makeDir(tilde, dirname);
	if (result == -1) return -1;


	result = makeFiles();
	if (result == -1) return -1;
	wordfree(&liszt);	
	return 0;
}


int install() {
	int makeDir = makeDirectories();	
	if (makeDir == -1) {
		return -1;
	}
	return 0;
}	

