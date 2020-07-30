#!/usr/bin/env python3
# Created on July 24, 2020. filefunc.py
# contains the functions for adding and removing
# files for Quick Note


import sys
import os.path
from os import path
import shutil


# Color Definiitons
BOLD = '\033[1m'
RESET = '\033[0m'


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
	old_name = ''
	new_name = ''
	counter = 0
	while (not args[counter] == '/') and (not counter == len(args)):
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
		return True 
	else:
		open(dot_name, 'w+')
		with open(file_list, 'a') as f:
			f.write(filename + '\n')
		print('Added new note \'' + filename + '\'')
		return False 


"""
Given the name of a .txt file,
makes a copy of that file as a .file
to be used as a new note
"""
def import_note(args, file_list):
	pair = parse_binary_args(args)
	old_name = pair[0]
	new_name = pair[1]
	# confirm that imported file is a '.txt'; return otherwise
	if not old_name[-4:] == '.txt':
		print(BOLD + 'Quick Note' + RESET + ' only allows for the importation of \'.txt\' files as notes. Please try again.')
		return
	new_note = path.expanduser('~/.quicknote/.' + new_name)
	new_note_exists = make_note(new_note, new_name, file_list)	
	if not new_note_exists: 
		shutil.copyfile(old_name, new_note)



"""
Given the name of a note, makes a 
copy of the note which is then exported
to the user's working directory
"""
def export_note(args, file_list):
	pair = parse_binary_args(args)
	note_name = pair[0]
	filename = pair[1] + '.txt'
	files = []
	with open(file_list, 'r') as f:
		files = f.readlines()
		name_with_newline = note_name + '\n'
		# confirm that a note actually exists with the given name
		if not name_with_newline in files:
			print('There is no note with name \'' + note_name + '\'. Please try again.')
			return
	note_name = path.expanduser('~/.quicknote/.' + note_name)
	# confirm that there is not an exists '.txt' file in the working directory with the same name
	if path.isfile(filename):
		print('A file with this name already exists in your working directory. Please pick a different name.')
	else:
		open(filename, 'w+')
		shutil.copyfile(note_name, filename)
		print('Created a new file called \'' + filename + '\' in your working directory')


"""
Given the name of a note, moves the name
of the note from the .filelist file and
adds it to the .archived file
"""
def archive_note():
	pass


"""
Given a filename, adds a dot file with
the given name, which will then be set 
as the default file for memories
"""
def add_note(args, file_list):
	filename = parse_unary_args(args) 
	dot_name = path.expanduser('~/.quicknote/.' + filename)
	make_note(dot_name, filename, file_list)


"""
Prints the list of current memory files
"""
def list_notes(file_list):
	counter = 1
	if path.getsize(file_list) == 0:
		print('You have no notes at the moment. Start by adding a new note or by importing one from a \'.txt.\' file.')
		return
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
	filename_to_remove = parse_unary_args(args)
	prompt = 'Are you sure you want to remove the note \'' + filename_to_remove + '\'?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = request_user_permission(prompt)
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
			print('The note you are trying to remove does not exist. Please try again.')


"""
Clears all notes
"""
def clear_notes(file_list):
	prompt = 'Are you sure you want to clear all of your notes?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = request_user_permission(prompt)
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
	name = parse_unary_args(args)
	
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
	pair = parse_binary_args(args)
	old_name = pair[0]
	new_name = pair[1]
	old_path = path.expanduser(prefix + old_name)
	new_path = path.expanduser(prefix + new_name)
	os.rename(old_path, new_path)
	files = []
	with open(file_list, "r") as f:
		files = f.readlines()
	# confirm that the note to change actually exists
	if not old_name.strip('\n') in files:
		print('The note you are trying to rename does not exist. Please try again.')
	with open(file_list, "w") as f:
		for filename in files:
			if not filename.strip('\n') == old_name:
				f.write(filename)
		f.write(new_name + '\n')
	print('Renamed \'' + old_name + '\' to \'' + new_name + '\'')	

