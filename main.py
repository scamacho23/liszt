#!/usr/bin/env python3

import sys
import json
import os.path
from os import path
# the below imports are quicknote .py files
import memory as mem
import helper_func as hf
import note


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
	print(BOLD + 'Quick Note v.1.0.4' + RESET) 
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
	print('If you would like to' + BOLD + ' view' + RESET + ' the current note, type \'remember --current-note\'')
	print('If you would like to' + BOLD + ' change' + RESET + ' the current note, type \'remember --change-note' + ITALIC + ' note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' rename' + RESET + ' a note, type \'remember --rename-note' + ITALIC + ' note_to_rename' + RESET + ' / ' + ITALIC + 'new_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' remove' + RESET + ' a particular note, type \'remember --remove-note' + ITALIC + ' note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' remove' + RESET + ' the current note, type \'remember --remove-note')
	print('If you would like to' + BOLD + ' clear' + RESET + ' your current notes, type \'remember --clear-notes\'')	
	print('If you would like to' + BOLD + ' import' + RESET + ' a note, type \'remember --import-note' + ITALIC + ' file_to_import' + RESET + ' / ' + ITALIC + 'note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' export' + RESET + ' a note, type \'remember --export-note' + ITALIC + ' note_to_export' + RESET + ' / ' + ITALIC + 'new_file_name' + RESET + '\'\n')
	print(BOLD + 'ARCHIVE' + RESET)
	print(ITALIC + 'Archived notes do not receive the same functionality as regular notes. To rename, remove, export, etc. archived notes, please unarchive them first.' + RESET + '\n')
	print('If you would like to' + BOLD + ' archive' + RESET + ' a particular memory, type \'remember --archive' + ITALIC + ' row_number' + RESET + '\'')
	print('If you would like to' + BOLD + ' archive' + RESET + ' a particular note, type \'remember --archive-note' + ITALIC + ' note_name' + RESET + '\'')
	print('If you would like to' + BOLD + ' archive' + RESET + ' the current note, type \'remember --archive-note\'')
	

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

	data_file = files[0]
	current_note = files[1].strip('\n')
	notes = files[2]
	archive_list = files[3]

	last_slash_index = current_note.rfind('/')	
	current_note_name = current_note[last_slash_index + 2:] 
	
	if len(args) == 0:
		info()
		return
	command = args[0]
	if len(args) == 1:
		if command == '--list':
			mem.list_memories(current_note)
		elif command == '--clear':
			mem.clear_memories(current_note)
		elif command == '--help':
			get_help()
		elif command == '--version':
			get_version()
		elif command == '--list-notes':
			note.list_notes(notes) 
		elif command == '--current-note':
			print(current_note_name)
		elif command == '--clear-notes':
			note.clear_notes(notes, current_note_name, data_file)
		# this is for removing the current note
		elif command == '--remove-note':
			print('This functionality is currently under maintenance. Please try again later.')
			return
			# note.remove_note(note.get_current_note(quicknote_cache), file_list)
		# this is for archiving the current note
		elif command == '--archive-note':
			print('This functionality is currently under maintenance. Please try again later.')
			return
			# note.archive_note(note.get_current_note(quicknote_cache), file_list)
		elif command == '--list-archive':
			print('This functionality is currently under maintenance. Please try again later.')
			return
			# note.list_archived_note(note.get_current_note(quicknote_cache), file_list)
		else:
			mem.add_memory(current_note, args)
	elif len(args) >= 1:
		if command == '--remove':
			mem.remove_memory(current_note, args[1])
		elif command == '--archive':
			mem.archive_memory(current_note, args[1])
		elif command == '--add-note':
			note.add_note(args[1:])
		elif command == '--change-note':
			note.change_note(args[1:], current_note, data_file)
		elif command == '--rename-note':
			note.rename_note(args[1:], current_note, data_file)
		# this is for removing any note
		elif command == '--remove-note':
			note.remove_note(args[1:], current_note_name, data_file)
		# this is for archiving any note
		elif command == '--archive-note':
			# note.remove_note(args[1:], file_list)	
			return
		elif command == '--import-note':
			note.import_note(args[1:])
		elif command == '--export-note':
			note.export_note(args[1:])
		else:
			mem.add_memory(current_note, args)


if __name__ == '__main__':
	main()	

