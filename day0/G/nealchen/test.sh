#!/usr/bin/bash
n=0
while ./ds <input >user_out && ./basic <input >answer && ./chk
do
	((n=$n+1))
	echo Correct $n
	if [[ $n == $1 ]]
	then
		break
	fi
	./rand3 100 >input
done
