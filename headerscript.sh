#!/bin/bash
for file in *.c *.h
do
vim -c 'Stdheader' -c 'wq' $file
done
