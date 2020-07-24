#!/usr/bin/env python3
# Created by Simon Camacho on
# July 24, 2020. Memory Manager
# is an application to save little
# memories for the user which can
# then be reported back at any point
# 
# @version 1.0.0: July 24, 2020
# Added basic functionality, add_memory
# clear_memories, list_memories, get_help
# and info methods. 


import sys
import os.path
from os import path


# Given a filename, removes all
# memories from that file
def clear_memories(filename):
	prompt = 'Are you sure you want to clear your current memories? There is no going back (y/n): '
	decision = input('Are you sure you want to clear your current memories? There is no going back (y/n): ')
	while (decision != 'y') and (decision != 'n'):
		decision = input('Are you sure you want to clear your current memories? There is no going back (y/n): ')
	if decision == 'y':
		open(filename, 'w').close()
		print('Memories cleared')
	elif decision == 'n':
		print('Memory clearing aborted')	


# Given a filename and a list of words,
# adds those words (as a single line) to
# the end of the file
def add_memory(filename, args):
	with open(filename, 'a') as f:
		temp_memory = '';
		for word in args:
			temp_memory += word + ' '
		memory = temp_memory.strip()
		f.write(memory)
		f.write('\n') # probably a better way to do this
		print('Remembered \'', memory, '\'', sep='')
		# add the ability to clear reminders
		# add the ability to archive reminders


# Given a filename, lists the current memories
# held by that file
def list_memories(filename):
	if (not path.isfile(filename)) or (path.getsize(filename) == 0):
		print('You have no memories currently')
		return;
	with open(filename, 'r') as f:
		for memory in f:
			if memory != '': # this isn't working quite right
				print(memory)


# Prints some help/usage information
def get_help():
	print('If you would like to add a memory, type \'remember your_memory\'')
	print('If you would like to view current memories, type \'remember --list\'')
	print('If you would like to clear your current memories, type \'remember --clear\'')


# Prints some random info about Memory Manager
def info():
	print('Memory Mananger is a simple note-taking software designed by Simon Camacho for his personal use')
	print('If you need help, type \'remember --help\'')
	# print a random quote??



def main():
	args = sys.argv[2:]
	user = sys.argv[1]
	filename = '/Users/' + user + '/.memories'
	if len(args) == 1:
		if args[0] == '--list':
			list_memories(filename)
		elif args[0] == '--clear':
			clear_memories(filename)
		elif args[0] == '--help':
			get_help()
	elif len(args) >= 1:
		add_memory(filename, args)
	else:
		info()


if __name__ == '__main__':
	main()	
