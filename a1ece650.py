#!/usr/bin/python
# -*- coding: <utf-8> -*-

import sys
import matplotlib
import re
import numpy as np
import pylab as pl
from matplotlib import collections  as mc
import intersect

class Street:
    vertices_base = [] 
    edge_base = []
    plot_base = []
    #flag for the four cmds
    flags =[0,0,0]

    def __init__(self,vBase,eBase):
        self.vertices_base.append(vBase)
        self.edges_base.append(eBase)

    def add_street(self,street_name,vItem):
        if self.vertices_base.has_key[street_name.upper()] == False:
            self.vertices_base[street_name.upper()] = vItem
        else:
            print("You added a street that has existed!")

    def delete_street(self,street_name):
        if self.vertices_base.has_key[street_name.upper()] == False:
            del self.vertices_base[street_name.upper()]
        else:
            print("The street you want to delete doesn't even exist!")

    def change_street(self,street_name,newVItem):
        if self.vertices_base.has_key[street_name.upper()] == False:
            self.vertices_base[street_name.upper()] = newVItem
        else:
            print("The street you want to change doesn't exist. Please check again.")

    def show_graph(self):
        if len(self.vertices_base)>0:
            for v in self.vertices_base.values():
                self.plot_base.append(v)
        else:
            print("The graph is empty.")
        if len(self.plot_base)>0:
            c = np.array([(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1)])
            lc = mc.LineCollection(plot_base, colors=c, linewidths=2)
            fig, ax = pl.subplots()
            ax.add_collection(lc)
            ax.autoscale()
            ax.margins(0.1)
            pl.show()
    def flags_clear():
        flags = [0,0,0]

    def isValidCmd(self,str_read):
        #cmd = re.search(r'^(\s)*[ac]\s+"((\w+\s*)+)"\s+(\(.*?\)\s*)+',str_read)
        flags_clear()
        cmd_ac = re.match(r'^(\s)*[ac]\s+"(\s*\w+\s*)+"\s+(\(.*?\)\s*)+$',str_read)
        if cmd_ac != None:
            flags[0] = 1
            return true
        else:
            cmd_r = re.match(r'^(\s)*[r]\s+"(\s*\w+\s*)+"\s+$',str_read) 
            if cmd_r != None:
                flags[1] = 1
                return true
            else:
                cmd_g = re.match(r'^\s*g\s*$',str_read)
                if cmd_g != None:
                    flags[2] = 1
                    return True
        return False


try:
   # str_read = stdin("enter your command: a add c change r remove g output graph:")
    str_read = 'a "Weber Street" (12,20) (2,1) (3,4)'

    cmd = re.search(r'(?P<op>[acrg])\s+"(?P<street>(\w+\s*)+)"\s+(?P<coordinates>\(.*?\)\s*)+',str_read)
    print(cmd.groups())
    #cor = re.findall(r'.*?\((\d+),.*?\)',str_read)
    #cmd = re.search(r'\([0-9]*\.?[0-9]+,[0-9]*\.?[0-9]+\)\s+',str_read)  
    #py = re.findall(r'.*?\(.*?,(\d+)\)',str_read)
    teststr = '(0,1) (1,2)'
    #cmd = re.search(r'\([0-9]\d*,[0-9]\d*\)',str_read) 
    if True:
        res = cmd.groupdict()
        print(res['coordinates']+" is digits")
        if cor: 
          # px = cor['x']
           print cor
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

#test case:
#input1: a "King Street" (2,1) (1.2,2.3) (4.2,2) #float match
#input2: a "King street" (3,4) (4,5) #add an existing street
#input3: a "weber street" (2,3) #add/change a street with one point
#input4: a "university ave" (2,3) (3,6)(9,0) #missing space between coordinates
#input5: a " King street west" (3,2) (2,5) #extra space on the cmd
#input6:   c  " university  ave " (2,3 ) (4   ,6) #extra space on the cmd
#input7: c "cedarbrae avenue" (3,4) (1,3)
#input8: c "king street" (3,4) (1,2) #smaller case
#input:  a "albert street" (2,1) (1,2,2.3) #street overlap

#所以，重叠的街道，所有重合的顶点都是交叉点？
#我之前以为重叠的街道只算首尾的点才是交叉点呢）（可是万一只是线段重合，但是顶点并没有重合呢？？）
#please format the float as 0.2f
#denominator == 0, is it exactly 0?



