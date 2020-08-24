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


void removeNote(char* args[], char* currentNote, char* dataFile);


void clearNotes(char* notes[], char* currentNote, char* dataFile) {
	char prompt[] = "Are you sure you want to clear all of your notes?\033[1m There is no going back (y/n): \033[0m";
	char decision[50];
	requestUserPermission(prompt, decision)
	if (strcmp(decision, "y") == 0) {
		// DELETE NOTES
	} else printf("Clearing of notes aborted");
		//for note in notes:
			//note_path = path.expanduser('~/.quicknote/.notes/.' + note)
			//if path.isfile(note_path) and note != 'default':
			//	os.remove(note_path)
		//if current_note != 'default':
			//hf.write_to_data_file(data_file, path.expanduser('~/.quicknote/.notes/.default'))
		//print('Cleared all user notes from Quick Note cache')


}


void clearArchiveNotes(char* archivedNotes[]);


void getCurrentNote(char* dataFile, char* currentNotePath, char* currentNoteName) {
	FILE* toRead;
	toRead = fopen(dataFile, "r");
	fscanf(toRead, "%s", currentNotePath);
	fclose(toRead);
	
	int counter = 0; // for counting the number of slashes passed
	int index = 0; // for counting the index in the string
	int pathLength = strlen(currentNotePath);
	while (counter < 5 && index < pathLength) {
		if (currentNotePath[index] == '/') {
			counter++; 
		}
		index++;
	}
	strncat(currentNoteName, currentNotePath + index, pathLength - index);

}	
	


int changeNote(char* args[], char* currentNote, char* dataFile);


int renameNote(char* args[], char* currentNote, char* dataFile);


