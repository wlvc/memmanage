#!/bin/bash

for X in memmanage strfield; do
	gcc --std=c99 $X.c -o $X;
done
