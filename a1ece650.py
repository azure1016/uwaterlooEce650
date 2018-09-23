#!/usr/bin/python
# -*- coding: <utf-8> -*-
#import os
import sys
import matplotlib
import re
#import turtle

try:
    print("do main loop")
   # str_read = raw_input("enter your command: a add c change r remove g output graph:")
    str_read = 'a "Weber Street" (12,20) (2,1) (3,4)'
#    str_list = re.split(r'[\s]',str_read)
#    print(str_list)
    ##cmd = re.search(r'.\s',str_read)

   # cmd = re.search(r'[acrg]\s+"((\w+\s*)+)"\s+(\([-+]?[0-9]*\.?[0-9]+,[-+]?[0-9]*\.?[0-9]+\)\s*+)',str_read)
    #cmd = re.search(r'\([0-9]*\.?[0-9]+,[0-9]*\.?[0-9]+\)\s+',str_read)  
    teststr = '(0,1) (1,2)'
    cmd = re.search(r'\([0-9]\d*,[0-9]\d*\)',teststr) 
    if cmd:
   #     print(cmd.group(1)+ " is cmd")
   #     print(cmd.group(2)+" is street")
        print(cmd.group(3)+" is digits")
       # if cmd.group
    else: 
        print("nothing found")
#actually can be processed with one exception
except BaseException:
   # print("do something")
    pass
finally:
    pass
    #print("what should be done whatever the situation?")


