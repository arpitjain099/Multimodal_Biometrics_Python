python3 process_reference.py
python3 process_template.py
python3 py0.py > output_temp.txt
python3 makerightformat.py
python3 rightformat.py > process.txt
python3 makerightformat2.py
cat final.txt |sed 's/.xyt//g'|awk '{printf("%s 1 %s 2 %d %f\n",$1,$2,$1==$2,1-$3);}' >t.txt
cp t.txt adiScripts
cd adiScripts
bash main_N.sh ./t.txt 1 1 /home/hp/Downloads/kplet_2/
