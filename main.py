#!/usr/bin/env python3

import sys
import filefunc as ff
import memfunc as mf
import os.path
from os import path


# Color Definitions
BOLD = '\033[1m'
ITALIC = '\033[3m'
RESET = '\033[0m'


"""
Given the user, returns a list containing
"""
def background_info():
	files = []
	quicknote_cache = path.expanduser('~/.quicknote/.quicknote_cache')
	file_list = path.expanduser('~/.quicknote/.filelist')
	current_note = path.expanduser('~/.quicknote/.' + ff.get_current_note(quicknote_cache))
	files.append(quicknote_cache)
	files.append(file_list)
	files.append(current_note)
	return files


"""
Prints the user's version of Quick Note
"""
def get_version():
	print(BOLD + 'Quick Note v.1.0.3' + RESET) 
	print('If you would like to update, run \'brew tap scamacho23/quicknote\'')


"""
Prints some help/usage information
"""
def get_help():
	get_version()
	print('\n', end='')
	print(BOLD + 'GENERAL' + RESET + '\n')
	print('\'Notes\' are files where we store your thoughts')
	print('\'Memories\' are the individual entries in each note\n')
	print(BOLD + 'MEMORIES' + RESET + '\n')
	print('If you would like to' + BOLD + ' add' + RESET + ' a memory, type \'remember' + ITALIC + ' your_memory' + RESET + '\'')
	print('If you would like to' + BOLD + ' view' + RESET + ' current memories, type \'remember --list\'')
	print('If you would like to' + BOLD + ' clear' + RESET + ' your current memories, type \'remember --clear\'')	
	print('If you would like to' + BOLD + ' remove' + RESET + ' a particular memory, type \'remember --remove' + ITALIC + ' row_number' + RESET + '\'\n')
	print(BOLD + 'NOTES' + RESET + '\n')
	print('If you would like to' + BOLD + ' add' + RESET + ' a note, type \'remember --add-note' + ITALIC + ' note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' view' + RESET + ' current notes, type \'remember --list-notes\'')
	print('If you would like to' + BOLD + ' view' + RESET + ' the default note, type \'remember --current-note\'')
	print('If you would like to' + BOLD + ' change' + RESET + ' the default note, type \'remember --change-note' + ITALIC + ' note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' rename' + RESET + ' a note, type \'remember --rename-note' + ITALIC + ' note_to_rename' + RESET + ' / ' + ITALIC + 'new_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' remove' + RESET + ' a particular note, type \'remember --remove-note' + ITALIC + ' note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' remove' + RESET + ' the current note, type \'remember --remove-note')
	print('If you would like to' + BOLD + ' clear' + RESET + ' your current notes, type \'remember --clear-notes\'')	
	print('If you would like to' + BOLD + ' import' + RESET + ' a note, type \'remember --import-note' + ITALIC + ' file_to_import' + RESET + ' / ' + ITALIC + 'note_name' + RESET + '\'')


"""
Prints some random info about Quick Note
"""
def info():
	print(BOLD + 'Quick Note' + RESET + ' is an open-source note-taking software designed for personal use')
	print('If you need help, type \'remember --help\'')
	# print a random quote??

"""
Handles command line arguments and redirects to appropriate
helper functions. Should be further decomposed
"""
def main():
	args = sys.argv[1:]
	files = background_info()

	quicknote_cache = files[0]
	file_list = files[1]
	current_note = files[2]
	
	# removing unwanted new-line characters
	if quicknote_cache[-1] == '\n':
		quicknote_cache == quicknote_cache[:-1]
	if file_list[-1] == '\n':
		file_list == file_list[:-1]
	if current_note[-1] == '\n':
		current_note == current_note[:-1]
	if len(args) == 0:
		info()
		return
	command = args[0]
	if len(args) == 1:
		if command == '--list':
			mf.list_memories(current_note)
		elif command == '--clear':
			mf.clear_memories(current_note)
		elif command == '--help':
			get_help()
		elif command == '--version':
			get_version()
		elif command == '--list-notes':
			ff.list_notes(file_list) 
		elif command == '--current-note':
			print(ff.get_current_note(quicknote_cache))
		elif command == '--clear-notes':
			ff.clear_notes(file_list)
		# this is for removing the default note
		elif command == '--remove-note':
			print('This functionality is currently under maintenance. Please try again later.')
			return
			ff.remove_note(ff.get_current_note(quicknote_cache), file_list)
		else:
			mf.add_memory(current_note, args)
	elif len(args) >= 1:
		if command == '--remove':
			mf.remove_memory(current_note, int(args[1])) # need to add error checking in case someone enters a faulty row number or a non-digit
		elif command == '--add-note':
			ff.add_note(args[1:], file_list)
		elif command == '--change-note':
			ff.change_note(args[1:], quicknote_cache)
		elif command == '--rename-note':
			ff.rename_note(args[1:], file_list)
		# this is for removing any note
		elif command == '--remove-note':
			ff.remove_note(args[1:], file_list)	
		elif command == '--import-note':
			ff.import_note(args[1:], file_list)
		else:
			mf.add_memory(current_note, args)


if __name__ == '__main__':
	main()	
