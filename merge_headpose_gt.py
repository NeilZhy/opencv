#!/usr/bin/python
import os
path = "./build" 
f_list = os.listdir(path)
fo = open("headpose.gt.txt", "w")
for i in f_list:
    if os.path.splitext(i)[1] == '.txt':
        i = "./build/" + i
        file = open(i)
        for line in file:
            fo.write(line)

