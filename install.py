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
Makes an empty dot folder in the user's home directory, in which their notes will be stored
"""
def make_memory_folder():
	dir_path = path.expanduser('~/.quicknote')
	os.mkdir(dir_path)


"""
Makes a file to contain the names of all of the users note-files
"""
def make_background_files():
	file_list = path.expanduser('~/.quicknote/.filelist')
	with open(file_list, 'w+') as f:
		f.write('default')
		f.write('archive')
	quicknote_cache = path.expanduser('~/.quicknote/.quicknote_cache')
	open(quicknote_cache, 'w+')
	archive_list = path.expanduser('~/.quicknote/.archivelist')

		 
"""
Makes the default note file
and the archive note file
"""
def make_defaults():
	default_file = path.expanduser('~/.quicknote/.default')
	open(default_file, 'w+')
	archive_file = path.expanduser('~/.quicknote/.archive')
	open(archive_file, 'w+')


def main():
	args = sys.argv[1:]
	if len(args) == 0:
		make_memory_folder()
		make_background_files()
		make_defaults()
		print(BOLD + 'Quick Note' + RESET + ' installation successful')
		print('Current note set to \'default\'')
	else:
		print(BOLD + 'Quick Note' + RESET + ' installation unsuccesfful. Please try again')


if __name__ == '__main__':
	main()

