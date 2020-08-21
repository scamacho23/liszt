#pragma once
/* note.h contains the function declarations necessary
 * for manipulating notes in the Liszt project.
 * See note.c for the function definitions.
 */

/*
 * Given the name of a note and an array of memories, 
 * adds all the memories to the note
 */
void writeToNote(char* note, char* memories[], int numMemories);


/*
 * Given the name of a note, duplicates that note and names
 * the new note the desired name.
 */
void duplicateNote(char* args[]);


/*
 * Given the name of a .txt file, makes a copy of that file 
 * to be used as a new note
 */
void importNote(char* args[]);


/*
 * Given the name of a note, makes a copy of the note which is then exported
 * to the user's working directory
 */
void exportNote(char* args[]);


/*
 * Given the name of a note, moves the note frrom the ~/.liszt/notes directory 
 * and to the ~/.liszt/archive_notes directory 
 */ 
void archiveNote(char* args[], char* currentNote, char* dataFile);


/*
 * Given the name of a note, moves the note frrom the ~/.liszt/archive_notes directory 
 * and to the ~/.liszt/notes directory 
 */ 
void unArchiveNote(char* args[]);


/*
 * Given a note-name, adds a file in the ~/.liszt/notes directory with the given name, 
 * which will then be set as the current file for memories
 */
void addNote(char* args[]);


/*
 * Prints the list of current notes.
 * Returns 0 if successful, -1 if not
 */
int listNotes(char* notes[]);


/*
 * Given the name of a note, deletes the note with that name if it exists.
 */
void removeNote(char* args[], char* currentNote, char* dataFile);


/*
 * Clears all available notes besides 'default'
 */
void clearNotes(char* notes[], char* currentNote, char* dataFile);


/*
 * Clears all archived notes
 */
void clearArchiveNotes(char* archivedNotes[]);


/*
 * Returns the name of the current working note
 */
void getCurrentNote(char* dataFile, char* currentNote);


/*
 * Given the name of a note, the current note, and data_file.json,
 * changes the current note to the given note.
 * Returns 0 if successful, -1 if not
 */
int changeNote(char* args[], char* currentNote, char* dataFile);


/*
 * Given the name of a note and new name, renames the note
 * to the given name.
 * Returns 0 if successful, -1 if not.
 */
int renameNote(char* args[], char* currentNote, char* dataFile);


#include "note.c"

