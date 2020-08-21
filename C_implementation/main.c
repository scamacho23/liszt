#include <stdio.h>
#include <string.h>
#include <wordexp.h>
#include <ctype.h>
#include <stdlib.h>
// The below imports are liszt .h files
#include "memory.h"
#include "helper_func.h"
#include "note.h"
#include "install.h"


// Color Definitions
const char* BOLD = "\033[1m";
const char* ITALIC = "\033[3m";
const char* RESET = "\033[0m";


/*
 * Finds the full path to data_file.json and the current note, and the contents 
 * of the archive and notes directories (i.e. the full paths of each file 
 * in those directories)
 */
void backgroundInfo(char* dataFilePath, char* currentNotePath, char* notes[], int* numNotes, char* archive[], int* numArchive) {
	// Get data_file.json
	wordexp_t dataFile;
	wordexp("~/.liszt/background/data_file.json", &dataFile, 0);
	dataFilePath = dataFile.we_wordv[0];

	// Get current note
	// char* currentNotePath = getCurrentNote(dataFilePath);

	// Get current notes
	wordexp_t notesDir;
	wordexp("~/.liszt/notes", &notesDir, 0);
	readDirectory(notesDir.we_wordv[0], notes, numNotes);	

	// Get archive notes
	wordexp_t archiveDir;
	wordexp("~/.liszt/archive", &archiveDir, 0);
	readDirectory(archiveDir.we_wordv[0], archive, numArchive);

	// THIS NEEDS WORK (ARRAYS NOT FUNCTIONING PROPERLY)

}


/*
 * Prints the user's version of Liszt
 */
void getVersion() {
	printf("\033[1mLiszt v.1.0.19\033[0m\n");
}


/*
 * Prints help and usage information for the various Liszt commands
 */
void getHelp() {
	getVersion();
	char* arrow = "\033[1m\033[34m==>\033[0m";
	// General concepts of Liszt
	printf("\n\033[1mGeneral\033[0m\n\n");
	printf("'Notes' are files where we store your thoughts\n");
	printf("'Memories' are the individual entries in each note\n\n");	
	// Memory functionality
	printf("\033[1mMemories\033[0m\n\n");
	printf("\033[1m\033[3m<your_memory>\033[0m %s for \033[1madding \033[0ma memory\n", arrow);
	printf("     Usage: 'lst Hello World!'\n");
	printf("\033[1m-l\033[0m %s for \033[1mlisting \033[0mmemories on the current note\n", arrow);
	printf("     Usage: 'lst -l'\n");
	printf("\033[1m-cl\033[0m %s for \033[1mclearing \033[0mmemories on the current note\n", arrow);
	printf("     Usage: 'lst -cl'\n");
	printf("\033[1m-r \033[3m<row_number>\033[0m %s for \033[1mremoving \033[0mthe memory at that row number in the current note (row number can be retrieved from '\033[1mqnote -l\033[0m')\n", arrow);
	printf("     Usage: 'lst -r 3'\n");
	printf("\033[1m-m \033[3m<row_number> <other_note_name>\033[0m %s for \033[1mmoving \033[0mthe memory at that row number in the current note to another note\n", arrow);
	printf("     Usage: 'lst -m 3 shopping list'\n");
	printf("\033[1m-c \033[3m<row_number> <other_note_name>\033[0m %s for \033[1mcopying \033[0mthe memory at that row number in the current note to another note\n", arrow);
	printf("     Usage: 'lst -c 3 shopping list'\n\n");
	// Note functionality
	printf("\033[1mNOTES\033[0m\n\n");
	printf("\033[1m-a \033[3m<note_name>\033[0m %s for \033[1madding \033[0ma new note with the given name\n", arrow);
	printf("     Usage: 'lst -a shopping list'\n");
	printf("\033[1m-ln \033[0m %s for \033[1mlisting \033[0mcurrent notes\n", arrow);
	printf("     Usage: 'lst -ln'\n");
	printf("\033[1m-n \033[0m %s for \033[1mviewing \033[0mthe name of the current note\n", arrow);
	printf("     Usage: 'lst -n'\n");
	printf("\033[1m-ch \033[3m<note_name>\033[0m %s for \033[1mchanging \033[0mto the note with the given name\n", arrow);
	printf("     Usage: 'lst -ch To Do'\n");
	printf("\033[1m-rn \033[3m<note_name>\033[0m\033[1m / \033[3m<new_name>\033[0m %s for \033[1mrenaming \033[0mthe given note\n", arrow);
	printf("     Usage: 'lst -rn To Do / Done'\n");
	printf("\033[1m-rm \033[3m<note_name>\033[0m %s for \033[1mremoving \033[0mthe note with the given name (if no name given, removes the current note)\n", arrow);
	printf("     Usage: 'lst -rm To Do'\n");
	printf("\033[1m-cln \033[0m %s for \033[1mclearing \033[0myour current notes\n", arrow);
	printf("     Usage: 'lst -cln'\n");
	printf("\033[1m-dp \033[3m<note_to_duplicate>\033[0m\033[1m / \033[3m<new_note_name>\033[0m %s for \033[1mduplicating \033[0mexisting notes\n", arrow);
	printf("     Usage: 'lst -dp random / general'\n");
	printf("\033[1m-in \033[3m<file_to_import>\033[0m\033[1m / \033[3m<note_name>\033[0m %s for \033[1mimporting \033[0m'.txt' files as notes\n", arrow);
	printf("     Usage: 'lst -in random.txt / Assorted Tasks'\n");
	printf("\033[1m-ex \033[3m<note_to_export>\033[0m\033[1m / \033[3m<new_file_name>\033[0m %s for \033[1mexporting \033[0mnotes as '.txt' files\n", arrow);
	printf("     Usage: 'lst -ex Assorted Tasks / nextweek'\n");
	// Archive Functionality
	printf("\033[1mARCHIVE\033[0m\n");
	printf("\033[3mArchived notes do not receive the same functionality as regular notes. To rename, remove, export, etc. archived notes, please unarchive them first.\033[0m\n\n");
	printf("\033[1m-ar \033[3m<note_name>\033[0m %s for \033[1marchiving \033[0mthe note with the given name (if no name given, removes the current note)\n", arrow);
	printf("     Usage: 'lst -ar To Do'\n");
	printf("\033[1m-unar \033[3m<note_name>\033[0m %s for \033[1munarchiving \033[0mthe note with the given name\n", arrow);
	printf("     Usage: 'lst -unar To Do'\n");
	printf("\033[1m-lar \033[0m %s for \033[1mlisting \033[0marchived notes\n", arrow);
	printf("     Usage: 'lst -lar'\n");
	printf("\033[1m-clar \033[0m %s for \033[1mclearing \033[0myour archived notes\n", arrow);
	printf("     Usage: 'lst -clar'\n");
}
	

/*
 * Prints some random info about Liszt 
 */
void info() {
	char liszt[14];
	strcpy(liszt, BOLD);

	strcat(liszt, "Liszt");
	strcat(liszt, RESET);
	printf("%s is an open-source note-taking software designed for personal use.\n", liszt);

	printf("If you need help, type 'lst -help'\n");
	printf("To view your version of %s, type 'lst -version'\n\n", liszt);
	printf("%s uses the GNU General Public License v3, so you can edit, distribute, and otherwise meddle with any of the source code.\n", liszt);
	printf("The only thing you can't do is take this software and make it closed-source and try to sell it. %s was designed to be free for everyone, forever.\n\n", liszt);
	
	char* random_piece = "Hungarian Rhapsody No. 2 in C-sharp minor";	
	printf("\033[1mCheckout %s by Franz Liszt!\n\033[0m", random_piece); 
}


/*
 * Handles command line arguments and
 * redirects to appropriate helper
 * functions.
 */
int main(int argc, char* argv[]) {

	// Check if ~/.liszt exists
	struct stat st = {0};
	wordexp_t liszt;
	wordexp("~/.liszt", &liszt, 0);
	char* lisztPath = liszt.we_wordv[0];
	if (stat(lisztPath, &st) == -1) {
		// if ~/.liszt does not exist (e.g. user deleted it), create a new one
		int installation = install();
		// if installation fails again, hard quit
		if (installation == -1) {
			exit(1);
		}
	}

	// Return quickly if no arguments supplied (besides program invocation)
	if (argc == 1) {
		info();
		return 0;
	}
	
	char* command = argv[1];

	// Necessary Info to Grab
	// The following does not work properly
	char dataFilePath[100];
	char currentNotePath[100];
	char* notes[256];
	int numNotes = 0;
	char* archive[256];
	int numArchive = 0;
	backgroundInfo(dataFilePath, currentNotePath, notes, &numNotes, archive, &numArchive);
	
	if (strcmp(command, "-bi") == 0) {
		printf("NOTES\n");
		for (int i = 0; i < numNotes; i++) {
			printf("%s\n", notes[i]);
		}
		printf("ARCHIVE\n");
		for (int i = 0; i < numArchive; i++) {
			printf("%s\n", archive[i]);
		}

	}


	// the following is not quite right
	char args[256];

	// Prevent overload errors on input
	if (argc - 2 > 256) {
		printf("Whoa there! That's a lot of information. Try and enter that in smaller pieces.\n");
		return 0;
	}

	// The following is not quite right;
	for (int i = 2; i < argc; i++) {
		args[i - 2] = *argv[i];	
	} 
	
	int numArgs = argc - 2;
	
	if (command[0] == '-') {
		if (numArgs == 0) {
			if (strcmp(command, "-l") == 0) {
				listMemories("test.txt", "test");
			} else if (strcmp(command, "-cl") == 0) {
				// mem.clear_memories(current_note)
			} else if (strcmp(command, "-help") == 0 || strcmp(command, "-h") == 0) {
				getHelp();
			} else if (strcmp(command, "-version") == 0 || strcmp(command, "-v") == 0) {
				// get_version()
			} else if (strcmp(command, "-ln") == 0) {
				// return_value = note.list_notes(notes) 
				// if return_value == None:
				//	print("You have no notes at the moment. Start by adding a new note or by importing one from a \".txt.\' file.')
			} else if (strcmp(command, "-n") == 0) {
				// print(current_note_name)
			} else if (strcmp(command, "-cln") == 0) {
				// note.clear_notes(notes, current_note_name, data_file)
			} else if (strcmp(command, "-clar") == 0) {
				// note.clear_archive_notes(archive_notes)
			} else if (strcmp(command, "-rm") == 0) {
				// note.remove_note(current_note_name, current_note_name, data_file)
			// this is for archiving the current note
			} else if (strcmp(command, "-ar") == 0) {
			//	note.archive_note(current_note_name, current_note_name, data_file)
			} else if (strcmp(command, "-lar") == 0) {
				printf("LIST ARCHIVE NOTES\n");
			//	return_value = note.list_notes(archive_notes)
			//	if return_value == None:
			//		print("You have no archived notes at the moment.")
			} else {
			//	printf("lst error: command '%s' not recognized. Please try again.\n", command);
			//	exit(1);
			}
		} else if (numArgs >= 1) {
			if (strcmp(command, "-r") == 0) {
				printf("REMOVE MEMORY\n");	
			} else if (strcmp(command, "-a") == 0) {
				// mem.clear_memories(current_note)
			} else if (strcmp(command, "-ch") == 0 || strcmp(command, "-h") == 0) {
				// get_help()
			} else if (strcmp(command, "-rn") == 0 ) {
				// get_version()
			} else if (strcmp(command, "-rm") == 0) {
				// return_value = note.list_notes(notes) 
				// if return_value == None:
				//	print("You have no notes at the moment. Start by adding a new note or by importing one from a \".txt.\' file.')
			} else if (strcmp(command, "-ar") == 0) {
				// print(current_note_name)
			} else if (strcmp(command, "-unar") == 0) {
				// note.clear_notes(notes, current_note_name, data_file)
			} else if (strcmp(command, "-in") == 0) {
				// note.clear_archive_notes(archive_notes)
			} else if (strcmp(command, "-ex") == 0) {
				// note.remove_note(current_note_name, current_note_name, data_file)
			} else if (strcmp(command, "-dp") == 0) {
			//	note.archive_note(current_note_name, current_note_name, data_file)
			} else if (strcmp(command, "-m") == 0) {
			//	return_value = note.list_notes(archive_notes)
			//	if return_value == None:
			//		print("You have no archived notes at the moment.")
			} else if (strcmp(command, "-c") == 0) {
				// nothing
			} else {
			//	printf("lst error: command '%s' not recognized. Please try again.\n", command);	
			//	exit(1);
			}
		}	
	} else {
		// mem.add_memory(current_note, args)
	}
	


	// EVERYTHING BELOW IS TESTING FUNCTIONS. NEEDS TO BE DELETED	
	// test parseUnaryArgs
	int result = 0;
	if (strcmp(command, "-pu") == 0) {
		char word[256];
		parseUnaryArgs(word, argv, argc);
		printf("Your args: %s\n", word);
	}

	// test parseBinaryArgs
	if (strcmp(command, "-pb") == 0) {
		char first[256];
		char second[256];
		result = parseBinaryArgs(first, second, argv, argc);
		if (result == 0) {
			printf("First Word: %s\n", first);
			printf("Second Word: %s\n", second);
		}
	}



	// test readDirectory
	if (strcmp(command, "-rd") == 0) {
		char* files[256];
		int numFiles = 0;
		wordexp_t lisztDir;
		wordexp("~/.liszt/notes", &lisztDir, 0);	
		// printf("%s\n", lisztDir.we_wordv[0]);
		readDirectory(lisztDir.we_wordv[0], files, &numFiles);
		for (int i = 0; i < numFiles; i++) {
			printf("%s\n", files[i]);
		}
	}	

	if (strcmp(command, "-cr") == 0) {
		char* filename = "test.txt";
		char ** memories = malloc(256 * sizeof(char *));
		for(int i = 0; i < 256; i++){
			memories[i] = malloc(256 * sizeof(char));
		}
		int numMemories = 0;
        int result = 0;
			// int result = checkRow(filename, argv[2], &memories, &numMemories); 
		if (result == 1) {
			return 0;
		}
		printf("%s", memories[0]);
		free(memories);
		// for (int i = 0; i < numMemories; i++) {
			// printf("%s\n", memories[i]);
		//}
	}

	if (strcmp(command, "-mn") == 0) {
		wordexp_t filepath;
		wordexp("~/.liszt/notes/random", &filepath, 0);	
		int result = makeNote(filepath.we_wordv[0]);
		if (result == 1) {
			printf("Successfully created a new note called random");
		}
	}

	if (strcmp(command, "-up") == 0) {
		char* prompt = "If you are seeing this, it may be working? (y/n): ";
		char decision[256];
		requestUserPermission(prompt, decision);
		printf("%s\n", decision);
	}
	makeDirectories();
	
	// This is just testing that commands are coming in properly
	// if (argc >= 2) {
	//		strcat(command, "\n");
	//	printf("Command: %s", command);
	//}
	

	return 0;
}
	
