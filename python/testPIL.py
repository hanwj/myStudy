#!/usr/bin/python
#Filename:testPIL

import os
from PIL import Image 

rootPath = "E:/airwind_tank/asset/base/images/globalUI/equip/"
fileList = os.listdir(rootPath)

for i in fileList:
	filePath = rootPath + i
	f = Image.open(filePath)
	width,height = f.size
	box = (2,2,80,80)
	if width > 80:
		f.crop(box).save(filePath)
# f=Image.open("E:/airwind_tank/asset/base/images/globalUI/equip/anmiejuanzhou_icon.jpg")
# box=(2,2,80,80)
# f.crop(box).save("test1.jpg")