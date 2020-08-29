#pragma once
#ifndef MEMORY_H
#define MEMORY_H
/*
 * This file contains function declarations
 * for memory manipulation for the Liszt project.
 * See memory.c for the definitions.
 */


/* 
 * Given a memory and the name of a 
 * note, appends the memory to the
 * end of the note
 */
void appendMemory(char* memory, char* note);


/* 
 * Given a row number, removes the memory 
 * at that row from a note and saves the 
 * value at that row number in the note
 */
int changeMemory(char* charRow, char* memory);


/*
 * Given the name of a note and
 * a row number, moves the memory
 * at that row number in the current
 * note to the given note
 */
void moveMemory(char* args[], int numArgs);


/*
 * Given the name of a note and
 * a row number, copies the memory
 * at that row number in the current
 * note to the given note
 */
void copyMemory(char* args[], int numArgs);


/*
 * Given a note and a row number,
 * removes the memory at that row number
 */
void removeMemory(char* row);


/* 
 * Given the name of a note, removes all
 * memories from that note
 */
void clearMemories();


/* 
 * Given the name of a note and a list of words,
 * adds those words (as a single line) to
 * the end of the note
 */
void addMemory(char* args[], int numArgs);


/*
 * Lists the memories held by the current note
 */
void listMemories();

#include "../c/memory.c"
#endif

