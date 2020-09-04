#include <stdio.h>
#include <string.h>
#include <wordexp.h>
#include <ctype.h>
#include <stdlib.h>
// The below imports are liszt .h files
#include "thought.h"
#include "helper.h"
#include "note.h"
#include "help.h"
#include "install.h"

#define MAX_LENGTH 256


/*
 * Handles command line arguments and
 * redirects to appropriate helper
 * functions.
 */
int main(int argc, char* argv[]) {

	// Check if ~/.liszt exists
	checkInstallation();

	// Return quickly if no arguments supplied (besides program invocation)
	if (argc == 1) {
		info();
		return 0;
	}
	
	// save first arg after program invocation as command (will be added back if just adding a thought)
	char* command = argv[1];

	// Prevent overload errors on input
	if (argc - 2 > MAX_LENGTH) {
		printf("Whoa there! That's a lot of information. Try and enter that in smaller pieces.\n");
		return 0;
	}

	if (command[0] == '-') {
		if (argc == 2) {
			if (strcmp(command, "-l") == 0) {
				listThoughts();
			} else if (strcmp(command, "-cl") == 0) {
				clearThoughts();
			} else if (strcmp(command, "-help") == 0 || strcmp(command, "-h") == 0) {
				getHelp();
			} else if (strcmp(command, "-version") == 0 || strcmp(command, "-v") == 0) {
				getVersion();
			} else if (strcmp(command, "-ln") == 0) {
				char dir[] = "notes";
				listNotes(dir);
			} else if (strcmp(command, "-n") == 0) {
				printCurrentNoteName();	
			} else if (strcmp(command, "-cln") == 0) {
				clearNotes();
			} else if (strcmp(command, "-clar") == 0) {
				clearArchiveNotes();
			} else if (strcmp(command, "-rm") == 0) { // this is for removing the current note
				removeCurrent();
			} else if (strcmp(command, "-ar") == 0) { // this is for archiving the current note
				archiveCurrent();
			} else if (strcmp(command, "-lar") == 0) {
				char dir[] = "archive";
				listNotes(dir);
			} else {
				sendErrorMessage(command);
			}
		} else if (argc > 2) {
			if (strcmp(command, "-r") == 0 && argc == 3) {
				removeThought(argv[2]);
			} else if (strcmp(command, "-a") == 0) {
				addNote(argv, argc);
			} else if (strcmp(command, "-ch") == 0) {
				changeNote(argv, argc);
			} else if (strcmp(command, "-rn") == 0 ) {
				renameNote(argv, argc);
			} else if (strcmp(command, "-rm") == 0) {
				removeNote(argv, argc);
			} else if (strcmp(command, "-ar") == 0) {
				archiveNote(argv, argc);
			} else if (strcmp(command, "-unar") == 0) {
				unArchiveNote(argv, argc);
			} else if (strcmp(command, "-in") == 0) {
				importNote(argv, argc);
			} else if (strcmp(command, "-ex") == 0) {
				exportNote(argv, argc);
			} else if (strcmp(command, "-dp") == 0) {
				duplicateNote(argv, argc);
			} else if (strcmp(command, "-mg") == 0) {
				mergeNotes(argv, argc);
			} else if (strcmp(command, "-m") == 0) {
				moveThought(argv, argc);
			} else if (strcmp(command, "-c") == 0) {
				copyThought(argv, argc);
			} else if (argc == 3 && (strcmp(command, "-help") == 0 || strcmp(command, "-h")) == 0) {
				if (strcmp(argv[2], "-") == 0) helpAddThought(); // get help with adding thoughts
				else if (strcmp(argv[2], "-l") == 0) helpListThoughts(); // get help with listing thoughts
				else if (strcmp(argv[2], "-cl") == 0) helpClearThoughts(); // get help with clearing thoughts
				else if (strcmp(argv[2], "-r") == 0) helpRemoveThought(); // get help with removing thoughts
				else if (strcmp(argv[2], "-m") == 0) helpMoveThought(); // get help with moving thoughts
				else if (strcmp(argv[2], "-c") == 0) helpCopyThought(); // get help with copying thoughts
				else if (strcmp(argv[2], "-a") == 0) helpAddNote(); // get help with adding notes
				else if (strcmp(argv[2], "-ln") == 0) helpListNotes(); // get help with listing notes
				else if (strcmp(argv[2], "-n") == 0) helpCurrentNote(); // get help with checking the current note
				else if (strcmp(argv[2], "-ch") == 0) helpChangeNote(); // get help with changing notes
				else if (strcmp(argv[2], "-rn") == 0) helpRenameNote(); // get help with renaming notes
				else if (strcmp(argv[2], "-rm") == 0) helpRemoveNote(); // get help with removing notes
				else if (strcmp(argv[2], "-cln") == 0) helpClearNotes(); // get help with clearing notes
				else if (strcmp(argv[2], "-dp") == 0) helpDuplicateNote(); // get help with duplicating notes
				else if (strcmp(argv[2], "-in") == 0) helpImportNote(); // get help with importing notes
				else if (strcmp(argv[2], "-ex") == 0) helpExportNote(); // get help with exporting notes
				else if (strcmp(argv[2], "-mg") == 0) return 0; // get help with exporting notes ADD HERE
				else if (strcmp(argv[2], "-ar") == 0) helpArchiveNote(); // get help with archiving notes
				else if (strcmp(argv[2], "-unar") == 0) helpUnarchiveNote(); // get help with unarchiving notes
				else if (strcmp(argv[2], "-lar") == 0) helpListArchivedNotes(); // get help with listing archived notes 
				else if (strcmp(argv[2], "-clar") == 0) helpClearArchivedNotes(); // get help with clearing archived notes
				else {
					sendHelpError(argv[2]);
				}
			} else {
				sendErrorMessage(command);
			}
		}	
	} else addThought(argv, argc);
	
	return 0;
}
	
