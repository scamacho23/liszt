#!/usr/bin/env python3
# Created on July 24, 2020.
# note.py contains the functions 
# for note manipulation for Quick Note 


import sys
import os.path
from os import path
import json
import shutil
import helper_func as hf


# Color Definiitons
BOLD = '\033[1m'
RESET = '\033[0m'


"""
Given the name of a note
and a list of memories, 
adds all the memories to the
note
"""
def write_to_note(note, memories):
	with open(note, 'w') as to_write:
		for memory in memories:
			to_write.write(memory)


"""
Given the name of a .txt file,
makes a copy of that file as a .file
to be used as a new note
"""
def import_note(args):
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
	import_name = pair[0]
	note_name = pair[1]
	# confirm that imported file is a '.txt'; return otherwise
	if import_name[-4:] != '.txt':
		print(BOLD + 'Quick Note' + RESET + ' only allows for the importation of \'.txt\' files as notes. Please try again.')
		return
	new_note = path.expanduser('~/.quicknote/.notes/.' + note_name)
	new_note_exists = hf.make_note(new_note, note_name)	
	if new_note_exists != 0: 
		shutil.copyfile(import_name, new_note)
		print('Successfully imported \'' + import_name + '\' as \'' + note_name + '\'')
	else:		
		print('Could not import \'' + import_name + '\'. Please try again.')


"""
Given the name of a note, makes a 
copy of the note which is then exported
to the user's working directory
"""
def export_note(args):
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
	note_name = pair[0]
	filename = pair[1] + '.txt'
	files = []
	note_path = path.expanduser('~/.quicknote/.notes/.' + note_name)
	# confirm that a note actually exists with the given name
	if not path.isfile(note_path):
		print('There is no note with name \'' + note_name + '\'. Please try again.')
		return
	# confirm that there is not an existing '.txt' file in the working directory with the same name
	if path.isfile(filename):
		print('A file with this name already exists in your working directory. Please pick a different name.')
	else:
		open(filename, 'w+')
		shutil.copyfile(note_path, filename)
		print('Created a new file called \'' + filename + '\' in your working directory')


"""
Given the name of a note, moves the note
rom the .notes directory and add it to the
.archive_notes directory 
"""
def archive_note(args, current_note, data_file):
	note_to_archive = hf.parse_unary_args(args)
	note_path = path.expanduser('~/.quicknote/.notes/.' + note_to_archive)
	
	if not path.isfile(note_path):
		print('The note you are trying to archive does not exist. Please try again.')	
		return
	# prevent the user from archiving 'archive' or 'default'
	if note_to_archive == 'archive' or note_to_archive == 'default':
		print('\'archive\' and \'default\' may not be archived. Please try again.')
		return
	new_path = path.expanduser('~/.quicknote/.archive_notes/.' + note_to_archive)
	os.rename(note_path, new_path) 
	print('Archived \'' + note_to_archive + '\'')
	if current_note != 'default':
				hf.write_to_data_file(data_file, path.expanduser('~/.quicknote/.notes/.default'))


"""
Given the name of a note, moves the note
from the .archive_notes directory to the
.notes directory.
"""
def un_archive_note(args):
	note_to_un_archive = hf.parse_unary_args(args)
	note_path = path.expanduser('~/.quicknote/.archive_notes/.' + note_to_un_archive)
	
	if not path.isfile(note_path):
		print('The note you are trying to un-archive does not exist. Please try again.')	
		return
	new_path = path.expanduser('~/.quicknote/.notes/.' + note_to_un_archive)
	os.rename(note_path, new_path) 
	print('Un-archived \'' + note_to_un_archive + '\'')


"""
Given a filename, adds a dot file with
the given name, which will then be set 
as the default file for memories
"""
def add_note(args):
	note_name = hf.parse_unary_args(args) 
	dot_name = path.expanduser('~/.quicknote/.notes/.' + note_name)
	hf.make_note(dot_name, note_name)
	print('Added new note \'' + note_name + '\'')


"""
Prints the list of current notes
"""
def list_notes(notes):
	counter = 1
	if len(notes) == 0:
		print('You have no notes at the moment. Start by adding a new note or by importing one from a \'.txt.\' file.')
		return
	print('Found ' + str(len(notes)) + ' notes')
	for note in notes:
		note = str(counter) + '. ' + note
		print(note)	
		counter += 1


"""
Prints the list of archived notes  
"""
def list_archive_notes(archive_notes): # this is a complete copy of list_notes, so maybe just delete and use list_notes
	counter = 1
	if len(archive_notes) == 0:
		print('You have no archived notes at the moment.')
		return
	print('Found ' + str(len(archive_notes)) + ' archived note(s)')
	for note in archive_notes:
		note = str(counter) + '. ' + note
		print(note)	
		counter += 1


"""
Given a filename, removes a file with that name
if it exists
"""
def remove_note(args, current_note, data_file):
	filename_to_remove = hf.parse_unary_args(args)
	if filename_to_remove.lower() == 'archive' or filename_to_remove.lower() == 'default':
		print('Sorry. The \'default\' and \'archive\' notes cannot be removed. However, they can be cleared of their contents.')
		return
	prompt = 'Are you sure you want to remove the note \'' + filename_to_remove + '\'?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
	if decision == 'n':
		print('Note removal aborted')
	elif decision == 'y': # this probably isn't necessary (i.e. don't need to check, could be an else)
		file_to_remove = path.expanduser('~/.quicknote/.notes/.' + filename_to_remove)
		files = []
		if path.isfile(file_to_remove):
			os.remove(file_to_remove)
			if current_note != 'default':
				hf.write_to_data_file(data_file, path.expanduser('~/.quicknote/.notes/.default'))
			print('Removed note \'' + filename_to_remove + '\'')
		else:
			print('The note you are trying to remove does not exist. Please try again.')


"""
Clears all available notes besides 'archive' and 'default'
"""
def clear_notes(notes, current_note, data_file):
	prompt = 'Are you sure you want to clear all of your notes?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
	if decision == 'n':
		print('Clearing of notes aborted')
	elif decision == 'y':
		for note in notes:
			note_path = path.expanduser('~/.quicknote/.notes/.' + note)
			if path.isfile(note_path) and (note != 'archive' and note != 'default'):
				os.remove(note_path)
		if current_note != 'default':
			hf.write_to_data_file(data_file, path.expanduser('~/.quicknote/.notes/.default'))
		print('Cleared all user notes from Quick Note cache')


"""
Clears all archived notes
"""
def clear_archive_notes(archive_notes):
	prompt = 'Are you sure you want to clear all of your archived notes?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
	if decision == 'n':
		print('Clearing of archived notes aborted')
	elif decision == 'y':
		for note in archive_notes:
			note_path = path.expanduser('~/.quicknote/.archive_notes/.' + note)
			if path.isfile(note_path):
				os.remove(note_path)
		print('Cleared all archived user notes from Quick Note cache')


"""
Returns the name of the current working note
"""
def get_current_note(data_file):
	with open(data_file, 'r') as f:
		data = json.load(f)
		return data['current_note'] 


"""
Given the user and a filename, changes the current note to 
the filename
"""
def change_note(args, current_note, data_file):
	filename = '~/.quicknote/.notes/.'
	note_name = hf.parse_unary_args(args)
	filename += note_name
	filename = path.expanduser(filename)
	# stop if the note to be changed to is the current note	
	if current_note == filename:
		print('The note you are trying to change to is already the current note.')
		return

	if not path.isfile(filename):
		print('Hmmm. The note you entered doesn\'t seem to exist. Please try again.')
		return
	
	hf.write_to_data_file(data_file, filename)
	print('Changed current note to \'' + note_name + '\'')


"""
Given a filename, renames the file
"""
def rename_note(args, current_note, data_file):
	prefix = '~/.quicknote/.notes/.'
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
	old_name = pair[0]
	new_name = pair[1]
	old_path = path.expanduser(prefix + old_name)
	new_path = path.expanduser(prefix + new_name)
	# confirm that the note to change actually exists
	if not path.isfile(old_path):
		print('The note you are trying to rename does not exist. Please try again.')
		return
	# prevent the user from renaming 'archive' or 'default'
	if old_name == 'archive' or old_name == 'default':
		print('\'archive\' and \'default\' are reserved names. Please try again.')
		return
	os.rename(old_path, new_path)
	counter = 0
	if old_path == current_note:
		hf.write_to_quicknote_cache(data_file, new_path)
	print('Renamed \'' + old_name + '\' to \'' + new_name + '\'')	

