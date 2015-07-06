#!/usr/bin/python
#Filename:testSys.py

import sys
import os

def readFile(filename):
	'''Print a file to the Standard output.'''
	
	# if filename.find('\\') == -1:
	# 	filename = os.path.abspath(os.path.dirname(sys.argv[0])) + os.sep + filename

	f = open(filename)
	while True:
		line = f.readline()
		if len(line) == 0:
			break
		print line,
	f.close()
if len(sys.argv) < 2:
	print "No action sepcified"
	sys.exit()

if sys.argv[1].startswith("--"):
	option = sys.argv[1][2:]
	if option == "version":
		print "Version  1.2.0"
	elif option == "help":
		print '''\
This program prints file to the standard output.
Any number of files can be specified.
Options include:
  --version: Print the version number
  --help: Display the help '''
	else:
		print "Unkonwn option"
		sys.exit()
else:
	for filename in sys.argv[1:]:
		print "open file",filename
		readFile(filename)
					  	