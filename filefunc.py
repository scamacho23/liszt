#!/usr/bin/env python3
# Created on July 24, 2020. filefunc.py
# contains the functions for adding and removing
# files for Quick Note


import sys
import os.path
from os import path


# Color Definiitons
BOLD = '\033[1m'
RESET = '\033[0m'


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
	dot_name = path.expanduser('~/.quicknote/.' + filename)
	if path.isfile(dot_name):
		print('A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.')
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
def remove_note(args, file_list):
	filename_to_remove = ''
	for word in args:
		filename_to_remove += word + ' '
	filename_to_remove = filename_to_remove.strip()

	prompt = 'Are you sure you want to remove the note \'' + filename_to_remove + '\'?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = input(prompt)
	while (decision != 'y') and (decision != 'n'):
		decision = input(prompt)
	if decision == 'n':
		print('Note removal aborted')
	elif decision == 'y': # this probably isn't necessary (i.e. don't need to check, could be an else)
		file_to_remove = path.expanduser('~/.quicknote/.' + filename_to_remove)
		files = []
		if path.isfile(file_to_remove):
			os.remove(file_to_remove)
			with open(file_list, "r") as f:
				files = f.readlines()
			with open(file_list, "w") as f:
				for filename in files:
					if not filename.strip('\n') == filename_to_remove:
						f.write(filename)
			print('Removed note \'' + filename_to_remove + '\'')
		else:
			print("The file does not exist")


"""
Clears all notes
"""
def clear_notes(file_list):
	prompt = 'Are you sure you want to clear all of your notes?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = input(prompt)
	while (decision != 'y') and (decision != 'n'):
		decision = input(prompt)
	if decision == 'n':
		print('Clearing of notes aborted')
	elif decision == 'y':
		filenames = []
		with open(file_list, "r") as f:
			filenames = f.readlines()
		for filename in filenames:
			filename = path.expanduser("~/.quicknote/." + filename.strip('\n'))
			if path.isfile(filename):
				os.remove(filename)
		open(file_list, "w").close()
		# Change current file in quicknote_cache?
		print('Cleared all notes from Quick Note cache')


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
	old_path = path.expanduser(prefix + old_name)
	counter += 1
	while not counter == len(args):
		new_name += args[counter] + ' '
		counter += 1 		
	new_name = new_name.strip()
	new_path = path.expanduser(prefix + new_name)
	os.rename(old_path, new_path)
	files = []
	with open(file_list, "r") as f:
		files = f.readlines()
	with open(file_list, "w") as f:
		for filename in files:
			if not filename.strip('\n') == old_name:
				f.write(filename)
		f.write(new_name + '\n')
	print('Renamed \'' + old_name + '\' to \'' + new_name + '\'')	

