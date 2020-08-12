#!/usr/bin/env python3

import sys
import json
import os.path
from os import path
import time
from datetime import datetime
# the below imports are quicknote .py files
import memory as mem
import helper_func as hf
import note
import install


# Color Definitions
BOLD = '\033[1m'
ITALIC = '\033[3m'
RESET = '\033[0m'


"""
Returns access to the .quicknote_cache file, the .archive_notes and .notes directories
"""
def background_info():
	files = []
	# this file holds any miscellaneous information that Quick Note needs –– at the moment, just the current file
	data_file = path.expanduser('~/.quicknote/.background/data_file.json')
	# this directory holds available notes
	notes = path.expanduser('~/.quicknote/.notes')
	# this holds the name of the current note, as taken from data_file
	current_note = note.get_current_note(data_file)
	# this directory holds archived notes
	archive_notes = path.expanduser('~/.quicknote/.archive_notes')
	
	files.append(data_file)
	files.append(current_note)
	files.append(hf.read_directory(notes))
	files.append(hf.read_directory(archive_notes))
	return files


"""
Prints the user's version of Quick Note
"""
def get_version():
	print(BOLD + 'Quick Note v.1.0.18' + RESET) 


"""
Prints some help/usage information
"""
def get_help():
	get_version()
	arrow = BOLD + BLUE + '  ==>' + RESET
	print('\n', end='')
	print(BOLD + 'GENERAL' + RESET + '\n')
	print('\'Notes\' are files where we store your thoughts')
	print('\'Memories\' are the individual entries in each note\n')
	print(BOLD + 'MEMORIES' + RESET + '\n')
	print(BOLD + ITALIC + '<your_memory>' + RESET + arrow + ' for ' + BOLD + 'adding ' + RESET + 'a memory')
	print('     Usage: \'qnote Hello World!\'')
	print(BOLD + '-l' + RESET + arrow + ' for ' + BOLD + 'listing ' + RESET + 'memories on the current note')
	print('     Usage: \'qnote -l\'')
	print(BOLD + '-cl' + RESET + arrow + ' for ' + BOLD + 'clearing ' + RESET + 'memories on the current note')
	print('     Usage: \'qnote -cl\'')
	print(BOLD + '-r ' + ITALIC + '<row_number>'  + RESET + arrow + ' for ' + BOLD + 'removing ' + RESET + 'the memory at that row number in the current note (row number can be retrieved from \'' + BOLD + 'qnote -l' + RESET + '\')')
	print('     Usage: \'qnote -r 3\'')
	print(BOLD + '-m ' + ITALIC + '<row_number> <other_note_name>'  + RESET + arrow + ' for ' + BOLD + 'moving ' + RESET + 'the memory at that row number in the current note to another note')
	print('     Usage: \'qnote -m 3 shopping list\'')
	print(BOLD + '-c ' + ITALIC + '<row_number> <other_note_name>'  + RESET + arrow + ' for ' + BOLD + 'copying ' + RESET + 'the memory at that row number in the current note to another note')
	print('     Usage: \'qnote -c 3 shopping list\'\n')
	print(BOLD + 'NOTES' + RESET + '\n')
	print(BOLD + '-a ' + ITALIC + '<note_name>'  + RESET + arrow + ' for ' + BOLD + 'adding ' + RESET + 'a new note with the given name')
	print('     Usage: \'qnote -a shopping list\'')
	print(BOLD + '-ln' + RESET + arrow + ' for ' + BOLD + 'listing ' + RESET + 'current notes')
	print('     Usage: \'qnote -ln\'')
	print(BOLD + '-n' + RESET + arrow + ' for ' + BOLD + 'viewing ' + RESET + 'the name of the current note')
	print('     Usage: \'qnote -n\'')
	print(BOLD + '-ch ' + ITALIC + '<note_name>'  + RESET + arrow + ' for ' + BOLD + 'changing ' + RESET + 'to the note with the given name')
	print('     Usage: \'qnote -ch To Do\'')
	print(BOLD + '-rn ' + ITALIC + '<note_name>' + RESET + BOLD + ' / ' + ITALIC + '<new_name>' + RESET + arrow + ' for ' + BOLD + 'renaming ' + RESET + 'the given note')
	print('     Usage: \'qnote -rn To Do / Done\'')
	print(BOLD + '-rm ' + ITALIC + '<note_name>'  + RESET + arrow + ' for ' + BOLD + 'removing ' + RESET + 'the note with the given name (if no name given, removes the current note)')
	print('     Usage: \'qnote -rm To Do\'')
	print(BOLD + '-cln' + RESET + arrow + ' for ' + BOLD + 'clearing ' + RESET + 'your current notes')
	print('     Usage: \'qnote -cln\'')
	print(BOLD + '-dp' + ITALIC + ' <note_to_duplicate>' + RESET + BOLD + ' / ' + ITALIC + '<new_note_name>' + RESET + arrow + ' for ' + BOLD + 'duplicating ' + RESET + 'existing notes')
	print('     Usage: \'qnote -dp random / general\'')
	print(BOLD + '-in ' + ITALIC + '<file_to_import>' + RESET + BOLD + ' / ' + ITALIC + '<note_name>' + RESET + arrow + ' for ' + BOLD + 'importing ' + RESET + '\'.txt\' files as notes')
	print('     Usage: \'qnote -in random.txt / Assorted Tasks\'')
	print(BOLD + '-ex ' + ITALIC + '<note_to_export>' + RESET + BOLD + ' / ' + ITALIC + '<new_file_name>' + RESET + arrow + ' for ' + BOLD + 'exporting ' + RESET + 'notes as \'.txt\' files')
	print('     Usage: \'qnote -ex Assorted Tasks / nextweek\'\n')
	print(BOLD + 'ARCHIVE' + RESET)
	print(ITALIC + 'Archived notes do not receive the same functionality as regular notes. To rename, remove, export, etc. archived notes, please unarchive them first.' + RESET + '\n')
	print(BOLD + '-ar ' + ITALIC + '<note_name>'  + RESET + arrow + ' for ' + BOLD + 'archiving ' + RESET + 'the note with the given name (if no name given, archives the curent note)')
	print('     Usage: \'qnote -ar To Do\'')
	print(BOLD + '-unar ' + ITALIC + '<note_name>'  + RESET + arrow + ' for ' + BOLD + 'unarchiving ' + RESET + 'the note with the given name')
	print('     Usage: \'qnote -unar To Do\'')
	print(BOLD + '-lar' + RESET + arrow + ' for ' + BOLD + 'listing ' + RESET + 'archived notes')
	print('     Usage: \'qnote -lar\'')
	print(BOLD + '-clar' + RESET + arrow + ' for ' + BOLD + 'clearing ' + RESET + 'your archived notes')
	print('     Usage: \'qnote -clar\'')


"""
Prints some random info about Quick Note
"""
def info():
	print(BOLD + 'Quick Note' + RESET + ' is an open-source note-taking software designed for personal use.')
	print('If you need help, type \'qnote -help\'')
	print('To view your version of ' + BOLD + 'Quick Note' + RESET + ', type \'qnote -version\'\n')
	print(BOLD + 'Quick Note' + RESET + ' uses the GNU General Public License v3, so you can edit, distribute, and otherwise meddle with any of the source code.')
	print('The only thing you can\'t do is take this software and make it closed-source and try to sell it. ' + BOLD + 'Quick Note' + RESET + ' was designed to be free for everyone, forever.')


"""
Handles command line arguments and redirects to appropriate
helper functions. Should be further decomposed
"""
def main():
	# confirm that necessary .quicknote folder exists
	quicknote = path.expanduser('~/.quicknote')
	if not path.isdir(quicknote):
		install.main()

	# send_update_message()
	args = sys.argv[1:]
	files = background_info()

	data_file = files[0]
	current_note = files[1].strip('\n')
	notes = files[2]
	archive_notes = files[3]

	last_slash_index = current_note.rfind('/')	
	current_note_name = current_note[last_slash_index + 2:] 
	
	if len(args) == 0:
		info()
		return
	command = args[0]
	if command[0] == '-':
		if len(args) == 1:
			if command == '-l':
				mem.list_memories(current_note, current_note_name)
			elif command == '-cl':
				mem.clear_memories(current_note)
			elif command == '-help' or command == '-h':
				get_help()
			elif command == '-version' or command == '-v':
				get_version()
			elif command == '-ln':
				return_value = note.list_notes(notes) 
				if return_value == None:
					print('You have no notes at the moment. Start by adding a new note or by importing one from a \'.txt.\' file.')
			elif command == '-n':
				print(current_note_name)
			elif command == '-cln':
				note.clear_notes(notes, current_note_name, data_file)
			elif command == '-clar':
				note.clear_archive_notes(archive_notes)
			elif command == '-rm':
				note.remove_note(current_note_name, current_note_name, data_file)
			# this is for archiving the current note
			elif command == '-ar':
				note.archive_note(current_note_name, current_note_name, data_file)
			elif command == '-lar':
				return_value = note.list_notes(archive_notes)
				if return_value == None:
					print('You have no archived notes at the moment.')
			else:
				print('qnote error: command \'' + command + '\' not recognized. Please try again.')
				exit(1)
		elif len(args) >= 1:
			if command == '-r':
				mem.remove_memory(current_note, args[1])
			elif command == '-a':
				mem.add_note(args[1:], current_note, data_file)
			elif command == '-ch':
				note_name = note.change_note(args[1:], current_note, data_file)			
				if note_name != None:
					print('Changed current note to \'' + note_name + '\'')
			elif command == '-rn':
				note.rename_note(args[1:], current_note, data_file)
			# this is for removing any note
			elif command == '-rm':
				note.remove_note(args[1:], current_note_name, data_file)
			# this is for archiving any note
			elif command == '-ar':
				note.archive_note(args[1:], current_note_name, data_file)	
			elif command == '-unar':
				note.un_archive_note(args[1:])
			elif command == '-in':
				note.import_note(args[1:])
			elif command == '-ex':
				note.export_note(args[1:])
			elif command == '-dp':
				note.duplicate_note(args[1:])
			elif command == '-m':
				mem.move_memory(current_note, args[1], args[2:])
			elif command == '-c':
				mem.copy_memory(current_note, args[1], args[2:])
			else:
				print('qnote error: command \'' + command + '\' not recognized. Please try again.')	
				exit(1)
	else:
		mem.add_memory(current_note, args)

if __name__ == '__main__':
	main()	

