#!/usr/bin/python
#Filename:testClass.py

class Person():
	#pass
	def __init__(self,name='NPC'):
		self.name = name

	def sayHi(self):
		print 'Hello, my name is %s'%self.name
		print "Hello, my name is",self.name
	
	def __del__(self):
		pass

p = Person('hanwj')
p.sayHi()