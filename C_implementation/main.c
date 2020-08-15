#include <stdio.h>
#include <string.h>
// The below imports are qnote .h files
#include "headers/memory.h"
#include "headers/helper_func.h"
#include "headers/note.h"
#include "headers/install.h"

// Macro to find the size of an array (found on the internet!)
#define NELEMS(array) (sizeof(array) / sizeof((array)[0]))


// Color Definitions
const char* BOLD = "\033[1m";
const char* ITALIC = "\033[3m";
const char* RESET = "\033[0m";


/*
 * Prints some random info about Quick Note
 */
void info() {
	char quicknote[100];
	strcpy(quicknote, BOLD);
	
	strcat(quicknote, "Quick Note\n");
	strcat(quicknote, RESET);
	
	printf("%s", quicknote);
	return;
}


/*
 * Handles command line arguments and
 * redirects to appropriate helper
 * functions.
 */
int main(int argc, char* argv[]) {

	if (argc == 1) {
		info();
		return 0;
	}
	char* command = argv[1];
	char args[100];
	// Prevent overload errors on input
	if (argc - 2 > 100) {
		printf("Whoa there! That's a lot of information. Try and enter that in smaller pieces.\n");
		return 0;
	}
	for (int i = 2; i < argc; i++) {
		args[i - 2] = *argv[i];	
	} 
	int numArgs = argc - 2;
	if (command[0] == "-") {
		if (numArgs == 1) {
			if (command == "-l") {
				// mem.list_memories(current_note, current_note_name)
			} else if (*command == "-cl") {
				// mem.clear_memories(current_note)
			} else if (*command == "-help" || command == "-h") {
				// get_help()
			} else if (*command == "-version" || command == "-v") {
				// get_version()
			} else if (*command == "-ln") {
				// return_value = note.list_notes(notes) 
				// if return_value == None:
				//	print("You have no notes at the moment. Start by adding a new note or by importing one from a \".txt.\' file.')
			} else if (*command == "-n") {
				// print(current_note_name)
			} else if (*command == "-cln") {
				// note.clear_notes(notes, current_note_name, data_file)
			} else if (*command == "-clar") {
				// note.clear_archive_notes(archive_notes)
			} else if (*command == "-rm") {
				// note.remove_note(current_note_name, current_note_name, data_file)
			// this is for archiving the current note
			} else if (*command == "-ar") {
			//	note.archive_note(current_note_name, current_note_name, data_file)
			} else if (*command == "-lar") {
			//	return_value = note.list_notes(archive_notes)
			//	if return_value == None:
			//		print("You have no archived notes at the moment.")
			} else {
			//	print("qnote error: command \"' + command + '\' not recognized. Please try again.')
			//	exit(1)
			}
		}
		else if (numArgs >= 1) {
			if (*command == "-r") {
			
			}
		}

	}	
	if (argc >= 2) {
		strcat(command, "\n");
		printf("%s", command);
	}
	

	return 0;
}
	
