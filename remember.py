#!/usr/bin/env python3
import sys
import os.path
from os import path
import filefunc as ff

# Color Definitions
BOLD = '\033[1m'
ITALIC = '\033[3m'
RESET = '\033[0m'

"""
Given a filename and a row number,
removes the memory at that row number
"""
def remove_memory(filename, row):
	memories = []
	with open(filename, 'r') as f:
		counter = 1
		for memory in f:
			if row != counter:
				memories.append(memory)
			counter += 1
	with open(filename, 'w') as f:
		for memory in memories:
			f.write(memory)


"""
Given a filename, removes all
memories from that file
"""
def clear_memories(filename):
	prompt = 'Are you sure you want to clear your current memories?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = input(prompt)
	while (decision != 'y') and (decision != 'n'):
		decision = input(prompt)
	if decision == 'y':
		open(filename, 'w').close()
		print('Memories cleared')
	elif decision == 'n': # this probably isn't necessary (i.e. don't need to check, could be an else)
		print('Memory clearing aborted')	


"""
Given a filename and a list of words,
adds those words (as a single line) to
the end of the file
"""
def add_memory(filename, args):
	with open(filename, 'a') as f:
		temp_memory = ''
		for word in args:
			temp_memory += word + ' '
		memory = temp_memory.strip() + '\n'
		f.write(memory)
		print('Remembered \'', temp_memory.strip(), '\'', sep='')


"""
Given a filename, lists the current memories
held by that file
"""
def list_memories(filename):
	if (not path.isfile(filename)) or (path.getsize(filename) == 0):
		print('You have no memories currently')
		return
	with open(filename, 'r') as f:
		counter = 1
		for memory in f:
			memory = str(counter) + '. ' + memory 
			print(memory, end='')
			counter += 1


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
	filename = '/Users/' + user + '/.quicknote/.memories' # this is deprecated and needs to be fixed
	if len(args) == 1:
		command = args[0]
		if command == '--list':
			list_memories(filename)
		elif command == '--clear':
			clear_memories(filename)
		elif command == '--help':
			get_help()
		elif command == '--version':
			print('Quick Note v.1.0.1')
		elif command == '--list-note':
			ff.list_files(user) 
		else:
			add_memory(filename, args)
	elif len(args) >= 1:
		if args[0] == '--remove':
			remove_memory(filename, int(args[1])) # need to add error checking in case someone enters a faulty row number or a non-digit
		elif args[0] == '--add-note':
				ff.add_file(user, args[1:])
		else:
			add_memory(filename, args)
	else:
		info()


if __name__ == '__main__':
	main()	
