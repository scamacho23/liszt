#pragma once
#ifndef NOTE_H
#define NOTE_H
/* note.h contains the function declarations necessary
 * for manipulating notes in the Liszt project.
 * See note.c for the function definitions.
 */


/*
 * Given the names of two notes, merges the
 * first note into the second and deletes the
 * first note
 */
void mergeNotes(char* args[], int numArgs);


/*
 * Given the name of a note, duplicates that note and names
 * the new note the desired name.
 */
void duplicateNote(char* args[], int numArgs);


/*
 * Given the name of a .txt file, makes a copy of that file 
 * to be used as a new note
 */
void importNote(char* args[], int numArgs);


/*
 * Given the name of a note, makes a copy of the note which is then exported
 * to the user's working directory
 */
void exportNote(char* args[], int numArgs);


/*
 * Given nothing, moves the current note frrom the ~/.liszt/notes directory 
 * to the ~/.liszt/archive_notes directory 
 */ 
void archiveCurrent();


/*
 * Given the name of a note, moves the note from the ~/.liszt/notes directory 
 * to the ~/.liszt/archive_notes directory 
 */ 
void archiveNote(char* args[], int numArgs);


/*
 * Given the name of a note, moves the note frrom the ~/.liszt/archive_notes directory 
 * and to the ~/.liszt/notes directory 
 */ 
void unArchiveNote(char* args[], int numArgs);


/*
 * Given a note-name, adds a file in the ~/.liszt/notes directory with the given name, 
 * which will then be set as the current file for thoughts
 */
void addNote(char* args[], int numArgs);


/*
 * Given the name of a directory, lists
 * the notes in that directory
 */
void listNotes(char* directory);


/*
 * Deletes the current note and changes to default
 */
void removeCurrent();


/*
 * Given the name of a note, deletes the note with that name if it exists.
 */
void removeNote(char* args[], int numArgs);


/*
 * Clears all available notes besides 'default'
 */
void clearNotes();


/*
 * Clears all archived notes
 */
void clearArchiveNotes();


/*
 * Given the name of a note, changes to that note
 * Returns 0 if successful, -1 if not
 */
int changeNoteHelper(char* note);


/*
 * Given the name of a note, changes the 
 * current note to the given note.
 */
void changeNote(char* args[], int numArgs);


/*
 * Given the name of a note and new name, renames the note
 * to the given name.
 */
void renameNote(char* args[], int numArgs);


#include "note.c"
#endif

