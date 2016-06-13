#!/bin/bash
msge=""
while true
do
clear
./dataGen
echo 'std'
time ./std < in.txt > stdout.txt
echo 'my'
time ./组队方案数 < in.txt > out.txt
diff out.txt stdout.txt
#echo $mege
echo '---'
read
done

