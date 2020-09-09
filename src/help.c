#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// The below are Liszt .h files
#include "help.h"


const char LISZT_PIECES[20][70] = {"Hungarian Rhapsodies Nos 1-19", "La Lagubre Gondola", "Mephisto Waltz No. 1",
				"Piano Sonata in B Minor", "A Faust Symphony", "Piano Concerto No. 1", "Piano Concerto No. 2", 
				"Totentanz", "Deux Legendes", "Annees de pelerinage", "Liebestraum No. 3", "La Campanella",
				"Transcendental Etudes", "Consolation No. 3", "Un Sospiro", "Schwanengesang", "Mazeppa",
				"Hexameron", "Hunnenschlacht", "Concerto pathetique"};
						

const char ARROW[] = "\033[1m\033[34m==>\033[0m";


void sendHelpError(char* command) {
	printf("lst error: command '%s' not recognized for help request. Please try again.\n", command);	
	exit(1);
}


void helpAddMemory() {
	printf("\033[1m\033[3m<your_memory>\033[0m %s for \033[1madding \033[0ma memory\n", ARROW);
	printf("     Usage: 'lst Hello, World!'\n");
}


void helpListMemories() {
	printf("\033[1m-l\033[0m %s for \033[1mlisting \033[0mmemories on the current note\n", ARROW);
	printf("     Usage: 'lst -l'\n");
}


void helpClearMemories() {
	printf("\033[1m-cl\033[0m %s for \033[1mclearing \033[0mmemories on the current note\n", ARROW);
	printf("     Usage: 'lst -cl'\n");
}


void helpRemoveMemory() {
	printf("\033[1m-r \033[3m<row_number>\033[0m %s for \033[1mremoving \033[0mthe memory at that row number in the current note (row number can be retrieved from '\033[1mlst -l\033[0m')\n", ARROW);
	printf("     Usage: 'lst -r 3'\n");
}


void helpMoveMemory() {
	printf("\033[1m-m \033[3m<row_number> <other_note_name>\033[0m %s for \033[1mmoving \033[0mthe memory at that row number in the current note to another note\n", ARROW);
	printf("     Usage: 'lst -m 3 shopping list'\n");
}


void helpCopyMemory() {
	printf("\033[1m-c \033[3m<row_number> <other_note_name>\033[0m %s for \033[1mcopying \033[0mthe memory at that row number in the current note to another note\n", ARROW);
	printf("     Usage: 'lst -c 3 shopping list'\n");
}


void helpAddNote() {
	printf("\033[1m-a \033[3m<note_name>\033[0m %s for \033[1madding \033[0ma new note with the given name\n", ARROW);
	printf("     Usage: 'lst -a shopping list'\n");
}


void helpListNotes() {
	printf("\033[1m-ln \033[0m %s for \033[1mlisting \033[0mcurrent notes\n", ARROW);
	printf("     Usage: 'lst -ln'\n");
}


void helpCurrentNote() {
	printf("\033[1m-n \033[0m %s for \033[1mviewing \033[0mthe name of the current note\n", ARROW);
	printf("     Usage: 'lst -n'\n");
}


void helpChangeNote() {
	printf("\033[1m-ch \033[3m<note_name>\033[0m %s for \033[1mchanging \033[0mto the note with the given name\n", ARROW);
	printf("     Usage: 'lst -ch To Do'\n");
}


void helpRenameNote() {
	printf("\033[1m-rn \033[3m<note_name>\033[0m\033[1m / \033[3m<new_name>\033[0m %s for \033[1mrenaming \033[0mthe given note\n", ARROW);
	printf("     Usage: 'lst -rn To Do / Done'\n");
}


void helpRemoveNote() {
	printf("\033[1m-rm \033[3m<note_name>\033[0m %s for \033[1mremoving \033[0mthe note with the given name (if no name given, removes the current note)\n", ARROW);
	printf("     Usage: 'lst -rm To Do'\n");
}

void helpClearNotes() {
	printf("\033[1m-cln \033[0m %s for \033[1mclearing \033[0myour current notes\n", ARROW);
	printf("     Usage: 'lst -cln'\n");
}


void helpDuplicateNote() {
	printf("\033[1m-dp \033[3m<note_to_duplicate>\033[0m\033[1m / \033[3m<new_note_name>\033[0m %s for \033[1mduplicating \033[0mexisting notes\n", ARROW);
	printf("     Usage: 'lst -dp random / general'\n");
}


void helpImportNote() {
	printf("\033[1m-in \033[3m<file_to_import>\033[0m\033[1m / \033[3m<note_name>\033[0m %s for \033[1mimporting \033[0m'.txt' files as notes\n", ARROW);
	printf("     Usage: 'lst -in random.txt / Assorted Tasks'\n");
}


void helpExportNote() {
	printf("\033[1m-ex \033[3m<note_to_export>\033[0m\033[1m / \033[3m<new_file_name>\033[0m %s for \033[1mexporting \033[0mnotes as '.txt' files\n", ARROW);
	printf("     Usage: 'lst -ex Assorted Tasks / nextweek'\n");
}


void helpMergeNotes() {
	printf("\033[1m-mg \033[3m<note_to_merge>\033[0m\033[1m / \033[3m<note_to_merge_into>\033[0m %s for \033[1mmerging \033[0mtwo notes (removes the first note)\n", ARROW);
	printf("     Usage: 'lst -mg Meal Planning List / Grocery List'\n");
}


void helpArchiveNote() {
	printf("\033[1m-ar \033[3m<note_name>\033[0m %s for \033[1marchiving \033[0mthe note with the given name (if no name given, removes the current note)\n", ARROW);
	printf("     Usage: 'lst -ar To Do'\n");
}


void helpUnarchiveNote() {
	printf("\033[1m-unar \033[3m<note_name>\033[0m %s for \033[1munarchiving \033[0mthe note with the given name\n", ARROW);
	printf("     Usage: 'lst -unar To Do'\n");
}


void helpListArchivedNotes() {
	printf("\033[1m-lar \033[0m %s for \033[1mlisting \033[0marchived notes\n", ARROW);
	printf("     Usage: 'lst -lar'\n");
}


void helpClearArchivedNotes() {
	printf("\033[1m-clar \033[0m %s for \033[1mclearing \033[0myour archived notes\n", ARROW);
	printf("     Usage: 'lst -clar'\n");
}


void getVersion() {
	printf("\033[1mLiszt v1.1.7\033[0m\n");
}


void getHelp() {
	getVersion();

	// General concepts of Liszt
	printf("\n\033[1mGeneral\033[0m\n\n");
	printf("'Notes' are files where we store your thoughts\n");
	printf("'Memories' are the individual entries in each note\n\n");	

	// Memory functionality
	printf("\033[1mMemories\033[0m\n\n");
	helpAddMemory();
	helpListMemories();
	helpClearMemories();
	helpRemoveMemory();
	helpMoveMemory();
	helpCopyMemory();
	printf("\n");

	// Note functionality
	printf("\033[1mNOTES\033[0m\n\n");
	helpAddNote();
	helpListNotes();
	helpCurrentNote();
	helpChangeNote();
	helpRenameNote();
	helpRemoveNote();
	helpClearNotes();
	helpDuplicateNote();
	helpImportNote();
	helpExportNote();
	helpMergeNotes();
	printf("\n");

	// Archive Functionality
	printf("\033[1mARCHIVE\033[0m\n");
	printf("\033[3mArchived notes do not receive the same functionality as regular notes. To rename, remove, export, etc. archived notes, please unarchive them first.\033[0m\n\n");
	helpArchiveNote();
	helpUnarchiveNote();
	helpListArchivedNotes();
	helpClearArchivedNotes();
}


void liszt() {
	srand(time(NULL));
	int randomPiece = rand() % 20;
	printf("\033[1mCheckout %s by Franz Liszt!\033[0m\n", LISZT_PIECES[randomPiece]); 
}


void info() {
	char lisztName[] = "\033[1mLiszt\033[0m";
	printf("%s is an open-source note-taking software designed for personal use.\n\n", lisztName);

	printf("If you need help in general, type 'lst -help' or 'lst -h'\n");
	char nameOfCommand[] = "\033[3m<name_of_command>\033[0m";
	printf("If you need help with a specific command, type 'lst -h %s', such as for help with adding memories ('lst -h -') or removing a note ('lst -h -rm')\n", nameOfCommand);
	printf("To view your version of %s, type 'lst -version' or 'lst -v'\n\n", lisztName);
	printf("%s uses the GNU General Public License v3, so you can edit, distribute, and otherwise meddle with any of the source code.\n", lisztName);
	printf("The only thing you can't do is take this software and make it closed-source and try to sell it. %s was designed to be free for everyone, forever.\n\n", lisztName);
	
	liszt();
}

