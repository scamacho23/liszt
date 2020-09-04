#pragma once
#ifndef INSTALL_H
#define INSTALL_H
/*
 * install.h holds the function declarations
 * for installing the necessary ~/.liszt directory
 * system. See install.c for the function definitions
 */


/*
 * Makes an empty dot directory called liszt in the user's home directory. Inside that directory,
 * creates three directories: "notes", "archive", and "background". Note files are stored in
 * either "notes" or "archive", while data_file.json is stored in "background".
 * Returns 0 if successful, -1 if not.
 */
int makeDirectories();


/* 
 * Creates data_file.json inside the user's ~/.liszt/background directory.
 * Creates default inside the user's ~/.liszt/notes directory
 * Returns 0 if successful, -1 if not.
 */
int makeFiles();



/*
 * Sets up the necessary Liszt directory system and files 
 * on the user's machine 
 * Returns 0 if successful, -1 if not.
 */
int install();

#include "install.c"
#endif

