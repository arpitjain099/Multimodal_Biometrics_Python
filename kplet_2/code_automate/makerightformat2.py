import glob
import os
import codecs
fi=codecs.open('process.txt', 'r', encoding='utf-8')
fg=fi.read()
fg=fg.split("\n")[0:250000]
length=len(fg)
f2=codecs.open('final.txt','w',encoding='utf-8')
for i in fg:
	if i != length+1:
		f2.write(str(i)+'\n')
fi.close()
f2.close()
