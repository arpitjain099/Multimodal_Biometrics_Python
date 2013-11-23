import sys, string, os
import glob
import os
import codecs
fi=codecs.open('output3.txt', 'r', encoding='utf-8')
fg=fi.read()
fg=fg.split('\n')
for lines in fg:
	line=lines.split(' ')

	for i,j in enumerate(line):
		global left
#		left=''
		global mid
#		mid=''
		global right
#		right=''
		#print(i)
		if i==0:
			left=j[40:]
		if i==1:
			mid=j[40:]
		if i==2:
			right=j
	print(left+' '+mid+' '+right)
#	print(mid)
#	print(right)
fi.close
