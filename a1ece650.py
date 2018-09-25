#!/usr/bin/python
# -*- coding: <utf-8> -*-

import sys
import matplotlib
import re
import numpy as np
import pylab as pl
from matplotlib import collections  as mc

class Street:
    vertices_base = {}
    edge_base = {}
    plot_base = []
    def __init__(self,vBase,eBase):
        self.verticesBase = vBase
        self.edgesBase = eBase
    def addStreet(self,streetName,vItem):
        if self.verticesBase.has_key[streetName.upper()] == False:
            self.verticesBase[streetName.upper()] = vItem
        else:
            print("You added a street that has existed!")
    def deleteStreet(self,streetName):
        if self.verticesBase.has_key[streetName.upper()] == False:
            del self.verticesBase[streetName.upper()]
        else:
            print("The street you want to delete doesn't even exist!")
    def changeStreet(self,streetName,newVItem):
        if self.verticesBase.has_key[streetName.upper()] == False:
            self.verticesBase[streetName.upper()] = newVItem
        else:
            print("The street you want to change doesn't exist. Please check again.")
    def showGraph(self):
        if len(self.verticesbase)>0:
            for v in self.verticesBase.values():
                self.plotBase.append(v)
        else:
            print("The graph is empty.")
        if len(self.plotBase)>0:
            c = np.array([(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1)])
            lc = mc.LineCollection(plotBase, colors=c, linewidths=2)
            fig, ax = pl.subplots()
            ax.add_collection(lc)
            ax.autoscale()
            ax.margins(0.1)
            pl.show()
    def isValidCmd                


try:
   # str_read = raw_input("enter your command: a add c change r remove g output graph:")
    str_read = 'a "Weber Street" (12,20) (2,1) (3,4)'

    cmd = re.search(r'(?P<op>[acrg])\s+"(?P<street>(\w+\s*)+)"\s+(?P<coordinates>\(.*?\)\s*)+',str_read)
    print(cmd.groups())
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



