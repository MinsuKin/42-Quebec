#!/bin/sh
i=`ls -Rl | grep -e ^- -e ^d | wc -l`
n=`expr $i + 1`
echo $n
