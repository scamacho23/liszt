#!/usr/bin/env python3

import sys
import os.path
from os import path


"""
Given the current user, makes an empty dot folder
in their home directory, in which their notes will be stored
"""
def make_memory_folder():
	dir_path = '~/.quicknote'
	dir_path = path.expanduser(dir_path)
	os.mkdir(dir_path)


"""
Given the current user, makes a file to contain
the names of all of the users note-files
"""
def make_background_files():
	file_list = '~/.quicknote/.filelist'
	file_list = path.expanduser(file_list)
	open(file_list, 'w+')
	quicknote_cache = '~/.quicknote/.quicknote_cache'
	quicknote_cache = path.expanduser(quicknote_cache)
	open(quicknote_cache, 'w+')
		 

def main():
	args = sys.argv[1:]
	if len(args) == 0:
		make_memory_folder()
		make_background_files()
	else:
		print("Quick Note installation unsuccesfful. Please try again")


if __name__ == '__main__':
	main()

