# **Quick Note Version History** #

Created on July 24, 2020. 

**Quick Note** is an application to save snippet
memories for the user which can
then be reported back at any point.
 
## **@version 1.0.0** ## 
July 24, 2020

Added basic functionality, `add_memory`
`clear_memories`, `list_memories`, `get_help`
and info methods.

## **@version 1.0.1** ## 
July 25-26, 2020

Added `remove_memory` method, and began
work on file adding and manipulation
methods

## **@version 1.0.2** ## 
July 27, 2020

Added initial `add_file`, `list_files`,
and `change_file` methods.

## **@version 1.0.3** ##
July 28, 2020

Fixed existing version of `rename_note`, added sample 
commands to main.py help command. Added simpler file 
pathing to eliminate the need for the `$USER` argument
in the command. Added the CONTRIBUTING.md file. Made
the install.py file add a default note upon installation.
Further fixed `rename_note`, added `remove_note` and `clear_note`
methods. Added `import_note` method. Added helper functions to assist
with code decomposition; these are `make_note`, `parse_binary_args`,
`parse_unary_args`, and `request_user_permission`. Added the ability
to export notes as `.txt` files by adding the `export_note` method.

## **@version 1.0.4** ##
July 29-30, 2020

Added the CODE_OF_CONDUCT.md file, added the GNU GPL.v3 license,
renamed memfunc.py and filefunc.py to memory.py and note.py, respectively,
for reasons of clarity. Added the helper_func.py file to hold the existing
helper functions `make_note`, `parse_binary_args`, `parse_unary_args`,
`request_user_permission`, and the new helper function `write_to_quicknote_cache`.
Added more extensive error handling throughout the software for various faulty
user inputs (so that the methods simply return instead of python throwing an error).
Made the install.py file add a '.archive' note upon it's running. Added the helper 
function `check_row` to helper_func.py and added `archive_memory` to memory.py

## **@version 1.0.5** ##
July 31-August 1, 2020

Removed the filelist and archivelist files, and replaced them with using `os.listdir()`
to read the contents of files. Changed the install.py file to add a .notes directory and
a .archive_notes folder in the .quicknote directory. Changed quicknote_cache to data_file.json,
so that it will be easier to store information about the current file and other related/important
information. Rewired most functions to adopt the filelist and quicknote_cache removal changes. Added
the ability to archive notes with `archive_note`, and added the ability to reverse archiving with
`un_archive_note`. Added the ability to clear archived notes with `clear_archive_notes`, and added
the ability list archived notes with `list_archive_notes`.

## **@version 1.0.6** ##
August 2, 2020

Added `move_memory` and `copy_memory`. Added the helper function `write_to_file` to helper_func.py.
Added the memory-helper functions `change_memory` and `append_memory` to memory.py. Added functionality
so that when user types `remember --list`, the number of memories found is displayed before the actual
memories. Implemented a similar functionality for `remember --list-notes` and `remember --list-archived-notes`,
so that these methods first print the number of notes found.

## **@versions 1.0.7 --> 1.0.14 ** ##
August 3-5, 2020

These versions were spent developing the brew tap and install functionality. In the process, added the qnote file
(which contains the contents of all the files in `files`, although those will become deprecated in time). Also,
added the `Formula` directory for holding the `qnote.rb` formula.

## **@version 1.0.15 ** ##
August 6, 2020

Fixed bugs in qnote file stemming from the collapse of main.py, install.py, note.py, memory.py, and helper_func.py in
to qnote.

## **@version 1.0.16 ** ##
August 6, 2020

Add `duplicate_note`. Shorten length of commands (instead of full words, mostly initials). Also removed double-dash from
commands and replaced with single dash

## **@version 1.0.17 ** ##
August 6, 2020

Change help menu

*Type `remember --version` to view your version of **Quick Note***
