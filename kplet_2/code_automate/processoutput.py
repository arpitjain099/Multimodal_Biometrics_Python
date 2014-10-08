import codecs
fi=codecs.open('output.txt', 'r', encoding='utf-8')
fg=fi.read()
fi.close
lines=fg.split("\n")
for lines in fg:
	#10070.xyt /home/hp/cs698x/kt/minutiaes/p2/Lum/new/20835.xyt 0.007305
	temp1=lines.split("/home/hp/cs698x/kt/minutiaes/p1/Lum/new/1/")[1]
	temp2=temp1.split(" ")
	mid=temp2[1].split("/home/hp/cs698x/kt/minutiaes/p2/Lum/new/")[1]
	left=temp2[0]
	right=temp2[2]
	print(left+' '+mid+' '+right)
	
