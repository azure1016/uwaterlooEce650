#!/usr/bin/python
# -*- coding: <utf-8> -*-
from __future__ import division
import sys
import matplotlib
import re
import numpy as np
import pylab as pl
from matplotlib import collections  as mc

import intersect
#you can use py3to2 to change python3 to python2
class Street(object):
    vb_dc_l = {} 
    #{

    #"st2":[Point(3,4), Point(4,5)]
    #}

    eb_dc_l = {
    #"st1":[l1,l2,l3]
    #"st2":[l4,l5,l6]
    }
    plot_base = {}
    #flag for the four cmds
    
    uniq_v_index = 0
    uniq_st_index = 0

    # def __init__(self,v_dc,e_l):
    #     self.vb_dc_l.append(v_dc)
    #     self.eb_dc_l.append(e_l)

    def add_street(self,street_name,vi_l,ei_l):
        #vi_l = get_coordinates(),ei_l = get_lines()
        if self.vb_dc_l.has_key[street_name.upper()] == False:
            self.vb_dc_l[street_name.upper()] = vi_l
            self.eb_dc_l[street_name.upper()] = ei_l
            #self.edges_list.add(ei_l)
        else:
            stdout("You added a street that has existed!")

    def delete_street(self,street_name):
        if self.vb_dc_l.has_key[street_name.upper()] == False:
            del self.vb_dc_l[street_name.upper()]
            del self.eb_dc_l[street_name.upper()]
        else:
            stdout("The street you want to delete doesn't even exist!")

    def change_street(self,street_name,newvi_l,newei_l):
        if self.vb_dc_l.has_key[street_name.upper()] == False:
            self.vb_dc_l[street_name.upper()] = newvi_l
            self.eb_dc_l[street_name.upper()] = newei_l
        else:
            stdout("The street you want to change doesn't exist. Please check again.")

    def show_graph(self):
        if len(self.vb_dc_l)>0:
            for v_s in self.vb_dc_l.values(): #v_s is a line
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

    def text_graph(self):
        pass

    # def flags_clear(self):
    #     self.flags = [0,0,0]
    
    def get_coordinates(self,str_read):
        # return {"A":(a,b),"B":(c,d)}
        cord =  re.findall(r'(\(\s*\d+\s*,\s*\d+\s*\)\s*)',str_read) 
        try:
            #might have invalid input so that can't eval
            vertices = [] 
            for val in cord:
                cor = eval(val)
                p = Point(cor[0],cor[1],uniq_v_index)
                vertices.append(p) 
                uniq_v_index = uniq_v_index + 1
            return vertices
        except exception1:
            pass# for now

    # def get_edges(self):
    #     #return a list of Line objects
    #     v_k = vi_l.keys()
    #     edges = []
    #     for i in range(0,len(v_k)-2):
    #         edges[i] = (i,i+1)
    #     return edges

    def get_lines(self,vi_l):
        #vi_l is a dictionary. return a list:[(1,2),(2,3),(3,4)]
        for v in self.vb_dc_l.values():
            for i in range(0,len(v)-2):
                l = Line(v[i],v[i+1])
                eb_dc_l[v.get_key()].append(l)

    def process_cmd(self,str_read):
        #cmd = re.search(r'^(\s)*[ac]\s+"((\w+\s*)+)"\s+(\(.*?\)\s*)+',str_read)
        self.flags_clear()
        cmd_ac = re.search(r'^\s*([ac])\s+".*?"\s+(\(.*?\)\s*)+$',str_read)
        if cmd_ac != None:
            vi_l = get_coordinates(str_read)
            ei_l = get_edges(str_read)
            str_list = cmd_ac.groups()
            if str_list[0] == "a":               
                add_street(str_list[1],vi_l,ei_l)
            elif str_list[0] == "c":
                change_street(str_list[1],vi_l,ei_l)
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
        #for i in range(0,len(self.eb_dc_l))

# class VertexCover(object):
#     valid_vertices = {}
#     valid_edges = {
#     #"street_1":[(a,b),(b,c)],
#     #"street_2":[],
#     #"street_3":[]...
#     }

#     def __init__(self,v_dc,e_l):
#         valid_vertices = v_dc
#         valid_edges = e_l

#     def make_valid_cover(self,v_dc,e_l):
#         #e_l have to be a list rather than a dictionary
#         #e_l = Street().eb_dc_l.values(), a list of list
#         e_end = len(self.e_l) -1 #the total streets
#         for i in range(0,e_end):
#             st_i = self.e_l[i]
#             for j in range(i+1,e_end):
#                 st_j = self.eb_dc_l[j]
#                 for m in range(0,len(st_i)-1):
#                     e1 = st_i[m]#edges on the street
#                     for n in range(0,len(st_j)-1):
#                         e2 = st_j[n]
#                         e1_seg = Line(Point(e1[0],e1[1]),Point())
                        




