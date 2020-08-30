#include <stdio.h>
#include <wordexp.h>
#include <sys/stat.h>
// The below are Liszt files
#include "install.h"
#include "helper.h"


/* ADD MORE DETAIL TO THIS FILE (ALSO MAYBE CHANGE NAME TO CONFIGURE)
 * AS IN, WHEN this is installing just have it write more stuff to console
 * so people know what is happening. Also, maybe this file should be called
 * configure? And maybe there should be a configure command? And maybe people
 * should get to configure Liszt a little bit to what they like (like change
 * display colors or something)
 *
 * also maybe just one wordexp_t instead of freeing each time
 */


int makeDirectories() {
	struct stat st = {0};
	
	// Make root .liszt directory
	wordexp_t liszt;
	wordexp("~/.liszt", &liszt, 0);
	char* lisztPath = liszt.we_wordv[0];
	mkdir(lisztPath, 0777);	
	if (stat(lisztPath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", lisztPath);
		printf("Please try again later.\n");
		return -1;	
	}
	wordfree(&liszt);
	
	// Make background directory
	wordexp_t background;
	wordexp("~/.liszt/background", &background, 0);
	char* backgroundPath = background.we_wordv[0];
	mkdir(backgroundPath, 0777);
	if (stat(backgroundPath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", backgroundPath);
		printf("Please try again later.\n");
		return -1;	
	}
	wordfree(&background);

	// Make notes directory
	wordexp_t notes;
	wordexp("~/.liszt/notes", &notes, 0);
	char* notesPath = notes.we_wordv[0];
	mkdir(notesPath, 0777);
	if (stat(notesPath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", notesPath);
		printf("Please try again later.\n");
		return -1;	
	}
	wordfree(&notes);

	// Make archive_notes directory
	wordexp_t archiveNotes;
	wordexp("~/.liszt/archive", &archiveNotes, 0);
	char* archiveNotesPath = archiveNotes.we_wordv[0];
	mkdir(archiveNotesPath, 0777);
	if (stat(archiveNotesPath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", archiveNotesPath);
		printf("Please try again later.\n");
		return -1;	
	}
	wordfree(&archiveNotes);
	
	return 0;
}


int makeFiles() {
	FILE* toCreate;
	struct stat st = {0};

	// Make data_file.json
	wordexp_t dataFile;
	wordexp("~/.liszt/background/data_file.json", &dataFile, 0);
	char* dataFilePath = dataFile.we_wordv[0];
	toCreate = fopen(dataFilePath, "w");
	fclose(toCreate);
	if (stat(dataFilePath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", dataFilePath);
		printf("Please try again later.\n");
		return -1;	
	}

	// Make default file
	wordexp_t defaultFile;
	wordexp("~/.liszt/notes/default", &defaultFile, 0);
	char* defaultFilePath = defaultFile.we_wordv[0];
	toCreate = fopen(defaultFilePath, "w");
	fclose(toCreate);
	if (stat(defaultFilePath, &st) == -1) {
		printf("\033[1mLiszt\033[0m installation unsuccessful. Failed to install '%s'\n", defaultFilePath);
		printf("Please try again later.\n");
		return -1;	
	}

	writeToDataFile(defaultFilePath);

	wordfree(&dataFile);
	wordfree(&defaultFile);
	
	return 0;
}	


int install() {
	int makeDir = makeDirectories();	
	int makeFile = makeFiles();
	if (makeDir == -1 || makeFile == -1) {
		return -1;
	}
	printf("\033[1m\033[3mLiszt\033[0m \033[3minstallation successful.\033[0m\n");
	return 0;
}	
