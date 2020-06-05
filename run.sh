#!/bin/sh
make clean
make
if [ $? -ne 0 ]
	then
		echo "make error"
	else
		echo "success!"
		if [ $# -ge 1 ]
			then		
				cd ./target
				du -h *
				./* $*
				cd ..
			else
				cd ./target				
				du -h *				
				./*
				cd ..
		fi
fi 
