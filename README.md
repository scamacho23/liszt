# Liszt 

![](liszt.png)

**Liszt makes it easy to jot down thoughts in the command line, and
keep ideas clear in separate notes**

[![Documentation Status](https://readthedocs.org/projects/liszt/badge/?version=latest)](https://liszt.readthedocs.io/en/latest/?badge=latest)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/scamacho23/homebrew-liszt.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/scamacho23/homebrew-liszt/context:cpp)
![liszt license](https://img.shields.io/badge/license-GPL%20v3-success)
![liszt release](https://img.shields.io/badge/release-v1.1.7-informational)

## Installation

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
$ cp lst /usr/local/bin/lst
```

### Pkg Installer
Click on [this](liszt-1.1.7.pkg) to be redirected to the local liszt-1.1.7.pkg
file. Click 'download' on the right side of the page to download the package
installer.

*Any issues with installation should be emailed to liszt.central@gmail.com*

## Contributing to the Project
For more information, see the `CONTRIBUTING.md` file.
This project is fully open-source. We appreciate all the help
we can get and are very open to beginners and anyone interested
in helping.

## Community Information
*There is a Slack channel for contributors. If you would like to join
the channel, make a pull request and include in the comment that you
would like to be added (and the email to be used for the invite).*
