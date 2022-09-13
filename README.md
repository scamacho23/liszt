# Liszt 

![](liszt.png)

**Liszt makes it easy to jot down thoughts in the command line, and
keep ideas clear in separate notes.**

View **Liszt** documentation [here](https://liszt.readthedocs.io "Liszt")

[![Documentation Status](https://readthedocs.org/projects/liszt/badge/?version=latest)](https://liszt.readthedocs.io/en/latest/?badge=latest)
[![Build Status](https://travis-ci.com/scamacho23/liszt.svg?branch=master)](https://travis-ci.com/scamacho23/liszt)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/scamacho23/homebrew-liszt.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/scamacho23/homebrew-liszt/context:cpp)
![liszt license](https://img.shields.io/badge/license-GPL%20v3-success)
![liszt release](https://img.shields.io/badge/release-v1.1.8-informational)
[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)

## Table of Contents
  - [Installation](#installation)
    - [Homebrew](#homebrew)
    - [Git Clone](#git-clone)
    - [Pkg Installer](#pkg-installer)
  - [Usage](#usage)
  - [Contributing to the Project](#contributing-to-the-project)
  - [Community Information](#community-information)
  

## Installation

*Please note that at the moment, **Liszt** is only tested on macOS, but it will build on linux.*

*Please also note that v1.1.8 does change some existing functionality that will cause incompatibility with
the existing **Liszt** file system on your computer. If you already have **Liszt** installed, before
updating to v1.1.8, please go to your ~/.liszt directory and rename the directory called 'notes' to
'main'.*

### Homebrew

*In your terminal*
```
$ brew tap liszt-music/liszt
$ brew install lst
```
These commands will install the tap of **Liszt** on your system and then install the executable
'lst' in /usr/local/bin. 

### Git Clone

*In your terminal*

```
$ git clone https://github.com/scamacho23/liszt.git
$ cd liszt 
$ cmake .
$ make
$ make install
```

**Liszt** relies on cmake for compilation and linking so we recommend having cmake installed on your
system. Alternatively, the following should do the trick (we use clang but any c compiler should work):

```
$ git clone https://github.com/scamacho23/liszt.git
$ cd liszt 
$ clang src/main.c -o lst -g
$ ln -s lst /usr/local/bin/lst
```

### Pkg Installer
Click on [this](liszt-1.1.8.pkg) to be redirected to the local liszt-1.1.8.pkg
file. Click 'download' on the right side of the page to download the package
installer.

*Any issues with installation should be emailed to liszt.central@gmail.com*

# Usage
*Please note that all functions listed below require `lst` before the command.*

| Command | Function |
|---------|----------|
| `-a <note title>` | Add a new note | 
| `-r <memory index>` | Remove memory at specified index |
| `<memory content>` | Add a new memory in current note |
| `-ch` | Change to a different note |
| `-rn` | Rename note |
| `-rm` | Remove note |
| `-ar` | Archive note |
| `-unar` | Unarchive note |
| `-in` | Import note |
| `-ex` | Export note |
| `-dp` | Duplicate note |
| `-mg` | Merge notes |
| `-c` | Copy memory |
| `-h <function handle>` | Get help for a specific function | 

## Contributing to the Project
For more information, see the `CONTRIBUTING.md` file.
This project is fully open-source. We appreciate all the help
we can get and are very open to beginners and anyone interested
in helping.

## Community Information
*There is a Slack channel for contributors. If you would like to join
the channel, make a pull request and include in the comment that you
would like to be added (and the email to be used for the invite).*
