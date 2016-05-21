#!/bin/bash
msge=""
while true
do
clear
./dataGen
./std < in.txt > stdout.txt
time ./Walls < in.txt > out.txt
diff out.txt stdout.txt
read
done
