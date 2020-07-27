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
def add_file(user, args):
	filename = ''
	for word in args:
		filename += word + ' '
	filename = filename.strip()
	dot_name = '/Users/' + user + '/.quicknote/.' + filename 
	if path.isfile(dot_name):
		print('A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.')
		return;
	else:
		file_list = '/Users/' + user + '/.quicknote/.filelist'
		open(dot_name, 'w+')
		with open(file_list, 'a') as f:
			f.write(filename + '\n')
		print('Added new note with name \'' + filename + '\'')


"""
Prints the list of current memory files
"""
def list_files(user):
	counter = 1
	file_path = '/Users/' + user + '/.quicknote/.filelist'
	with open(file_path, 'r') as f:
		for filename in f:
			filename = str(counter) + '. ' + filename
			print(filename, end='')
			counter += 1


"""
Given a filename, removes a file with that name
if it exists
"""
def remove_file(user, filename):
	pass	


"""
Clears all notes
"""
def clear_files(user):
	pass


"""
Given the user and a filename, changes the current note to 
the filename
"""
def change_file(user, args):
	# what if they are trying to change to the current note –– cut it off
	filename = '/Users/' + user + '/.quicknote/.'
	name = ''
	for word in args:
		name += word + ' '
	name = name.strip()
	filename += name
	if not path.isfile(filename):
		print('Hmmm. The note you entered doesn\'t seem to exist. Please try again.')
		return
	quicknote_cache = '/Users/' + user + '/.quicknote/.quicknote_cache'
	cache_info = ''
	with open(quicknote_cache, 'r') as f:
		cache_info = f.readlines()
		cache_info[0] = filename
	with open(quicknote_cache, 'w') as f:
		f.writelines(cache_info)	
	print('Changed current note to \'' + name + '\'')


