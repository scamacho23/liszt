#!/usr/bin/env python3

import sys
import os.path
from os import path

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
			else:
				memory = memory[:-1]
				print('Removed memory with name \'' + memory + '\'')
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
	if not path.isfile(filename):
		print('Hmmm. The current note doesn\'t seem to be working. Please try again later.')
		return
	elif path.getsize(filename) == 0:
		print('You have no memories on this note')
		return
	with open(filename, 'r') as f:
		counter = 1
		for memory in f:
			memory = str(counter) + '. ' + memory 
			print(memory, end='')
			counter += 1


def archive_memory(row):
	pass

