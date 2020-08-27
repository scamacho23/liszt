#include <stdio.h>
#include <string.h>
#include <wordexp.h>
#include <ctype.h>
#include <stdlib.h>
// The below imports are liszt .h files
#include "memory.h"
#include "helper_func.h"
#include "note.h"
#include "help.h"
#include "install.h"


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
	wordfree(&liszt);

	// Return quickly if no arguments supplied (besides program invocation)
	if (argc == 1) {
		info();
		return 0;
	}
	
	char* command = argv[1];

	// Prevent overload errors on input
	if (argc - 2 > 256) {
		printf("Whoa there! That's a lot of information. Try and enter that in smaller pieces.\n");
		return 0;
	}

	if (command[0] == '-') {
		if (argc == 2) {
			if (strcmp(command, "-l") == 0) {
				listMemories();
			} else if (strcmp(command, "-cl") == 0) {
				clearMemories();
			} else if (strcmp(command, "-help") == 0 || strcmp(command, "-h") == 0) {
				getHelp();
			} else if (strcmp(command, "-version") == 0 || strcmp(command, "-v") == 0) {
				getVersion();
			} else if (strcmp(command, "-ln") == 0) {
				char* shortName = " ";
				wordexp_t notes;
				wordexp("~/.liszt/notes", &notes, 0);
				printDirectory(notes.we_wordv[0], shortName);
				wordfree(&notes);
			} else if (strcmp(command, "-n") == 0) {
				char currentNotePath[256];
				char currentNoteName[256];
				getCurrentNote(currentNotePath, currentNoteName);	
				printf("%s\n", currentNoteName);
			} else if (strcmp(command, "-cln") == 0) {
				clearNotes();
			} else if (strcmp(command, "-clar") == 0) {
				clearArchiveNotes();
			} else if (strcmp(command, "-rm") == 0) { // this is for removing the current note
				removeCurrent();
			} else if (strcmp(command, "-ar") == 0) { // this is for archiving the current note
				archiveCurrent();
			} else if (strcmp(command, "-lar") == 0) {
				char* shortName = " archived ";
				wordexp_t archive;
				wordexp("~/.liszt/archive", &archive, 0);
				printDirectory(archive.we_wordv[0], shortName);
				wordfree(&archive);
			} else {
				printf("lst error: command '%s' not recognized. Please try again.\n", command);
				printf("(hint: did you include the necessary arguments for this command? Run 'lst -h' to find out)\n");
				exit(1);
			}
		} else if (argc > 2) {
			if (strcmp(command, "-r") == 0 && argc == 3) {
				removeMemory(argv[2]);
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
			} else if (strcmp(command, "-m") == 0) {
				moveMemory(argv, argc);
			} else if (strcmp(command, "-c") == 0) {
				copyMemory(argv, argc);
			} else if (argc == 3 && (strcmp(command, "-help") == 0 || strcmp(command, "-h")) == 0) {
				if (strcmp(argv[2], "-") == 0) helpAddMemory();
				else if (strcmp(argv[2], "-l") == 0) helpListMemories(); 
				else if (strcmp(argv[2], "-cl") == 0) helpClearMemories(); 
				else if (strcmp(argv[2], "-r") == 0) helpRemoveMemory(); 
				else if (strcmp(argv[2], "-m") == 0) helpMoveMemory(); 
				else if (strcmp(argv[2], "-c") == 0) helpCopyMemory(); 
				else if (strcmp(argv[2], "-a") == 0) helpAddNote(); 
				else if (strcmp(argv[2], "-ln") == 0) helpListNotes(); 
				else if (strcmp(argv[2], "-n") == 0) helpCurrentNote(); 
				else if (strcmp(argv[2], "-ch") == 0) helpChangeNote(); 
				else if (strcmp(argv[2], "-rn") == 0) helpRenameNote(); 
				else if (strcmp(argv[2], "-rm") == 0) helpRemoveNote(); 
				else if (strcmp(argv[2], "-cln") == 0) helpClearNotes(); 
				else if (strcmp(argv[2], "-dp") == 0) helpDuplicateNote(); 
				else if (strcmp(argv[2], "-in") == 0) helpImportNote(); 
				else if (strcmp(argv[2], "-ex") == 0) helpExportNote(); 
				else if (strcmp(argv[2], "-ar") == 0) helpArchiveNote(); 
				else if (strcmp(argv[2], "-unar") == 0) helpUnarchiveNote(); 
				else if (strcmp(argv[2], "-lar") == 0) helpListArchivedNotes(); 
				else if (strcmp(argv[2], "-clar") == 0) helpClearArchivedNotes(); 
				else {
					printf("lst error: command '%s' not recognized for help request. Please try again.\n", argv[2]);	
					exit(1);
				}
			} else {
				printf("lst error: command '%s' not recognized. Please try again.\n", command);	
				printf("(hint: did you include the necessary arguments for this command? Run 'lst -h' to find out)\n");
				exit(1);
			}
		}	
	} else addMemory(argv, argc);
	
	return 0;
}
	
