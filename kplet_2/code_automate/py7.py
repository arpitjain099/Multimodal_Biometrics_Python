import sys, string, os
import glob
import os
import codecs
import subprocess
os.chdir( '/home/hp/Downloads/kplet_2' )
a=' 10002.xyt'
b=' 10002_1.xyt'
c="./graph_match "
d='gcc new.c'
e='./a.out'
#print(c)
#print(os.system( '"/home/hp/Downloads/kplet_2/graph_match" + a + b' ))
#subprocess.call("/home/hp/Downloads/kplet_2/graph_match/"+[d])
#print(os.system(c))
#print(os.system(e))
a=glob.glob("/home/hp/cs698x/kt/minutiaes/p1/Lum/new/7/*.xyt")
b=glob.glob("/home/hp/cs698x/kt/minutiaes/p2/Lum/new/*.xyt")
for files in a:
	for files2 in b:
		var2=c +' '+ files+' '+files2
		print(os.system(var2))
	
