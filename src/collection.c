#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <wordexp.h>
#include <sys/stat.h>
#include "helper.h"
#include "collection.h"

#define MAX_LENGTH 256

void listCollections() {
	DIR* directory;
	struct dirent* dir;

	wordexp_t dirPath;
	char path[] = "~/.liszt";
	wordexp(path, &dirPath, 0);
		
	directory = opendir(dirPath.we_wordv[0]);
	if (directory) {
		int counter = 0; // for counting the number of collections
		while ((dir = readdir(directory)) != NULL) {
			if (dir->d_type == DT_DIR) {
				counter++;
			}
		}
		counter -= 4; // decrement counter bc don't want to include 'archive', 'background', '.', and '..' in the count
		if (counter == 1) {
			printf("\033[1mFound 1 collection\033[0m\n");
		} else printf("\033[1mFound %d collections\033[0m\n", counter);
		rewinddir(directory);

		while ((dir = readdir(directory)) != NULL) {
			char* dirName = dir->d_name;
			if (strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0) continue;
			if (strcmp(dirName, "archive") == 0 || strcmp(dirName, "background") == 0) continue;
			if (dir->d_type == DT_DIR) {
				printf("%s\n", dirName);
			}
		}
		closedir(directory);
	}

	wordfree(&dirPath);
}


void addCollection(char* args[], int numArgs) {
	char collection[MAX_LENGTH];
	char collectionPath[MAX_LENGTH];
	parseUnaryArgs(collection, args, numArgs);
	
	// stop the user from trying to name a collection 'main', 'archive', or 'background'	
	char* offLimits = "main";
	int result = checkSame(collection, offLimits);
	if (result == -1) return;

	offLimits = "archive";
	result = checkSame(collection, offLimits);
	if (result == -1) return;

	offLimits = "background";
	result = checkSame(collection, offLimits);
	if (result == -1) return;

	// the following should be decomposed
	char* tilde = "~";
	wordexp_t newCollection;
	wordexp(tilde, &newCollection, 0);
	strcpy(collectionPath, tilde);
	strcat(collectionPath, "/.liszt/");
	strcat(collectionPath, collection);

	// confirm that a collection does not already exist with this name
	struct stat st = {0};
	if (stat(collectionPath, &st) == 0) {
		printf("You already have a collection with this name.\n");
		return;
	}
	// TODO: mkdir exiting with -1 and not making a dir
	result = mkdir(collectionPath, 0777);
	printf("%s\n", collectionPath);
	printf("%d\n", result);
	// change to this collection when changeCollection is added
	printf("Added new collection '%s'\n", collection);

	wordfree(&newCollection);
}


void changeCollection(char* args[], int numArgs);


void removeCollection(char* args[], int numArgs);


void renameCollection(char* args[], int numArgs);


void clearCollections();


void importCollection(char* args[], int numArgs);


void exportCollection(char* args[], int numArgs);


void compressCollection(char* args[], int numArgs);

