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
    valid_points = []
    valid_edges = []
    point_history = []
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
            sys.stdout("You added a street that has existed!")

    def delete_street(self,street_name):
        if self.vb_dc_l.has_key[street_name.upper()] == False:
            del self.vb_dc_l[street_name.upper()]
            del self.eb_dc_l[street_name.upper()]
        else:
            sys.stdout("The street you want to delete doesn't even exist!")

    def change_street(self,street_name,newvi_l,newei_l):
        if self.vb_dc_l.has_key[street_name.upper()] == False:
            self.vb_dc_l[street_name.upper()] = newvi_l
            self.eb_dc_l[street_name.upper()] = newei_l
        else:
            sys.stdout("The street you want to change doesn't exist. Please check again.")

    # def show_graph(self):
    #     if len(self.vb_dc_l)>0:
    #         for v_s in self.vb_dc_l.values(): #v_s is a line
    #             self.plot_base.append(v_s)
    #     else:
    #         stdout("The graph is empty.")
    #     if len(self.plot_base)>0:
    #         c = np.array([(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1)])
    #         lc = mc.LineCollection(plot_base, colors=c, linewidths=2)
    #         fig, ax = pl.subplots()
    #         ax.add_collection(lc)
    #         ax.autoscale()
    #         ax.margins(0.1)
    #         pl.show()

    def text_graph(self):
        self.process_graph()
        sys.stdout("V = {")
        for v in self.valid_points:
            print v+"\n"
        print "}"
        print "E = {"
        for e in self.valid_edges:
            print e+"\n"
        print "}"

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
                self.point_history.append(p)
                vertices.append(p) 
                uniq_v_index = uniq_v_index + 1
            return vertices
        #except exception1:
            #pass# for now

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
                self.eb_dc_l[v.get_key()].append(l)

    def process_cmd(self,str_read):
        #cmd = re.search(r'^(\s)*[ac]\s+"((\w+\s*)+)"\s+(\(.*?\)\s*)+',str_read)
        self.flags_clear()
        cmd_ac = re.search(r'^\s*([ac])\s+".*?"\s+(\(.*?\)\s*)+$',str_read)
        if cmd_ac != None:
            vi_l = self.get_coordinates(str_read)
            ei_l = self.get_edges(str_read)
            str_list = cmd_ac.groups()
            if str_list[0] == "a":               
                self.add_street(str_list[1],vi_l,ei_l)
            elif str_list[0] == "c":
                self.change_street(str_list[1],vi_l,ei_l)
        else:
            cmd_r = re.search(r'^(\s)*[r]\s+"(.*?)"\s*$',str_read) 
            if cmd_r != None:
                #street_name = re.sub(r'\"\s+',"\"",cmd_r.group(2))
                #street_name = 
                self.delete_street(cmd_r.group(1))
                #return true
            else:
                cmd_g = re.search(r'^\s*g\s*$',str_read)
                if cmd_g != None:
                    self.text_graph()
                    #return True
        #return False
    def add_if_not_in(self,some_list,some_storage):
        for i in some_list:
            if not i.is_in(some_storage):
                some_storage.append(i)

    def process_graph(self):
        #process valid_points
        for i in self.eb_dc_l.keys():
            for j in self.eb_dc_l.keys():
                if i!=j:
                    for l1 in self.eb_dc_l[i]:
                        for l2 in self.eb_dc_l[j]:
                            p_l = self.intersect_on_segment(l1,l2,self.uniq_v_index)
                            #when no valid point found,return a none object rather than a list?
                            if p_l != None:
                                for p in p_l:
                                    if not p.is_in(self.point_history):# a brand new
                                        self.uniq_v_index = self.uniq_v_index + 1
                                        self.point_history.append(p)
                                        self.valid_points.append(p)
                                        self.add_if_not_in([p],self.valid_points)
                                        # if not p.is_in(l1.intersections):
                                        self.add_if_not_in([p],l1.intersections)
                                        #if not p.is_in(l2.intersections):
                                        self.add_if_not_in([p],l2.intersections)
                                    else:#not a brand new, but may not previously in line.intersections
                                        for ph in self.point_history:
                                            if p==ph:
                                                p.index = ph.index
                                                break
                                        self.add_if_not_in([p,l1.src,l1.dst,l2.src,l2.dst],self.valid_points)
                                        self.add_if_not_in([p],l1.intersections)
                                        self.add_if_not_in([p],l2.intersections)
                                #if p_l!=None, then you can expect valid edges
                                v_p = [l1.src,l1.dst].append(l1.intersections)
                                v_p.sort()
                                for i in range(0,len(v_p)-2):
                                    self.valid_edges.append(Line(v_p[i],v_p[i+1]))
    
 

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
                        




