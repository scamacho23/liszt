#!/usr/bin/env python3

import sys
import os.path
from os import path


"""
Given the current user, makes an empty dot folder
in their home directory, in which their notes will be stored
"""
def make_memory_folder(user):
	dir_path = '/Users/' + user + '/.quicknote'
	os.mkdir(dir_path)


"""
Given the current user, makes a file to contain
the names of all of the users note-files
"""
def make_background_files(user):
	file_list = '/Users/' + user + '/.quicknote/.filelist'
	open(file_list, 'w+')
	quicknote_cache = '/Users/' + user + '/.quicknote/.quicknote_cache'
	open(quicknote_cache, 'w+')
		 

def main():
	args = sys.argv[1:]
	if len(args) == 1:
		user = args[0]
		make_memory_folder(user)
		make_background_files(user)
	else:
		print("Quick Note installation unsuccesfful. Please try again")


if __name__ == '__main__':
	main()

