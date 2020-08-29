#pragma once
/*
 * This file contains function declarations 
 * for helper functions for the Liszt project.
 * See helper_func.c for the definitions.
 */


/*
 * Given the name of a faulty command,
 * exits the program with a 1 error code
 * and prints some help information
 * to the console
 */
void sendErrorMessage(char* command);


/*
 * Checks to see if the necessary directory
 * and file system for Liszt functionality
 * has been installed on the user's machine.
 * If not, attempts to install the system.
 * If installation is unsuccessful, exits
 * the program with an error code of 1.
 */
void checkInstallation();


/*
 * Prints the name of the current note
 * to the console
 */
void printCurrentNoteName();


/*
 * Fills the given currentNoteName char array
 * with the name of the current note name 
 */
void getCurrentNoteName(char* currentNoteName);


/*
 * Fills the given currentNotePath char array
 * with the name of the current note path
 */
void getCurrentNotePath(char* currentNotePath);


/*
 * Returns the name and path of the current working note
 */
void getCurrentNote(char* currentNotePath, char* currentNoteName);


/*
 * Sets the current note to 'default'
 */
void setToDefault();


/*
 * Finds the path to the data_file
 */
void getDataFile(char* dataFile); 


/*
 * Given the dir in which a note is located,
 * either ~/.liszt/notes or ~/.liszt/archive,
 * finds the full path to the note 
 */
void getNotePath(char* dirName, char* noteName, char* notePath);


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
 * Given the name of a note, checks if it
 * is default.
 * Returns 0 if note is note default, -1 if it is
 */
int checkDefault(char* note);


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
 * Returns 0 if successful, -1 if not
 */ 
int checkRow(char* filename, char* charRow);


/*
 * Given the data_file.json file and a filename, 
 * changes the filename held in data_file 
 */
void writeToDataFile(char* filename);


/*
 * Given a prompt, captures the user's answer as either 'y' or 'n'
 */ 
void requestUserPermission(char* prompt, char* decision);


/*
 * Given an array of arguments, parses them and returns the found row and word
 * note name
 * Returns 0 if successful, -1 if not
 */
int parseSpecialArgs(char* filename, char* args[], int numArgs);


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

