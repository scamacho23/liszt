#!/usr/bin/env python3
# This file installs the .quicknote
# folder in the user's home directory,
# and adds the file_list, quicknote_cache
# default and archive files to that folder

import sys
import os.path
from os import path


# Color Definitions
BOLD = '\033[1m'
RESET = '\033[0m'


"""
Makes an empty dot folder in the user's home directory, in which their notes will be stored.
Makes a folder inside of that folder, in which background Quick Note information will be stored.
"""
def make_background_folders():
	quicknote = path.expanduser('~/.quicknote')
	os.mkdir(quicknote)
	background = path.expanduser('~/.quicknote/.background')
	os.mkdir(background)
	notes = path.expanduser('~/.quicknote/.notes')
	os.mkdir(notes)
	archived_notes = path.expanduser('~/.quicknote/.archive_notes')
	os.mkdir(archived_notes)


"""
Makes a file to contain the name of the current note
"""
def make_background_files():
	prefix = path.expanduser('~/.quicknote/')
	quicknote_cache = prefix + '.background/.quicknote_cache'
	default_file = prefix + '.notes/.default'
	with open(quicknote_cache, 'w+') as f:
		f.write(default_file)
		 

"""
Makes the default note file
and the archive note file
"""
def make_defaults():
	default_note = path.expanduser('~/.quicknote/.notes/.default')
	open(default_note, 'w+')
	archive_note = path.expanduser('~/.quicknote/.notes/.archive')
	open(archive_note, 'w+')


def main():
	args = sys.argv[1:]
	if len(args) == 0:
		make_background_folders()
		make_background_files()
		make_defaults()
		print(BOLD + 'Quick Note' + RESET + ' installation successful')
		print('Current note set to \'default\'')
	else:
		print(BOLD + 'Quick Note' + RESET + ' installation unsuccesfful. Please try again')


if __name__ == '__main__':
	main()

