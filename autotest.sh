#!/bin/bash
	make
	for ((i=0; i<=9; ++i))
	do
		./TP2 < toy_"$i"_input
		diff -q ./indices/toy_"$i"/index ./respostas/toy_"$i"/index
	done