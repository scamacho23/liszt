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
ITALIC = '\033[5m'
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
Given the name of a note,
duplicates that note and names
the new note the desired name
"""
def duplicate_note(args):
	pair = hf.parse_binary_args(args)
	if pair == None:
		return
	existing_note = pair[0]
	new_note = pair[1]
	existing_path = path.expanduser('~/.quicknote/.notes/.' + existing_note)
	new_path = path.expanduser('~/.quicknote/.notes/.' + new_note)
	# confirm that a note actually exists with the given name
	if not path.isfile(existing_path):
		print('There is no note called \'' + existing_note + '\'. Please try again.')
		return
	# prevent the user from duplicating default
	if existing_note == 'default':
		hf.print_default_error()
		return
	new_note_exists = hf.make_note(new_path, new_note)	
	if new_note_exists != None: 
		shutil.copyfile(existing_path, new_path)
		print('Successfully duplicated \'' + existing_note + '\' as \'' + new_note + '\'')
	else:		
		print('Could not duplicate \'' + existing_note + '\'. Please try again.')


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
	note_path = path.expanduser('~/.quicknote/.notes/.' + note_name)
	# confirm that a note actually exists with the given name
	if not path.isfile(note_path):
		print('There is no note with name \'' + note_name + '\'. Please try again.')
		return
	# prevent the user from exporting default
	if note_name == 'default':
		hf.print_default_error()
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
	# prevent the user from archiving 'default'
	if note_to_archive == 'default':
		hf.print_default_error()
		return
	new_path = path.expanduser('~/.quicknote/.archive_notes/.' + note_to_archive)
	if path.isfile(new_path):
		print('You already have an archived note named \'' + note_to_archive + '\'. Please try again. (hint: rename something)')
		return
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
	if path.isfile(new_path):
		print('You already have a note named \'' + note_to_un_archive + '\'. Please try again. (hint: rename something)')
		return
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
	return_value = hf.make_note(dot_name, note_name)
	if return_value == None:
		return
	change_note(note_name, current_note, data_file) 
	print('Added new note \'' + note_name + '\'')


"""
Prints the list of current notes
"""
def list_notes(notes):
	counter = 1
	if len(notes) == 0:
		return
	print(BOLD + ITALIC + 'Found ' + str(len(notes)) + ' notes' + RESET)
	for note in notes:
		if note != 'default':
			note = BOLD + str(counter) + '. ' + RESET + note
			print(note)	
			counter += 1
	return 0


"""
Given a filename, removes a file with that name
if it exists
"""
def remove_note(args, current_note, data_file):
	note_to_remove = hf.parse_unary_args(args)
	if note_to_remove.lower() == 'default':
		hf.print_default_error()
		return
	prompt = 'Are you sure you want to remove \'' + note_to_remove + '\'?' + BOLD + ' There is no going back (y/n): ' + RESET
	decision = hf.request_user_permission(prompt)
	if decision == 'n':
		print('Note removal aborted')
	elif decision == 'y': # this probably isn't necessary (i.e. don't need to check, could be an else)
		note_path_to_remove = path.expanduser('~/.quicknote/.notes/.' + note_to_remove)
		if path.isfile(note_path_to_remove):
			os.remove(note_path_to_remove)
			if current_note == note_to_remove:
				hf.write_to_data_file(data_file, path.expanduser('~/.quicknote/.notes/.default'))
			print('Removed note \'' + note_to_remove + '\'')
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
			if path.isfile(note_path) and note != 'default':
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
	with open(data_file, 'r') as read_from:
		data = json.load(read_from)
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
	# stop if the user is trying to change to the default note
	if note_name == 'default':
		print_default_error()
		return
	if not path.isfile(filename):
		print('Hmmm. The note you entered doesn\'t seem to exist. Please try again.')
		return
	if current_note[-7:] == 'default':
		with open(current_note, 'r') as to_read:
			memories = to_read.readlines()
			if len(memories) > 0:
				new_name = input('The current note must be named before changing notes. Please enter a name (ENTER to delete the current note): ')
				if new_name != '':
					dot_name = path.expanduser('~/.quicknote/.notes/.' + new_name)
					return_value = hf.make_note(dot_name, new_name)
				if return_value == None:
					return
				shutil.copyfile(current_note, dot_name)
				open(current_note, 'w').close()	
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
	# prevent the user from renaming 'default'
	if old_name == 'default':
		print_default_error()
		return
	os.rename(old_path, new_path)
	if old_path == current_note:
		hf.write_to_data_file(data_file, new_path)
	print('Renamed \'' + old_name + '\' to \'' + new_name + '\'')	

