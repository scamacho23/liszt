#pragma once
#ifndef PARSE_H
#define PARSE_H
/*
 * This file contains function declarations 
 * for parsing functions for the Liszt project.
 * See parse.c for the definitions.
 */


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


#include "parse.c"
#endif

