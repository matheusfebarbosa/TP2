#!/bin/bash
	make
	for ((i=0; i<9; i++)) do
		./TP2 < toys/toy_"$i"_input
		diff -q indices/toy_"$i" respostas/toy_"$i"
	done