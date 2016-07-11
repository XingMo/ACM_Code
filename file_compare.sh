#!/bin/bash
msge=""
while true
do
clear
./dataGen
echo 'std'
time ./std < in.txt > stdout.txt
echo 'my'
time ./这是一颗普通的树 < in.txt > out.txt
diff stdout.txt out.txt
#echo $mege
echo '---'
read
done

