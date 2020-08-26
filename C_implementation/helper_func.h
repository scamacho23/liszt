#pragma once
/*
 * This file contains function declarations 
 * for helper functions for the Liszt project.
 * See helper_func.c for the definitions.
 */


/*
 * Given two filepaths, copies the text from the
 * first file into the second file
 */
void copyFile(char* firstFile, char* secondFile);


/*
 * Given the name of a file, returns the int
 * value of the number of lines in the file
 */
int getFileSize(char* filename);


/*
 * Prints the default refusal of access command
 */
void printDefaultError();


/*
 * Given the path to a directory, populates
 * the given files array with the names of files
 * in the directory
 */
void readDirectory(char* dirName, char* files[], int* numFiles);


/*
 * Given the path to a directory, prints the names
 * of the files in that directory (not the paths)
 */
void printDirectory(char* dirName, char* shortName);

/*
 * Given a filename and a row number, 
 * confirms that the entered row is a valid row number.
 * Populates the given memories array with memories in 
 * the given note.
 * Returns 1 if successful, 0 if not
 */ 
int checkRow(char* filename, char* charRow, char* memories, int* numMemories);


/*
 * Given the data_file.json file and a filename, 
 * changes the filename held in data_file 
 */
void writeToDataFile(char* dataFile, char* filename);


/*
 * Given a prompt, captures the user's answer as either 'y' or 'n'
 */ 
void requestUserPermission(char* prompt, char* decision);


/*
 * Given an array of arguments, parses them and returns the found word
 * Returns 0 if successful, -1 if not
 */
int parseUnaryArgs(char* word, char* args[], int numArgs);


/*
 * Given a set of arguments, parses the words to the left and right of the '/'
 * Returns 0 if successful, -1 if not
 */
int parseBinaryArgs(char* first, char* second, char* args[], int numArgs);


/*
 * Given the path to a file,
 * makes a new note with that name. Returns 0 if
 * successful, returns -1 if not 
 */
int makeNote(char* filePath);

#include "helper_func.c"

