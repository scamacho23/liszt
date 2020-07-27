#!/usr/bin/env python3

import sys
import filefunc as ff
import memfunc as mf


# Color Definitions
BOLD = '\033[1m'
ITALIC = '\033[3m'
RESET = '\033[0m'


"""
Returns the name of the current working note
"""
def get_current_note(user):
	quicknote_cache = '/Users/' + user + '/.quicknote/.quicknote_cache'
	default_file = ''
	with open(quicknote_cache, 'r') as f:
		default_file = f.readline()	
	return default_file[:-1]


"""
Prints the user's version of Quick Note
"""
def get_version():
	print(BOLD + 'Quick Note v.1.0.1' + RESET) 
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
	print('If you would like to' + BOLD + ' view' + RESET + ' current notes, type \'remember --list-note\'')


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
	current_note = '/Users/' + user + '/.quicknote/.' + get_current_note(user)
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
		elif command == '--list-note':
			ff.list_files(user) 
		elif command == '--current-note':
			print(get_current_note(user))
		else:
			mf.add_memory(current_note, args)
	elif len(args) >= 1:
		if command == '--remove':
			mf.remove_memory(current_note, int(args[1])) # need to add error checking in case someone enters a faulty row number or a non-digit
		elif command == '--add-note':
				ff.add_file(user, args[1:])
		elif command == '--change-note':
				ff.change_file(user, args[1:]) 
		else:
			mf.add_memory(current_note, args)
	else:
		info()


if __name__ == '__main__':
	main()	
