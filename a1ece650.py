#!/usr/bin/python
# -*- coding: <utf-8> -*-

import sys
import matplotlib
import re

class Street:
    verticesBase = {}
    edgesBase = {}
    plotBase = []
    def __init__(self,vBase,eBase):
        self.verticesBase = vBase
        self.edgesBase = eBase
    def addStreet(self,streetName,vItem):
        if self.verticesBase.has_key[streetName] == False:
            self.verticesBase[streetName] = vItem
        else:
            print("You added a street that has existed!")
    def deleteStreet(self,streetName):
        if self.verticesBase.has_key[] == False:
            del self.verticesBase[streetName]
        else:
            print("The street you want to delete doesn't even exist!")
    def changeStreet(self,streetName,newVItem):
        if self.verticesBase.has_key[streetName] == False:
            self.verticesBase[streetName] = newVItem
        else:
            print("The street you want to change doesn't exist.Please Check again.")
    def showGraph(self):
        if len(self.verticesbase)>0:
            for v in self.verticesBase.values():
                self.plotBase    


try:
   # str_read = raw_input("enter your command: a add c change r remove g output graph:")
    str_read = 'a "Weber Street" (12,20) (2,1) (3,4)'

    cmd = re.search(r'(?P<op>[acrg])\s+"(?P<street>(\w+\s*)+)"\s+(?P<coordinates>\(.*?\)\s*)+',str_read)
    cor = re.findall(r'.*?\((\d+),.*?\)',str_read)
    #cmd = re.search(r'\([0-9]*\.?[0-9]+,[0-9]*\.?[0-9]+\)\s+',str_read)  
    py = re.findall(r'.*?\(.*?,(\d+)\)',str_read)
    teststr = '(0,1) (1,2)'
    #cmd = re.search(r'\([0-9]\d*,[0-9]\d*\)',str_read) 
    if True:
        res = cmd.groupdict()
        print(res['coordinates']+" is digits")
        if cor: 
          # px = cor['x']
           print(cor)
        if py:
           #res['coordinates'] = cor
           print(py)
        if res['op'] == 'a':
           pass
           
    else: 
        print("nothing found")
#actually can be processed with one exception
except BaseException:
    pass
finally:
    pass



