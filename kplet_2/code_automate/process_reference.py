import glob
import os
import codecs
os.chdir("/home/hp/cs698x/kt/minutiaes/p1/Lum")
for files in glob.glob("*.xyt"):
	fi=codecs.open(files, 'r', encoding='utf-8')
	fg=fi.read()
	fg=fg.split("\n")[1:]
	fg='\n'.join(fg)
	output='/home/hp/cs698x/kt/minutiaes/p1/Lum/new/'+files
	print(output)
	fi=codecs.open(output, 'w', encoding='utf-8')
	fi.write(fg)
	fi.close
