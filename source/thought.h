#pragma once
#ifndef THOUGHT_H
#define THOUGHT_H
/*
 * This file contains function declarations
 * for thought manipulation for the Liszt project.
 * See thought.c for the definitions.
 */


/* 
 * Given a thought and the name of a 
 * note, appends the thought to the
 * end of the note
 */
void appendThought(char* thought, char* note);


/* 
 * Given a row number, removes the thought 
 * at that row from a note and saves the 
 * value at that row number in the note
 */
int changeThought(char* charRow, char* thought);


/*
 * Given the name of a note and
 * a row number, moves the thought
 * at that row number in the current
 * note to the given note
 */
void moveThought(char* args[], int numArgs);


/*
 * Given the name of a note and
 * a row number, copies the thought
 * at that row number in the current
 * note to the given note
 */
void copyThought(char* args[], int numArgs);


/*
 * Given a note and a row number,
 * removes the thought at that row number
 */
void removeThought(char* row);


/* 
 * Given the name of a note, removes all
 * thoughts from that note
 */
void clearThoughts();


/* 
 * Given the name of a note and a list of words,
 * adds those words (as a single line) to
 * the end of the note
 */
void addThought(char* args[], int numArgs);


/*
 * Lists the thoughts held by the current note
 */
void listThoughts();

#include "thought.c"
#endif

