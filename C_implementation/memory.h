#pragma once
/*
 * This file contains function declarations
 * for memory manipulation for the Liszt project.
 * See memory.cpp for the definitions.
 */


/* 
 * Given a memory and the name of a 
 * note, appends the memory to the
 * end of the note
 */
void appendMemory(char* memory, char* note);


/* 
 * Given the current_note and a row number,
 * removes the memory at that row and returns
 * its value
 */
char* changeMemory(char* currentNote, char* row);


/*
 * Given the name of a note and
 * a row number, moves the memory
 * at that row number in the current
 * note to the given note
 */
void moveMemory(char* currentNote, char* row, char args[]);


/*
 * Given the name of a note and
 * a row number, copies the memory
 * at that row number in the current
 * note to the given note
 */
void copyMemory(char* currentNote, char* row, char args[]);


/*
 * Given a note and a row number,
 * removes the memory at that row number
 */
void removeMemory(char* note, char* row);


/* 
 * Given the name of a note, removes all
 * memories from that note
 */
void clearMemories(char* note);


/* 
 * Given the name of a note and a list of words,
 * adds those words (as a single line) to
 * the end of the note
 */
void addMemory(char* note, char args[]);


/*
 * Given a the name of a note, lists the current memories
 * held by that note 
 */
void listMemories(char* notePath, char* noteName);

#include "memory.c"

