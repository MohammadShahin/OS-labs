#!/bin/bash

gcc ex1.c -o ex1
for ((n=0;n<10;n++)); 
do 
  ./ex1
done
