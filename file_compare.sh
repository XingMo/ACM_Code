#!/bin/bash
msge=""
while true
do
clear
./dataGen
./std < in.txt > stdout.txt
time ./Dynamic_Inversion < in.txt > out.txt
diff out.txt stdout.txt
#echo $mege
echo '---'
read
done

