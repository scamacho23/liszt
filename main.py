#!/usr/bin/env python3

import sys
import filefunc as ff
import memfunc as mf


# Color Definitions
BOLD = '\033[1m'
ITALIC = '\033[3m'
RESET = '\033[0m'


"""
Given the user, returns a list containing
"""
def background_info(user):
	files = []
	quicknote_cache	= '/Users/' + user + '/.quicknote/.quicknote_cache'
	file_list = '/Users/' + user + '/.quicknote/.filelist'
	current_note = '/Users/' + user + '/.quicknote/.' + ff.get_current_note(quicknote_cache)
	files.append(quicknote_cache)
	files.append(file_list)
	files.append(current_note)
	return files


"""
Prints the user's version of Quick Note
"""
def get_version():
	print(BOLD + 'Quick Note v.1.0.2' + RESET) 
	print('If you would like to update, run \'brew tap scamacho23/quicknote\'')


"""
Prints some help/usage information
"""
def get_help():
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
	print('If you would like to' + BOLD + ' remove' + RESET + ' a particular note, type \'remember --remove-note' + ITALIC + ' row_number' + RESET + '\'')
	print('If you would like to' + BOLD + ' clear' + RESET + ' your current notes, type \'remember --clear-notes\'')	


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
	args = sys.argv[2:]
	user = sys.argv[1]
	files = background_info(user)

	quicknote_cache = files[0]
	file_list = files[1]
	current_note = files[2]

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
			print('This functionality has not been set up yet. Please look for the next release of ' + BOLD + 'Quick Note' + RESET)
		else:
			mf.add_memory(current_note, args)
	elif len(args) >= 1:
		if command == '--remove':
			mf.remove_memory(current_note, int(args[1])) # need to add error checking in case someone enters a faulty row number or a non-digit
		elif command == '--add-note':
				ff.add_note(user, args[1:], file_list)
		elif command == '--change-note':
				ff.change_note(user, args[1:], quicknote_cache) 
		elif command == '--rename-note':
				ff.rename_note(user, args[1:], file_list)
		elif command == '--remove-note':
			print('This functionality has not been set up yet. Please look for the next release of ' + BOLD + 'Quick Note' + RESET)
		else:
			mf.add_memory(current_note, args)
	else:
		info()


if __name__ == '__main__':
	main()	
