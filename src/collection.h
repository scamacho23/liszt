#pragma once
#ifndef COLLECTION_H
#define COLLECTION_H
/* collection.h contains the function declarations necessary
 * for manipulating collections of notes in the Liszt project.
 * See collection.c for the function definitions.
 */


/*
 * Lists the available user collections,
 * including 'main' but not 'archive'
 */
void listCollections();


/*
 * Adds a directory inside of ~/.liszt,
 * which will hold notes for the user
 */
void addCollection(char* args[], int numArgs);


/*
 * Given the name of another collection,
 * changes to that collection
 */
void changeCollection(char* args[], int numArgs);


/*
 * Given the name of a collection, removes
 * that collection
 */
void removeCollection(char* args[], int numArgs);


/*
 * Given the name of a collection and a new 
 * name, renames that collection
 */
void renameCollection(char* args[], int numArgs);


/*
 * Clears all user collections besides 'main'
 */
void clearCollections();


/*
 * Given a directory holding .txt files,
 * imports that directory as a collection 
 */
void importCollection(char* args[], int numArgs);


/*
 * Exports a collection as a directory of txt files
 */
void exportCollection(char* args[], int numArgs);


/*
 * Compresses a collection to a zipfile
 */
void compressCollection(char* args[], int numArgs);


#include "collection.c"
#endif

