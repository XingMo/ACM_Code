#!/bin/bash
while true
do
#clear
./dataGen
echo 'std'
time ./std < in.txt > stdout.txt
echo 'my'
time ./Gems_Fight < in.txt > out.txt
if ! diff stdout.txt out.txt; then
	break
fi
echo '---'
#read
done
