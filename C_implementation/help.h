#pragma once
/* help.h contains the function declarations necessary
 * for getting help for the various functions that come
 * with the Liszt application. See note.h for the function 
 * definitions.
 */


/*
 * Prints help information about adding memories
 */
void helpAddMemory();


/*
 * Prints help information about listing memories
 */
void helpListMemories();


/*
 * Prints help information about clearing memories
 */
void helpClearMemories();


/*
 * Prints help information about removing memories
 */
void helpRemoveMemory();


/*
 * Prints help information about moving memories
 */
void helpMoveMemory();


/*
 * Prints help information about copying memories
 */
void helpCopyMemory();


/*
 * Prints help information about adding notes
 */
void helpAddNote();


/*
 * Prints help information about listing notes
 */
void helpListNotes();


/*
 * Prints help information about getting the current
 * note
 */
void helpCurrentNote();


/*
 * Prints help information about changing notes
 */
void helpChangeNote();


/*
 * Prints help information about renaming notes
 */
void helpRenameNote();


/*
 * Prints help information about removing notes
 */
void helpRemoveNote();


/*
 * Prints help information about clearing notes
 */
void helpClearNotes();


/*
 * Prints help information about duplicating notes
 */
void helpDuplicateNote();


/*
 * Prints help information about importing notes
 */
void helpImportNote();


/*
 * Prints help information about exporting notes
 */
void helpExportNote();


/*
 * Prints help information about archiving notes 
 */
void helpArchiveNote();


/*
 * Prints help information about un-archiving notes 
 */
void helpUnarchiveNote();


/*
 * Prints help information about listing archived notes 
 */
void helpListArchivedNotes();


/*
 * Prints help information about clearing archived notes
 */
void helpClearArchivedNotes();


/*
 * Prints the user's version of Liszt
 */
void getVersion();


/*
 * Prints help and usage information for the various Liszt commands
 */
void getHelp();


/*
 * Prints a random musical piece by the ETERNAL FRANZ LISZT
 */
void liszt();


/*
 * Prints some random info about Liszt 
 */
void info();


#include "help.c"

