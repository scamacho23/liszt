#!/usr/bin/env python3
# Created on July 24, 2020.
# note.py contains the functions 
# for note manipulation for Quick Note 


import sys
import os.path
from os import path
import helper_func as hf
import shutil


# Color Definiitons
BOLD = '\033[1m'
RESET = '\033[0m'


"""
Given the name of a .txt file,
makes a copy of that file as a .file
to be used as a new note
"""
def import_note(args, file_list):
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
	old_name = pair[0]
	new_name = pair[1]
	# confirm that imported file is a '.txt'; return otherwise
	if not old_name[-4:] == '.txt':
		print(BOLD + 'Quick Note' + RESET + ' only allows for the importation of \'.txt\' files as notes. Please try again.')
		return
	new_note = path.expanduser('~/.quicknote/.' + new_name)
	new_note_exists = hf.make_note(new_note, new_name, file_list)	
	if not new_note_exists: 
		shutil.copyfile(old_name, new_note)


"""
Given the name of a note, makes a 
copy of the note which is then exported
to the user's working directory
"""
def export_note(args, file_list):
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
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
	# confirm that there is not an existing '.txt' file in the working directory with the same name
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
	filename = hf.parse_unary_args(args) 
	dot_name = path.expanduser('~/.quicknote/.' + filename)
	hf.make_note(dot_name, filename, file_list)


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
	filename_to_remove = hf.parse_unary_args(args)
	if filename_to_remove.lower() == 'archive' or filename_to_remove.lower() == 'default':
		print('Sorry. The \'default\' and \'archive\' notes cannot be removed. However, they can be cleared!')
		return
	prompt = 'Are you sure you want to remove the note \'' + filename_to_remove + '\'?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
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
def clear_notes(file_list, current_note, quicknote_cache):
	prompt = 'Are you sure you want to clear all of your notes?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
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
		with open(file_list, 'w') as f:
			f.write('default')
			f.write('archive')
		if not current_note == 'default':	
			hf.write_to_quicknote_cache(quicknote_cache, 'default')
		print('Cleared all user notes from Quick Note cache')


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
def change_note(args, quicknote_cache, current_note):
	filename = '~/.quicknote/.'
	name = hf.parse_unary_args(args)
	# stop if the note to be changed to is the current note	
	if current_note == name:
		print('The note you are trying to change to is already the current note.')
		return

	filename += name
	filename = path.expanduser(filename)
	if not path.isfile(filename):
		print('Hmmm. The note you entered doesn\'t seem to exist. Please try again.')
		return
	
	hf.write_to_quicknote_cache(quicknote_cache, name)
	print('Changed current note to \'' + name + '\'')


"""
Given a filename, renames the file
"""
def rename_note(args, file_list, quicknote_cache):
	prefix = '~/.quicknote/.'
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
	old_name = pair[0]
	new_name = pair[1]
	old_path = path.expanduser(prefix + old_name)
	new_path = path.expanduser(prefix + new_name)
	os.rename(old_path, new_path)
	files = []
	with open(file_list, "r") as f:
		files = f.readlines()
	# confirm that the note to change actually exists
	if not (old_name + '\n') in files:
		print('The note you are trying to rename does not exist. Please try again.')
		return
	with open(file_list, "w") as f:
		for filename in files:
			if not filename.strip('\n') == old_name:
				f.write(filename)
		f.write(new_name + '\n')
	hf.write_to_quicknote_cache(quicknote_cache, new_name)
	print('Renamed \'' + old_name + '\' to \'' + new_name + '\'')	

