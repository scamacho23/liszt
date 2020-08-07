#!/usr/bin/env python3
# Created on July 30, 2020
# This file holds a number of
# helper functions used throughout
# the project

import json
import os.path
from datetime import datetime
from os import path


def print_default_error():
    """
    Prints the default refusal of access command

    Parameters
    ----------
    None

    Returns
    -------
    None
    """	
    print('Sorry. \'default\' is off limits.')


def save_datetime(data_file):
    """
    Given the data_file, saves the current datetime to the data_file

    Parameters
    ----------
    data_file : str
        Name of the file

    Returns
    -------
    None
    """
    data = {}
    with open(data_file, 'r') as read_from:
        data = json.load(read_from)
    data['last_update_date'] = datetime.now()
    with open(data_file, 'w') as write_to:
        json.dump(data, write_to)


def get_last_update_date(data_file):
    """
    Given the data_file, returns the last update date of Quick Note on the user's machine

    Parameters
    ----------
    data_file: str
        Name of the file

    Returns
    -------
    str
        The last update date of Quick Note on the user's machine
    """
    data = {}
    with open(data_file, 'r') as read_from:
        data = json.load(read_from)
    return data['last_update_date']


def read_directory(dir_name):
    """
    Given the path to a directory, returns a list containing the files in that directory

    Parameters
    ----------
    dir_name: str
        Path to directory

    Returns
    -------
    files: list
        List of files in the directory

    """
    files = []
    for filename in os.listdir(dir_name):
        filename = path.join(dir_name, filename)
        if path.isfile(filename):
            last_slash_index = filename.rfind('/')
            filename = filename[last_slash_index + 2:]
            files.append(filename)
    return files


def check_row(filename, row):
    """
    Given a filename and a row number, confirms that the entered row is a valid row number.
    Returns the contents of the note as a list

    Parameters
    ----------
    filename: str
        Name of the file
    row: str
        Row number

    Returns
    -------
    memories: list
        The contents of the note as a list
    """
    if not row.isnumeric():
        print('You have entered in a faulty row number. Please choose an integer value.')
        return
    row = float(row)
    if not row.is_integer():
        print('You have entered in a faulty row number. Please choose an integer value.')
        return
    row = int(row)
    memories = []
    with open(filename, 'r') as f:
        memories = f.readlines()
    if row <= 0 or row > len(memories):
        print('You have entered in a faulty row number. Please try again.')
        return
    return memories


def write_to_data_file(data_file, filename):
    """
    Given the data_file.json file and a filename, changes the filename held in data_file 

    Parameters
    ----------
    data_file: str
        name of the data_file.json file
    filename
        Name of the file to set as the current file

    Returns
    -------
    None:
        Changes the current file held in data_file.json 
    """
    data = {}
    with open(data_file, 'r') as read_from:
        data = json.load(read_from)
    data['current_note'] = filename
    with open(data_file, 'w') as write_to:
        json.dump(data, write_to)


def request_user_permission(prompt):
    """
    Given a prompt, captures the user's answer as either 'y' or 'n'

    Parameters
    ----------
    prompt:str
        Prompt displayed to user

    Returns
    -------
    decision: str
        User input, can contain 'y' or 'n'
    """
    decision = input(prompt)
    while (decision != 'y') and (decision != 'n'):
        decision = input(prompt)
    return decision


def parse_unary_args(args):
    """
    Given a set of arguments, parses them and returns the found word

    Parameters
    ----------
    args: dict
        Argument list to parse

    Returns
    -------
    word:str
        Found word.
    """
    if type(args) == str:
        return args.strip()
    if len(args) == 1:
        return args[0].strip()
    word = ''
    for arg in args:
        word += arg + ' '
    return word.strip()


def parse_binary_args(args):
    """
    Given a set of arguments, parses the words to the left and right of the '/'

    Parameters
    ----------
    args: dict
        List of arguments to parse

    Returns
    -------
    list:
        Words which are adjacent to '/'
    """
    if len(args) == 1 or not '/' in args:
        print('You haven\'t entered enough information. Please try again.')
        return
    old_name = ''
    new_name = ''
    counter = 0
    while (not counter >= len(args)) and (not args[counter] == '/'):
        old_name += args[counter] + ' '
        counter += 1
    old_name = old_name.strip()
    counter += 1
    while not counter == len(args):
        new_name += args[counter] + ' '
        counter += 1
    new_name = new_name.strip()
    if len(new_name) == 0:
        print('You haven\'t entered enough information. Please try again.')
        return
    return old_name, new_name


def make_note(dot_name, filename):
    """
    Given a dot_name and a filename, makes a new note with that name

    Parameters
    ----------
    dot_name: str
       Path to the file 
    filename : str
        Name of the file

    Returns
    -------
    None or 1
        Makes a new note with the given name
    None suggests an error in creating the note
    1 suggests that make_note succesffuly created the new note
    """
    if path.isfile(dot_name):
        print('A note with this name already exists. Please choose a different name, delete the other note, '
              'or rename the other note.')
        return 
    else:
        open(dot_name, 'w+').close()
        return 1
