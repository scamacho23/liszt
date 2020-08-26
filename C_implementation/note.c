#include <stdio.h>
#include <wordexp.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
// The below are Liszt .h files
#include "note.h"
#include "helper_func.h"


void writeToNote(char* note, char* memories[], int numMemories) {
	FILE* toWrite;
	toWrite = fopen(note, "w");
	for (int i = 0; i < numMemories; i++) {
		fprintf(toWrite, "%s", memories[i]);
	}
	fclose(toWrite);
}


void duplicateNote(char* args[]);


void importNote(char* args[], int numArgs) {
	char import[256];
	char note[256];
	int result = parseBinaryArgs(import, note, args, numArgs);
	struct stat st = {0};
	if (result == -1) {
		return;
	}
	if (stat(import, &st) == -1) {
		printf("Sorry. \033[1mLiszt\033[0m can't find the file you are trying to import\n");
		return;
	}
	char* extension = strrchr(import, '.');
	if (!extension) {
		printf("Sorry. \033[1mLiszt\033[0m can't import the type of file you are trying to import\n");
		printf("\033[1mLiszt\033[0m only understands '.txt' files at the moment.\n");
	}
	if (strcmp(extension, ".txt") != 0) {
		printf("Sorry. \033[1mLiszt\033[0m can't import the type of file you are trying to import\n");
		printf("\033[1mLiszt\033[0m only understands '.txt' files at the moment.\n");
		return;
	}
	char* tilde = "~";	
	wordexp_t newNote;
	wordexp(tilde, &newNote, 0);
	
	char fullNotePath[256];
	strcpy(fullNotePath, newNote.we_wordv[0]);
	strcat(fullNotePath, "/.liszt/notes/");
	strcat(fullNotePath, note);

	result = makeNote(fullNotePath);
	if (result == 0) {
		copyFile(import, fullNotePath);	
		printf("Successfully imported '%s' as '%s'\n", import, note);
	}
	wordfree(&newNote);	
}


void exportNote(char* args[], int numArgs) {
	char note[256];
	char export[256];
	int result = parseBinaryArgs(note, export, args, numArgs);

	if (result == -1) {
		return;
	}

	wordexp_t newFile;
	char* tilde = "~";
	wordexp(tilde, &newFile, 0);
	char notePath[256];
	strcpy(notePath, newFile.we_wordv[0]);
	strcat(notePath, "/.liszt/notes/");
	strcat(notePath, note);
	
	struct stat st = {0};
	if (stat(notePath, &st) == -1) {
		printf("Sorry. \033[1mLiszt\033[0m can't find the note you are trying to export: '%s'. Did you spell the name of the note correctly?\n", note);
		return;
	}
	if (strcmp(note, "default") == 0) {
		printDefaultError();
		return;
	}
	
	strcat(export, ".txt");

	if (stat(export, &st) == 0) {
		printf("Sorry. A file with this name already exists in the directory to which you are trying to add. Please pick a different name\n");
		return;
	}

	copyFile(notePath, export);
	printf("Successfully exported '%s' as '%s'\n", note, export);
	wordfree(&newFile);
}

void archiveNote(char* args[], char* currentNote, char* dataFile);


void unArchiveNote(char* args[]);


void addNote(char* args[], int numArgs) {
	char note[256];
	char notePath[256];
	char* tilde = "~";
	parseUnaryArgs(note, args, numArgs);
	
	wordexp_t newNote;
	wordexp(tilde, &newNote, 0);	

	strcpy(notePath, newNote.we_wordv[0]);
	strcat(notePath, "/.liszt/notes/");
	strcat(notePath, note);

	int result = makeNote(notePath);
	if (result == -1) {
		return;	
	}
	// Change to this note, add with addition of changeNote
	printf("Added new note '%s'\n", note);
	wordfree(&newNote);
	
}


void removeNote(char* args[], int numArgs, char* currentNote, char* dataFile) {
	char note[256];
	int returnVal = parseUnaryArgs(note, args, numArgs);
	if (returnVal == 1) {
		printf("You haven't entered enough infomration. Please try again.\n");
		return;
	}
	// PREVENTING USER FROM DELETING DEFAULT NOT WORKING
	// char loweredNote[256];
	// int numChars = strlen(note);
	// char result = tolower(note[0]);
	// strcpy(loweredNote, &result);
	// for (int i = 1; i < numChars; i++) {
	//	result = tolower(note[i]);
	//	strcat(loweredNote, &result);
	//}
	//if (strcmp(loweredNote, "default") == 0) {
	//	printDefaultError();
	//	return;
	//}
	// ISSUE WITH DEFAULT ENDS HERE
	char prompt[256] = "Are you sure you want to remove '";
	strcat(prompt, note);
	strcat(prompt, "'?\033[1m There is no going back (y/n): \033[0m");
 
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		wordexp_t noteToRemovePath;
		char noteToRemove[256];
		strcpy(noteToRemove, "~/.liszt/notes/");
		strcat(noteToRemove, note);
		wordexp(noteToRemove, &noteToRemovePath, 0);

		char* fullNotePath = noteToRemovePath.we_wordv[0];

		struct stat st = {0};
		if (stat(fullNotePath, &st) == -1) {
			printf("The note you are trying to remove does not exist. Please try again.\n");
			return;
		}
		remove(fullNotePath);
		// why am i entering this conditional...
		if (strcmp(currentNote, "default") != 0) {
			printf("Inside conditional\n");
			wordexp_t defaultPath;
			wordexp("~/.liszt/notes/default", &defaultPath, 0);
			writeToDataFile(dataFile, defaultPath.we_wordv[0]);
		}
		
		 printf("Sucessfully removed '%s'\n", note);
	} else printf("Note removal aborted\n");

}


void clearNotes(char* currentNote, char* dataFile) {
	char prompt[] = "Are you sure you want to clear all of your notes?\033[1m There is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		wordexp_t notesDir;
		wordexp("~/.liszt/notes", &notesDir, 0);
		char* notes[256];
		int numNotes = 0;
		readDirectory(notesDir.we_wordv[0], notes, &numNotes);
		if (numNotes == 1) {
			printf("You have no notes to clear!\n");
			return;
		}

		for (int i = 0; i < numNotes; i++) {
			if (strcmp(notes[i], "default") == 0) continue;
			wordexp_t notePath;
			char note[256];
			strcpy(note, "~/.liszt/notes/");
			strcat(note, notes[i]);
			wordexp(note, &notePath, 0);
			remove(notePath.we_wordv[0]);	
		}
		if (strcmp(currentNote, "default") != 0) {
			wordexp_t defaultPath;
			wordexp("~/.liszt/notes/default", &defaultPath, 0);
			writeToDataFile(dataFile, defaultPath.we_wordv[0]);
		}
			
		printf("Cleared all user notes for Liszt cache\n");
	} else printf("Clearing of notes aborted\n");
}


void clearArchiveNotes(char* archivedNotes[]);


void getCurrentNote(char* dataFile, char* currentNotePath, char* currentNoteName) {
	FILE* toRead;
	toRead = fopen(dataFile, "r");
	fscanf(toRead, "%s", currentNotePath);
	fclose(toRead);
	
	int counter = 0; // for counting the number of slashes passed
	int index = 0; // for counting the index in the string
	int pathLength = strlen(currentNotePath);
	while (counter < 5 && index < pathLength) {
		if (currentNotePath[index] == '/') {
			counter++; 
		}
		index++;
	}
	strncat(currentNoteName, currentNotePath + index, pathLength - index);

}	
	

int changeNote(char* args[], int numArgs, char* dataFile) {

	char currentNotePath[256];
	char currentNoteName[256];
	getCurrentNote(dataFile, currentNotePath, currentNoteName);

	char note[256];
	char notePath[256];
	char* tilde = "~";
	parseUnaryArgs(note, args, numArgs);
	// stop if the note to be change to is the current note	
	if (strcmp(currentNoteName, note) == 0) {
		printf("The note you are trying to change to is already the current note.\n");
		return -1;
	}
	if (strcmp(note, "default") == 0) {
		printDefaultError();
		return -1;
	}
	
	struct stat st = {0};
	wordexp_t changeNote;
	wordexp(tilde, &changeNote, 0);	

	tilde = changeNote.we_wordv[0];

	strcpy(notePath, tilde);
	strcat(notePath, "/.liszt/notes/");
	strcat(notePath, note);

	if (stat(notePath, &st) == -1) {
		printf("Hmmm. The note you entered doesn't seem to exist. Please try again.\n");
		return -1;
	}	

	if (strcmp(currentNoteName, "default") == 0) {
		int numMemories = getFileSize(currentNotePath);
		if (numMemories > 0) {
			char newNote[256];
			printf("The current note must be named before changing notes. Please enter a name (ENTER to delete the current note): ");
			scanf("%s", newNote);
			if (strlen(newNote) > 0) {
				char newNotePath[256];	
				strcpy(newNotePath, tilde);
				strcat(newNotePath, "/.liszt/notes/");
				strcat(newNotePath, newNote);
				int result = makeNote(newNotePath);
				if (result == -1) {
					return -1;
				}
				copyFile(currentNotePath, newNotePath);
				// the following is for clearing 'default'
				FILE* toClear = fopen(currentNotePath, "w");
				fclose(toClear);
			}
		}
	}
	
	writeToDataFile(dataFile, notePath);
	wordfree(&changeNote);
	printf("Changed current note to '%s'\n", note);
	return 0;
}


int renameNote(char* args[], char* currentNote, char* dataFile);


