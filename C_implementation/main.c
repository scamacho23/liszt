#include <stdio.h>
#include <string.h>
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
	if (numArgs == 0) {
		if (strcmp(command, "-l") == 0) {
			listMemories("test.txt", "test");
		} else if (strcmp(command, "-cl") == 0) {
			// mem.clear_memories(current_note)
		} else if (strcmp(command, "-help") == 0 || strcmp(command, "-h") == 0) {
			// get_help()
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
		// mem.add_memory(current_note, args)
		//	print("qnote error: command \"' + command + '\' not recognized. Please try again.')
		//	exit(1)
		}
	}
	else if (numArgs >= 1) {
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
		// mem.add_memory(current_note, args)
		//	print("qnote error: command \"' + command + '\' not recognized. Please try again.')
		//	exit(1)
		}
		
	}
	
	// This is just testing that commands are coming in properly
	if (argc >= 2) {
		strcat(command, "\n");
		printf("Command: %s", command);
	}
	

	return 0;
}
	
