#!/usr/bin/env python3
# Created on July 30, 2020
# This file holds a number of
# helper functions used throughout
# the project

import sys
import os.path
from os import path


"""
Given a filename and a row number,
confirms that the entered row is a 
valid row number. Returns the contents 
of the note as a list 
"""
def check_row(filename, row):
	if not isinstance(row, int):
		print('You have entered in a faulty row number. Please choose an integer value.')
		return
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
def write_to_quicknote_cache(quicknote_cache, filename):
	cache_info = [] 
	with open(quicknote_cache, 'r') as f:
		cache_info = f.readlines()
		cache_info[0] = filename
	with open(quicknote_cache, 'w') as f:
		f.writelines(cache_info)
	

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
	if len(args) == 1:
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
	return (old_name, new_name)


"""
Given a dot_name, a filename, and the file_list,
makes a new note with that name and
adds the name to file_list
"""
def make_note(dot_name, filename, file_list):
	if path.isfile(dot_name):
		print('A note with this name already exists. Please choose a different name, delete the other note, or rename the other note.')
		return
	else:
		open(dot_name, 'w+')
		with open(file_list, 'a') as f:
			f.write(filename + '\n')
		print('Added new note \'' + filename + '\'')

