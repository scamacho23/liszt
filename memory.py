#!/usr/bin/env python3

import sys
import os.path
from os import path
import note
import helper_func as hf

# Color Definitions
BOLD = '\033[1m'
ITALIC = '\033[3m'
RESET = '\033[0m'


"""
Given a memory and the name of a 
note, appends the memory to the
end of the note
"""
def append_memory(memory, note):
	with open(note, 'a') as f:
		memory += '\n'
		f.write(memory)


"""
Given the current_note and a row number,
removes the memory at that row and returns
its value
"""
def change_memory(current_note, row):
	memories = hf.check_row(current_note, row)	
	if memories == None:
		return
	row = int(row)
	memory_to_remove = memories[row - 1].strip('\n')
	del memories[row - 1]
	note.write_to_note(current_note, memories)
	return memory_to_remove


"""
Given the name of a note and
a row number, moves the memory
at that row number in the current
note to the given note
"""
def move_memory(current_note, row, args):
	note = hf.parse_unary_args(args)
	note_path = path.expanduser('~/.quicknote/.notes/.' + note)
	if not path.isfile(note_path):
		print('The note you are trying to add to does not exist. Please try again.')	
		return
	memory_to_move = change_memory(current_note, row)	
	if memory_to_move == None:
		return
	append_memory(memory_to_move, note_path)
	print('Moved \'' + memory_to_move + '\' to \'' + note + '\'')
		

"""
Given the name of a note and
a row number, copies the memory
at that row number in the current
note to the given note
"""
def copy_memory(current_note, row, args):
	note = hf.parse_unary_args(args)
	note_path = path.expanduser('~/.quicknote/.notes/.' + note)
	if not path.isfile(note_path):
		print('The note you are trying to add to does not exist. Please try again.')
		return
	memories = hf.check_row(current_note, row)	
	if memories == None:
		return
	row = int(row)
	memory_to_copy = memories[row - 1].strip('\n')
	append_memory(memory_to_copy, note_path)
	print('Copied \'' + memory_to_copy + '\' to \'' + note + '\'')


"""
Given a note and a row number,
removes the memory at that row number
"""
def remove_memory(note, row):
	if not path.isfile(note):
		return
	memory_to_remove = change_memory(note, row)	
	if memory_to_remove == None:
		return
	print('Removed memory \'' + memory_to_remove + '\'')


"""
Given a filename, removes all
memories from that file
"""
def clear_memories(filename):
	prompt = 'Are you sure you want to clear your current memories on this note?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
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
def add_memory(note, args):
	memory = hf.parse_unary_args(args)
	append_memory(memory, note)
	print('Remembered \'' + memory + '\'')


"""
Given a filename, lists the current memories
held by that file
"""
def list_memories(filename):
	if not path.isfile(filename):
		print('Hmmm. The current note doesn\'t seem to be working. Please try again later.')
		print('If the current note continues to fail to open, please submit a help ticket by emailing us at quicknote.v1@gmail.com')
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


"""
Given a row number, removes the
memory at that row and adds it to
the '.archive' memory file
"""
def archive_memory(filename, row):
	archive_note = path.expanduser('~/.quicknote/.notes/.archive')
	memories = hf.check_row(filename, row)
	if memories == None:
		return
	row = int(row)
	memory_to_archive = memories[row - 1]
	del memories[row - 1]
	with open(filename, 'w') as f:
		for memory in memories:
			f.write(memory)
	with open(archive_note, 'a') as f:
		f.write(memory_to_archive)
	print('Archived memory \'' + memory_to_archive.strip('\n') + '\'')

