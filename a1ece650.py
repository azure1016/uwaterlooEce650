#!/usr/bin/python
# -*- coding: <utf-8> -*-

import sys
import matplotlib
import re
import numpy as np
import pylab as pl
from matplotlib import collections  as mc
from __future__ import division
import intersect
#you can use py3to2 to change python3 to python2
class Street:
    vertices_base = {} 
    #{
    #"street_1":{"1":(1,2), "2":(2,3)}
    #"street_2":{"3":(3,4), "4":(4,5)}
    #"street_3":{"5":(5,6),"6":(6,7)}
    #}
    vertices_base_backup = {}
    edges_base = {
    #"street_1":[(),(),...()]
    #"street_2":[(),(),...()]
    }
    plot_base = {}
    #flag for the four cmds
    street_flag = 0 #0 for end of street, 1 for continuing
    flags =[0,0,0]
    unique_index = 0

    def __init__(self,vBase,eBase):
        self.vertices_base.append(vBase)
        self.edges_base.append(eBase)

    def add_street(self,street_name,vItem,eItem):
        #vItem is a dictionary while eItem is a list
        if self.vertices_base.has_key[street_name.upper()] == False:
            self.vertices_base[street_name.upper()] = vItem
            self.edges_base[street_name.upper()] = eItem
        else:
            stdout("You added a street that has existed!")

    def delete_street(self,street_name):
        if self.vertices_base.has_key[street_name.upper()] == False:
            del self.vertices_base[street_name.upper()]
            del self.edges_base[street_name.upper()]
        else:
            stdout("The street you want to delete doesn't even exist!")

    def change_street(self,street_name,newVItem,newEItem):
        if self.vertices_base.has_key[street_name.upper()] == False:
            self.vertices_base[street_name.upper()] = newVItem
            self.edges_base[street_name.upper()] = newEItem
        else:
            stdout("The street you want to change doesn't exist. Please check again.")

    def show_graph(self):
        if len(self.vertices_base)>0:
            for v_s in self.vertices_base.values(): #v_s is a line
                self.plot_base.append(v_s)
        else:
            stdout("The graph is empty.")
        if len(self.plot_base)>0:
            c = np.array([(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1)])
            lc = mc.LineCollection(plot_base, colors=c, linewidths=2)
            fig, ax = pl.subplots()
            ax.add_collection(lc)
            ax.autoscale()
            ax.margins(0.1)
            pl.show()

    def flags_clear(self):
        self.flags = [0,0,0]
    
    def get_coordinates(self,str_read):
        # return {"A":(a,b),"B":(c,d)}
        cord =  re.findall(r'(\(.*?\)\s*)+',str_read) 
        try:
            #might have invalid input so that can't eval
            vertices = {} 
            for val in cord:
                vertices[unique_index] = eval(val)  
                unique_index = unique_index + 1
            return vertices
        except exception1:
            pass# for now

    def get_edges(self,vBase):
        #return a list:[(1,2),(2,3),(3,4)]
        v_k = vBase.keys()
        edges = []
        for i in range(0,len(v_k)-2):
            edges[i] = (i,i+1)
        return edges

    def process_cmd(self,str_read):
        #cmd = re.search(r'^(\s)*[ac]\s+"((\w+\s*)+)"\s+(\(.*?\)\s*)+',str_read)
        self.flags_clear()
        cmd_ac = re.search(r'^\s*([ac])\s+".*?"\s+(\(.*?\)\s*)+$',str_read)
        if cmd_ac != None:
            vItem = get_coordinates(str_read)
            str_list = cmd_ac.groups()
            if str_list[0] == "a":               
                add_street(str_list[1],vItem)
            elif str_list[0] == "c":
                change_street(str_list[1],vItem)
        else:
            cmd_r = re.search(r'^(\s)*[r]\s+"(.*?)"\s*$',str_read) 
            if cmd_r != None:
                #street_name = re.sub(r'\"\s+',"\"",cmd_r.group(2))
                #street_name = 
                delete_street(cmd_r.group(1))
                #return true
            else:
                cmd_g = re.search(r'^\s*g\s*$',str_read)
                if cmd_g != None:
                    show_graph()
                    #return True
        #return False

    #def process_graph(self):
        #for i in range(0,len(self.edges_base))

class VertexCover:
    valid_vertices = {}
    valid_edges = {
    #"street_1":[(a,b),(b,c)],
    #"street_2":[],
    #"street_3":[]...
    }

    def __init__(self,vBase,eBase):
        valid_vertices = vBase
        valid_edges = eBase

    def make_valid_cover(self):
        e_end = len(self.valid_edges) -1
        for i in range(0,e_end):
            for j in range(i+1,e_end):
                for m in range(0,len(self.edges_base[i])-1):
                    for n in range(0,len(self.edges_base[j])-1):
                        

# try:
#    # str_read = stdin("enter your command: a add c change r remove g output graph:")
#     str_read = 'a "Weber Street" (12,20) (2,1) (3,4)'

#     cmd = re.search(r'(?P<op>[acrg])\s+"(?P<street>(\w+\s*)+)"\s+(?P<coordinates>\(.*?\)\s*)+',str_read)
#     print(cmd.groups())
#     #cor = re.findall(r'.*?\((\d+),.*?\)',str_read)
#     #cmd = re.search(r'\([0-9]*\.?[0-9]+,[0-9]*\.?[0-9]+\)\s+',str_read)  
#     #py = re.findall(r'.*?\(.*?,(\d+)\)',str_read)
#     teststr = '(0,1) (1,2)'
#     #cmd = re.search(r'\([0-9]\d*,[0-9]\d*\)',str_read) 
#     if True:
#         res = cmd.groupdict()
#         print(res['coordinates']+" is digits")
#         if cor: 
#           # px = cor['x']
#            print cor
#         if py:
#            #res['coordinates'] = cor
#            print(py)
#         if res['op'] == 'a':
#            pass
           
#     else: 
#         print("nothing found")
# #actually can be processed with one exception
# except BaseException:
#     pass
# finally:
#     pass

try: 
    ns = Street()
    while True:
        #std_read = stdin("please input the command:")
        #I heard that stdin will get a \n
        std_read = a "King Street" (2,1) (1.2,2.3) (4.2,2)       
        if ns.isValidCmd(std_read):
            for i in range(0,2):
                if ns.flags[i] == 1:

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



