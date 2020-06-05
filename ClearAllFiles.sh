#!/bin/sh
for file in $(ls .)
do
	if [ -d $file"/" ]
	then
		echo $file
		cd $file
		rm *
		ls .
		cd ..
	fi
done
