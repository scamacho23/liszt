#include <stdio.h>
#include <wordexp.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
// The below are Liszt .h files
#include "note.h"
#include "util.h"

#define MAX_LENGTH 256


void mergeNotes(char* args[], int numArgs) {
	pair_t notes; 
	int result = parseBinaryArgs(&notes, args, numArgs);
	char *first_note = notes.first;
	char *second_note = notes.second;
	if (result == -1) return;

	char* dirName = "main";
	char *first_path = getNotePath(dirName, first_note);
	char *second_path = getNotePath(dirName, second_note);

	// confirm that notes actually exist with the given name
	struct stat st = {0};
	if (stat(first_path, &st) == -1) {
		printf("There is no note called '%s'. Please try again.\n", first_note);
		return;
	}
	if (stat(second_path, &st) == -1) {
		printf("There is no note called '%s'. Please try again.\n", second_note);
		return;
	}

	// prevent the user from merging into or from default
	result = checkDefault(first_note);
	if (result == -1) return;

	result = checkDefault(second_note);
	if (result == -1) return;
	
	// append the first note to the second
	FILE* source, * target;
	source = fopen(first_path, "r");
	target = fopen(second_path, "a");
	char filechar;
	while ((filechar = fgetc(source)) != EOF) {
		fputc(filechar, target);
	}
	fclose(source);
	fclose(target);

	remove(first_path);

	// change to default if merging the current note	
	char *current_path;
	char *current_note = getCurrentNote(&current_path);
	if (!strcmp(current_note, first_note)) {
		setToDefault();
	}
	
	printf("Successfully merged '%s' into '%s'\n", first_note, second_note);
	free(first_path);
	free(second_path);
	free(current_note);
	free(current_path);
	free(first_note);
	free(second_note);
}


void duplicateNote(char* args[], int numArgs) {
	pair_t notes;
	int result = parseBinaryArgs(&notes, args, numArgs);
	char *existing_note = notes.first;
	char *new_note = notes.second;
	if (result == -1) return;

	char* dirName = "main";
	char *existing_path = getNotePath(dirName, existing_note);
	char *new_path = getNotePath(dirName, new_note);

	// confirm that a note actually exists with the given name
	struct stat st = {0};
	if (stat(existing_path, &st) == -1) {
		printf("There is no note called '%s'. Please try again.\n", existing_note);
		return;
	}

	// prevent the user from duplicating default
	result = checkDefault(existing_note);
	if (result == -1) return;
	
	result = makeNote(new_path);
	if (result == -1) {
		printf("Could not duplicate '%s'. Please try again.\n", existing_note);
		return;
	}
	copyFile(existing_path, new_path);
	printf("Successfully duplicated '%s' as '%s'\n", existing_note, new_note);
	free(existing_path);
	free(new_path);
	free(existing_note);
	free(new_note);
}


void importNote(char* args[], int numArgs) {
	pair_t notes;
	int result = parseBinaryArgs(&notes, args, numArgs);
	char *note = notes.first;
	char *import = notes.second;
	struct stat st = {0};
	if (result == -1) {
		return;
	}

	// stop the user from even trying to import a note as 'default'
	result = checkDefault(import);
	if (result == -1) return;

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
	char *full_note_path = getNotePath("main", note);

	result = makeNote(full_note_path);
	if (result == 0) {
		copyFile(import, full_note_path);	
		printf("Successfully imported '%s' as '%s'\n", import, note);
	}
	free(full_note_path);
	free(note);
	free(import);
}


void exportNote(char* args[], int numArgs) {
	pair_t notes;
	int result = parseBinaryArgs(&notes, args, numArgs);
	char *note = notes.first;
	char *to_export = notes.second;

	if (result == -1) return;

	char *note_path = getNotePath("main", note);
	
	struct stat st = {0};
	if (stat(note_path, &st) == -1) {
		printf("Sorry. \033[1mLiszt\033[0m can't find the note you are trying to export: '%s'. Did you spell the name of the note correctly?\n", note);
		return;
	}

	// prevent the user from exporting default
	result = checkDefault(note);
	if (result == -1) return;
	
	strcat(to_export, ".txt");

	if (stat(to_export, &st) == 0) {
		printf("Sorry. A file with this name already exists in the directory to which you are trying to add. Please pick a different name\n");
		return;
	}

	copyFile(note_path, to_export);
	printf("Successfully exported '%s' as '%s'\n", note, to_export);
	free(note_path);
}


void archiveCurrent() {
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);

	// prevent the user from archiving default
	int result = checkDefault(current_note_name);
	if (result == -1) return;
	
	char *new_path = getNotePath("archive", current_note_name);
	rename(current_note_path, new_path);

	// switch current note to default
	setToDefault();

	printf("Archived '%s'\n", current_note_name);
	free(new_path);
	free(current_note_path);
	free(current_note_name);
}


void archiveNote(char* args[], int numArgs) {
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);

	char *note_to_archive = parseUnaryArgs(args, numArgs);
	char *note_path = getNotePath("main", note_to_archive);

	struct stat st = {0};	

	if (stat(note_path, &st) == -1) {
		printf("The note you are trying to archive does not exist. Please try again.\n");
		return;
	}

	// prevent the user from archiving default
	int result = checkDefault(note_to_archive);
	if (result == -1) return;

	char *dirName = "archive";
	char *new_path = getNotePath(dirName, note_to_archive);

	if (stat(new_path, &st) != -1) {
		printf("You already have an archived note named '%s'. Please try again. (hint: rename something)\n", note_to_archive);
		return;
	}

	rename(note_path, new_path);

	if (strcmp(current_note_name, note_to_archive) == 0) {
		setToDefault();
	}

	printf("Archived '%s'\n", note_to_archive);
	free(note_path);
	free(new_path);
	free(current_note_path);
	free(current_note_name);
	free(note_to_archive);
}


void unArchiveNote(char* args[], int numArgs) {
	char *note_to_unarchive = parseUnaryArgs(args, numArgs);
	char* dirName = "archive";
	char *note_path = getNotePath(dirName, note_to_unarchive);

	struct stat st = {0};	

	if (stat(note_path, &st) == -1) {
		printf("The note you are trying to un-archive does not exist. Please try again.\n");
		return;
	}

	dirName = "main";
	char *new_path = getNotePath(dirName, note_to_unarchive);

	if (stat(new_path, &st) != -1) {
		printf("You already have a note named '%s'. Please try again. (hint: rename something)\n", note_to_unarchive);
		return;
	}

	rename(note_path, new_path);

	printf("Un-archived '%s'\n", note_to_unarchive);
	free(note_path);
	free(new_path);
	free(note_to_unarchive);
}


void addNote(char* args[], int numArgs) {
	char *note = parseUnaryArgs(args, numArgs);

	// stop the user from even trying to name a note 'default'
	int result = checkDefault(note);
	if (result == -1) return;
	
	char *dirName = "main";
	char *note_path = getNotePath(dirName, note);

	result = makeNote(note_path);
	if (result == -1) {
		return;	
	}
	result = changeNoteHelper(note); 
	printf("Added new note '%s'\n", note);
	free(note_path);
}


void listNotes(char *directory) {
	wordexp_t dir;
	char path[20];
	strcpy(path, "~/.liszt/");
	strcat(path, directory);	
	wordexp(path, &dir, 0);

	char shortName[15];
	if (strcmp(directory, "main") == 0) {
		strcpy(shortName, " ");
	} else if (strcmp(directory, "archive") == 0) {
		strcpy(shortName, " archived ");
	}

	printDirectory(dir.we_wordv[0], shortName);

	wordfree(&dir);
}


void removeCurrent() {
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);

	// prevent the user from archiving default
	int result = checkDefault(current_note_name);
	if (result == -1) return;
	
	char prompt[MAX_LENGTH] = "Are you sure you want to remove '";
	strcat(prompt, current_note_name);
	strcat(prompt, "'?\033[1m There is no going back (y/n): \033[0m");
 
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		remove(current_note_path);
		// if the user is removing the current note
		setToDefault();

		printf("Sucessfully removed '%s'\n", current_note_name);
	} else printf("Note removal aborted\n");
	free(current_note_path);
	free(current_note_name);
}


void removeNote(char* args[], int numArgs) {
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);
	
	char *data_file = getDataFile();

	char *note = parseUnaryArgs(args, numArgs);
	// prevent the user from deleting default
	int result = checkDefault(note);
	if (result == -1) return;
	
	char prompt[MAX_LENGTH] = "Are you sure you want to remove '";
	strcat(prompt, note);
	strcat(prompt, "'?\033[1m There is no going back (y/n): \033[0m");
 
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		char* dirName = "main";
		char *full_note_path = getNotePath(dirName, note);

		struct stat st = {0};
		if (stat(full_note_path, &st) == -1) {
			printf("The note you are trying to remove does not exist. Please try again.\n");
			free(full_note_path);
			return;
		}
		remove(full_note_path);
		// if the user is removing the current note
		if (strcmp(current_note_name, note)) {
			setToDefault();
		}
		
		 printf("Sucessfully removed '%s'\n", note);
		 free(full_note_path);
	} else printf("Note removal aborted\n");
	free(current_note_path);
	free(data_file);
	free(current_note_name);
	free(note);
}


void clearNotes() {
	char *current_note_path;
	char *current_note = getCurrentNote(&current_note_path);
	
	char *data_file = getDataFile();

	char prompt[] = "Are you sure you want to clear all of your notes?\033[1m There is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		wordexp_t mainDir;
		wordexp("~/.liszt/main", &mainDir, 0);
		struct dirent **notes;
		int numNotes = scandir(mainDir.we_wordv[0], &notes, filter_entries, NULL);
		if (!numNotes) {
			printf("You have no notes to clear!\n");
			wordfree(&mainDir);
			return;
		}

		for (int i = 0; i < numNotes; i++) {
			char* dirName = "main";
			struct dirent *curr = notes[i];
			char *note = getNotePath(dirName, curr->d_name);
			remove(note);
			free(curr);
			free(note);
		}
		if (strcmp(current_note, "default") != 0) {
			setToDefault();
		}
		wordfree(&mainDir);	
		free(notes);
		printf("Cleared all user notes from Liszt cache\n");
	} else printf("Clearing of notes aborted\n");
	free(current_note_path);
	free(current_note);
	free(data_file);
}


void clearArchiveNotes() {
	char prompt[] = "Are you sure you want to clear all of your archived notes?\033[1m There is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision);
	if (strcmp(decision, "y") == 0) {
		wordexp_t archiveDir;
		wordexp("~/.liszt/archive", &archiveDir, 0);
		struct dirent **archive;
		int numNotes = scandir(archiveDir.we_wordv[0], &archive, filter_entries, NULL);
		if (!numNotes) {
			printf("You have no notes to clear!\n");
			wordfree(&archiveDir);
			return;
		}

		for (int i = 0; i < numNotes; i++) {
			char* dirName = "archive";
			struct dirent *curr = archive[i];
			char *note = getNotePath(dirName, curr->d_name);
			remove(note);	
			free(curr);
			free(note);
		}
		wordfree(&archiveDir);	
		free(archive);
		printf("Cleared all archived user notes from Liszt cache\n");
	} else printf("Clearing of notes aborted\n");
}


int changeNoteHelper(char* note) {
	char *data_file = getDataFile();
	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);

	// stop if the note to be changed to is the current note	
	if (!strcmp(current_note_name, note)) {
		printf("The note you are trying to change to is already the current note.\n");
		return -1;
	}
	// stop if the note to be changed to is 'default'
	int result = checkDefault(note);
	if (result == -1) return -1;

	struct stat st = {0};

	char *dirName = "main";
	char *note_path = getNotePath(dirName, note);

	if (stat(note_path, &st) == -1) {
		printf("Hmmm. The note you entered doesn't seem to exist. Please try again.\n");
		return -1;
	}	

	if (strcmp(current_note_name, "default") == 0) {
		int numMemories = getFileSize(current_note_path);
		if (numMemories > 0) {
			char new_note[MAX_LENGTH];
			printf("The current note must be named before changing notes. Please enter a name (ENTER to delete the current note): ");
			fgets(new_note, MAX_LENGTH, stdin);
			int length = strlen(new_note);
			if (length > 0) {
				new_note[length - 1] = '\0';
				char *new_note_path = getNotePath(dirName, new_note);

				result = makeNote(new_note_path);
				if (result == -1) return -1;
				copyFile(current_note_path, new_note_path);
				// the following is for clearing 'default'
				FILE* toClear = fopen(current_note_path, "w");
				fclose(toClear);
				free(new_note_path);
			}
		}
	}
	writeFilenameToDataFile(note_path);
	free(note_path);
	free(current_note_path);
	free(current_note_name);
	return 0;
}

 
void changeNote(char* args[], int numArgs) {
	char *note = parseUnaryArgs(args, numArgs);
	int result = changeNoteHelper(note);
	if (result == 0) printf("Changed current note to '%s'\n", note); 
	free(note);
}


void renameNote(char* args[], int numArgs) {
	pair_t notes;
	int result = parseBinaryArgs(&notes, args, numArgs);
	char *old_name = notes.first;
	char *new_name = notes.second;
	if (result == -1) return;
	
	char* dirName = "main";	
	char *old_path = getNotePath(dirName, old_name);
	char *new_path = getNotePath(dirName, new_name);

	// confirm that the note to change actually exists
	struct stat st = {0};
	if (stat(old_path, &st) == -1) {
		printf("The note you are trying to rename does not exist. Please try again.\n");
		return;
	}

	// prevent the user from renaming 'default'
	result = checkDefault(old_name);
	if (result == -1) return;

	rename(old_path, new_path);

	char *current_note_path;
	char *current_note_name = getCurrentNote(&current_note_path);

	if (strcmp(old_path, current_note_path) == 0) {
		writeFilenameToDataFile(new_path);
	}
	
	printf("Renamed '%s' to '%s'\n", old_name, new_name);
	free(old_path);
	free(new_path);
	free(current_note_path);
	free(current_note_name);
	free(old_name);
	free(new_name);
}

