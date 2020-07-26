#!/usr/bin/env python3
# Created on July 24, 2020. remember-file.py
# contains the functions for adding and removing
# files for the Quick Note software

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
	dot_name = '/User/' + user + '/.quicknote/.' + filename 
	if path.isfile(dot_name):
		print('A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.')
		return;
	else:
		file_list = '/User/' + user + '/.quicknote/.filelist'
		open(filename, 'w+')
		with open(filename, 'a') as f:
			f.write(filename)
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
			print(filename)
			counter += 1
