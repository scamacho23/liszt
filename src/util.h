#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H
/*
 * This file contains function declarations 
 * for helper functions for the Liszt project.
 * See helper_func.c for the definitions.
 */


typedef struct {
	char *first;
	char *second;
} pair_t;


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
 * Returns the name and path of the current working note
 */
char *getCurrentNote(char** currentNotePath);


/*
 * Fills the given currentNotePath char array
 * with the name of the current note path
 */
char *getCurrentNotePath();


/*
 * Sets the current note to 'default'
 */
void setToDefault();


/*
 * Finds the path to the data_file
 */
char *getDataFile(); 


/*
 * Given the dir in which a note is located,
 * either ~/.liszt/notes or ~/.liszt/archive,
 * finds the full path to the note 
 */
char *getNotePath(char* dirName, char* noteName);


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
 * Given the path to a directory, prints the names
 * of the files in that directory (not the paths)
 */
void printDirectory(char* dirName, char* shortName);

/*
 * Given a filename and a row number, 
 * confirms that the entered row is a valid row number.
 * Returns 0 if successful, -1 if not
 */ 
long checkRow(char* filename, char* charRow);


/*
 * Given the data_file.json file and a filename and a
 * dirname, overwrites the existing data_file.json 
 */
void overwriteFilenameToDataFile(char* filename, char* dirname);


/*
 * Given the data_file.json file and a filename, 
 * changes the filename held in data_file 
 */
void writeFilenameToDataFile(char* filename);


/*
 * Given a prompt, captures the user's answer as either 'y' or 'n'
 */ 
void requestUserPermission(char* prompt, char* decision);


/*
 * Given an array of arguments, parses them and returns the found row and word
 * note name
 * Returns 0 if successful, -1 if not
 */
char *parseSpecialArgs(char* args[], int numArgs);


/*
 * Given an array of arguments, parses them and returns the found word
 * Returns 0 if successful, -1 if not
 */
char *parseUnaryArgs(char* args[], int numArgs);


/*
 * Given a set of arguments, parses the words to the left and right of the '/'
 * Returns 0 if successful, -1 if not
 */
int parseBinaryArgs(pair_t *notes, char* args[], int numArgs);


/*
 * Given the path to a file,
 * makes a new note with that name. Returns 0 if
 * successful, returns -1 if not 
 */
int makeNote(char* filePath);

#include "util.c"
#endif

