#!/usr/bin/env python3
# Created on July 30, 2020
# This file holds a number of
# helper functions used throughout
# the project

import sys
import os.path
from os import path
import json


"""
Given the path to a directory, returns a list containing
the files in that directory 
"""
def read_directory(dir_name):
	files = []
	for filename in os.listdir(dir_name):
		filename = path.join(dir_name, filename)
		if path.isfile(filename):
			last_slash_index = filename.rfind('/')	
			filename = filename[last_slash_index + 2:] 
			files.append(filename)
	return files


"""
Given a filename and a row number,
confirms that the entered row is a 
valid row number. Returns the contents 
of the note as a list 
"""
def check_row(filename, row):
	if not row.isnumeric():
		print('You have entered in a faulty row number. Please choose an integer value.')
		return
	row = float(row)	
	if not row.is_integer():
		print('You have entered in a faulty row number. Please choose an integer value.')
		return
	row = int(row)
	memories = []
	with open(filename, 'r') as f:
		memories = f.readlines()
	if row <= 0 or row > len(memories):
		print('You have entered in a faulty row number. Please try again.')
		return
	return memories


"""
Given the quicknote_cache file, changes the
default file held in quicknote_cache
"""
def write_to_data_file(data_file, filename):
	data = {}
	data['current_note'] = filename
	with open(data_file, 'w') as f:
		json.dump(data, f)
	

"""
Given a prompt, captures the user's
answer as either 'y' or 'n'
"""
def request_user_permission(prompt):
	decision = input(prompt)
	while (decision != 'y') and (decision != 'n'):
		decision = input(prompt)
	return decision


"""
Given a set of arguments,
parses them and returns the
found word
"""
def parse_unary_args(args):
	if type(args) == str:
		return args.strip()
	if len(args) == 1:
		return args[0].strip()
	word = ''
	for arg in args:
		word += arg + ' '
	return word.strip()


"""
Given a set of arguments, parses
the words to the left and right of
the '/'
"""
def parse_binary_args(args):
	if len(args) == 1 or not '/' in args:
		print('You haven\'t entered enough information. Please try again.')
		return
	old_name = ''
	new_name = ''
	counter = 0
	while (not counter >= len(args)) and (not args[counter] == '/'):
		old_name += args[counter] + ' '
		counter += 1 		
	old_name = old_name.strip()
	counter += 1
	while not counter == len(args):
		new_name += args[counter] + ' '
		counter += 1 		
	new_name = new_name.strip()
	if len(new_name) == 0:
		print('You haven\'t entered enough information. Please try again.')
		return	
	return (old_name, new_name)


"""
Given a dot_name, a filename, and the file_list,
makes a new note with that name and
adds the name to file_list
"""
def make_note(dot_name, filename):
	if path.isfile(dot_name):
		print('A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.')
		# return 0 to signify failure
		return 0
	else:
		open(dot_name, 'w+').close()

