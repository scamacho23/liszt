#include "note.h"
#include <stdio.h>
#include <wordexp.h>


void writeToNote(char* note, char* memories[], int numMemories) {
	FILE* toWrite;
	toWrite = fopen(note, "w");
	for (int i = 0; i < numMemories; i++) {
		fprintf(toWrite, "%s", memories[i]);
	}
	fclose(toWrite);
}


void duplicateNote(char* args[]);


void importNote(char* args[]);


void exportNote(char* args[]);


void archiveNote(char* args[], char* currentNote, char* dataFile);


void unArchiveNote(char* args[]);


void addNote(char* args[]);


int listNotes(char* notes[]);


void removeNote(char* args[], char* currentNote, char* dataFile);


void clearNotes(char* notes[], char* currentNote, char* dataFile);


void clearArchiveNotes(char* archivedNotes[]);


void getCurrentNote(char* dataFile, char* currentNote);


int changeNote(char* args[], char* currentNote, char* dataFile);


int renameNote(char* args[], char* currentNote, char* dataFile);


