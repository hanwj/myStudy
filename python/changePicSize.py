#!usr/bin/python

import sys
import os
from PIL import Image

inputDir = sys.argv[1]

fileList = os.listdir(inputDir)
maxWidth = 1136
maxHeight = 640
for i in fileList:
	filePath = os.path.join(inputDir,i)
	f = Image.open(filePath)
	width,height = f.size
	if width > maxWidth or height > maxHeight:
		scaleX = float(width) / maxWidth
		scaleY = float(height) / maxHeight
		scale = scaleX > scaleY and scaleX or scaleY
		realWidth = width / scale
		realHeight = height / scale
		print scale
		print i,width,height
		print i,realWidth,realHeight
		f.resize((int(realWidth),int(realHeight))).save(filePath)