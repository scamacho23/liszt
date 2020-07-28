#!/usr/bin/env python3
# Created on July 24, 2020. filefunc.py
# contains the functions for adding and removing
# files for Quick Note


import sys
import os.path
from os import path


"""
Given a filename, adds a dot file with
the given name, which will then be set 
as the default file for memories
"""
def add_note(args, file_list):
	filename = ''
	for word in args:
		filename += word + ' '
	filename = filename.strip()
	dot_name = '~/.quicknote/.' + filename 
	dot_name = path.expanduser(dot_name)
	if path.isfile(dot_name):
		print('A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.')
		return;
	else:
		open(dot_name, 'w+')
		with open(file_list, 'a') as f:
			f.write(filename + '\n')
		print('Added new note with name \'' + filename + '\'')


"""
Prints the list of current memory files
"""
def list_notes(file_list):
	counter = 1
	with open(file_list, 'r') as f:
		for filename in f:
			filename = str(counter) + '. ' + filename
			print(filename, end='')
			counter += 1


"""
Given a filename, removes a file with that name
if it exists
"""
def remove_note(filename):
	pass	


"""
Clears all notes
"""
def clear_notes():
	pass


"""
Returns the name of the current working note
"""
def get_current_note(quicknote_cache):
	default_file = ''
	with open(quicknote_cache, 'r') as f:
		return f.readline()


"""
Given the user and a filename, changes the current note to 
the filename
"""
def change_note(args, quicknote_cache):
	filename = '~/.quicknote/.'
	name = ''
	for word in args:
		name += word + ' '
	name = name.strip()
	
	with open(quicknote_cache, 'r') as f:
		if f.readline() == name:
			print('The note you are trying to change to is already the default.')
			return

	filename += name
	filename = path.expanduser(filename)
	if not path.isfile(filename):
		print('Hmmm. The note you entered doesn\'t seem to exist. Please try again.')
		return

	cache_info = ''
	with open(quicknote_cache, 'r') as f:
		cache_info = f.readlines()
		cache_info[0] = name
	with open(quicknote_cache, 'w') as f:
		f.writelines(cache_info)	
	print('Changed current note to \'' + name + '\'')


"""
Given a filename, renames the file
"""
def rename_note(args, file_list):
	prefix = '~/.quicknote/.'
	old_name = ''
	new_name = ''
	counter = 0
	while (not args[counter] == '/') and (not counter == len(args)):
		old_name += args[counter] + ' '
		counter += 1 		
	old_name = old_name.strip()
	old_path = prefix + old_name
	old_path = path.expanduser(old_path)
	counter += 1
	while not counter == len(args):
		new_name += args[counter] + ' '
		counter += 1 		
	new_name = new_name.strip()
	new_path = prefix + new_name
	new_path = path.expanduser(new_path)
	os.rename(old_path, new_path)
	index = 0
	with open(file_list, 'r') as f:
		for filename in f:
			if filename[-1] == '\n':
				filename = filename[:-1]
			if filename == old_name:
				break 
			else:
				index += 1
	files = []
	with open(file_list, 'r') as f:
		files = f.readlines()
		files[index] = new_name
	with open(file_list, 'w') as f:
		f.writelines(files)	
	
	print('Renamed \'' + old_name + '\' to \'' + new_name + '\'')	

