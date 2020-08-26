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


void duplicateNote(char* args[], int numArgs) {
	char existingNote[256];
	char newNote[256];
	int result = parseBinaryArgs(existingNote, newNote, args, numArgs);
	if (result == -1) return;

	char* dirName = "notes";
	char existingPath[256];
	char newPath[256];
	getNotePath(dirName, existingNote, existingPath);
	getNotePath(dirName, newNote, newPath);

	// confirm that a note actually exists with the given name
	struct stat st = {0};
	if (stat(existingPath, &st) == -1) {
		printf("There is no note called '%s'. Please try again.\n", existingNote);
		return;
	}

	// prevent the user from duplicating default
	if (strcmp(existingNote, "default") == 0) {
		printDefaultError();
		return;
	}
	
	result = makeNote(newPath);
	if (result == -1) {
		printf("Could not duplicate '%s'. Please try again.\n", existingNote);
		return;
	}
	copyFile(existingPath, newPath);
	printf("Successfully duplicated '%s' as '%s'\n", existingNote, newNote);
}


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
	char* dirName = "notes";	
	char fullNotePath[256];
	getNotePath(dirName, note, fullNotePath);

	result = makeNote(fullNotePath);
	if (result == 0) {
		copyFile(import, fullNotePath);	
		printf("Successfully imported '%s' as '%s'\n", import, note);
	}
}


void exportNote(char* args[], int numArgs) {
	char note[256];
	char export[256];
	int result = parseBinaryArgs(note, export, args, numArgs);

	if (result == -1) {
		return;
	}

	char notePath[256];
	char* dirName = "notes";
	getNotePath(dirName, note, notePath);
	
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
}


void archiveNote(char* args[], int numArgs) {
	char noteToArchive[256];
	parseUnaryArgs(noteToArchive, args, numArgs);
	char* dirName = "notes";
	char notePath[256];
	getNotePath(dirName, noteToArchive, notePath);

	struct stat st = {0};	

	if (stat(notePath, &st) == -1) {
		printf("The note you are trying to archive does not exist. Please try again.\n");
		return;
	}

	// prevent the user from archiving 'default'
	if (strcmp(noteToArchive, "default") == 0) {
		printDefaultError();
		return;	
	}

	dirName = "archive";
	char newPath[256];
	getNotePath(dirName, noteToArchive, newPath);

	if (stat(newPath, &st) != -1) {
		printf("You already have an archived note named '%s'. Please try again. (hint: rename something)\n", noteToArchive);
		return;
	}

	copyFile(notePath, newPath);
	remove(notePath);

	char currentNotePath[256];
	char currentNoteName[256];
	getCurrentNote(currentNotePath, currentNoteName);

	if (strcmp(currentNoteName, noteToArchive) == 0) {
		wordexp_t defaultPath;
		wordexp("~/.liszt/notes/default", &defaultPath, 0);
		writeToDataFile(defaultPath.we_wordv[0]);
	}

	printf("Archived '%s'\n", noteToArchive);
	
}


void unArchiveNote(char* args[], int numArgs) {



	char noteToUnArchive[256];
	parseUnaryArgs(noteToUnArchive, args, numArgs);
	char* dirName = "archive";
	char notePath[256];
	getNotePath(dirName, noteToUnArchive, notePath);

	struct stat st = {0};	

	if (stat(notePath, &st) == -1) {
		printf("The note you are trying to un-archive does not exist. Please try again.\n");
		return;
	}

	dirName = "notes";
	char newPath[256];
	getNotePath(dirName, noteToUnArchive, newPath);

	if (stat(newPath, &st) != -1) {
		printf("You already have a note named '%s'. Please try again. (hint: rename something)\n", noteToUnArchive);
		return;
	}

	copyFile(notePath, newPath);
	remove(notePath);

	printf("Un-archived '%s'\n", noteToUnArchive);
}


void addNote(char* args[], int numArgs) {
	char note[256];
	char notePath[256];
	parseUnaryArgs(note, args, numArgs);
	
	char* dirName = "notes";
	getNotePath(dirName, note, notePath);

	int result = makeNote(notePath);
	if (result == -1) {
		return;	
	}
	result = changeNoteHelper(note); 
	printf("Added new note '%s'\n", note);
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
		char* dirName = "notes";
		char fullNotePath[256];
		getNotePath(dirName, note, fullNotePath);

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
			writeToDataFile(defaultPath.we_wordv[0]);
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
			char* dirName = "notes";
			char note[256];
			getNotePath(dirName, notes[i], note);
			remove(note);	
		}
		if (strcmp(currentNote, "default") != 0) {
			wordexp_t defaultPath;
			wordexp("~/.liszt/notes/default", &defaultPath, 0);
			writeToDataFile(defaultPath.we_wordv[0]);
			wordfree(&defaultPath);
		}
		wordfree(&notesDir);	
		printf("Cleared all user notes for Liszt cache\n");
	} else printf("Clearing of notes aborted\n");
}


void clearArchiveNotes(char* archivedNotes[]);


void getCurrentNote(char* currentNotePath, char* currentNoteName) {
	char dataFile[256];
	getDataFile(dataFile);

	FILE* toRead;
	toRead = fopen(dataFile, "r");
	fscanf(toRead, "%s", currentNotePath);
	fclose(toRead);
	
	char slash = '/';
	char* lastSlash = strrchr(currentNotePath, slash);
	strcpy(currentNoteName, lastSlash + 1);
}	
	

int changeNoteHelper(char* note) {
	char dataFile[256];
	getDataFile(dataFile);
	char currentNotePath[256];
	char currentNoteName[256];
	getCurrentNote(currentNotePath, currentNoteName);

	// stop if the note to be changed to is the current note	
	if (strcmp(currentNoteName, note) == 0) {
		printf("The note you are trying to change to is already the current note.\n");
		return -1;
	}
	// stop if the note to be changed to is 'default'
	if (strcmp(note, "default") == 0) {
		printDefaultError();
		return -1;
	}

	struct stat st = {0};
	
	char* dirName = "notes";
	char notePath[256];
	getNotePath(dirName, note, notePath);

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
				getNotePath(dirName, newNote, newNotePath);

				int result = makeNote(newNotePath);
				if (result == -1) return -1;
				copyFile(currentNotePath, newNotePath);
				// the following is for clearing 'default'
				FILE* toClear = fopen(currentNotePath, "w");
				fclose(toClear);
			}
		}
	}
	writeToDataFile(notePath);
	return 0;
}

 
void changeNote(char* args[], int numArgs) {
	char note[256];
	parseUnaryArgs(note, args, numArgs);
	int result = changeNoteHelper(note);
	if (result == 0) printf("Changed current note to '%s'\n", note); 
}


int renameNote(char* args[], char* currentNote, char* dataFile);


