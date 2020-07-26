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
def make_file_list(user):
	file_path = '/Users/' + user + '/.quicknote/.filelist'
	open(file_path, 'w+')
		 

def main():
	args = sys.argv[1:]
	if len(args) == 1:
		user = args[0]
		make_memory_folder(user)
		make_file_list(user)
	else:
		print("Quick Note installation unsuccesfful. Please try again")


if __name__ == '__main__':
	main()

