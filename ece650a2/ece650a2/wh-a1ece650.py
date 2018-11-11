#!/usr/bin/env python
from __future__ import division
import re
import sys

# YOUR CODE GOES HERE
class Street(object):
    vb_dc_l = {} 
    eb_dc_l = {}
    valid_points = []
    valid_edges = []
    point_history = []
    uniq_v_index = 0

    def add_street(self,street_name,vi_l,ei_l):
        #vi_l = get_coordinates(),ei_l = get_lines()
        stn = street_name.upper()
        if self.vb_dc_l.has_key(stn) == False:
            self.vb_dc_l[stn] = vi_l
            self.eb_dc_l[stn] = ei_l
        else:
            sys.stderr.write("Error: invalid command: 'a' specified a street that has already existed \n")

    def delete_street(self,street_name):
        if self.vb_dc_l.has_key(street_name.upper()) == True:
            del self.vb_dc_l[street_name.upper()]
            del self.eb_dc_l[street_name.upper()]
        else:
            sys.stderr.write("Error: invalid command:The street you want to delete doesn't even exist!\n")

    def change_street(self,street_name,newvi_l,newei_l):
        if self.vb_dc_l.has_key(street_name.upper()) == True:
            self.vb_dc_l[street_name.upper()] = newvi_l
            self.eb_dc_l[street_name.upper()] = newei_l
        else:
            sys.stderr.write("Error: invalid command:The street you want to change doesn't exist. Please check again.\n")

    def text_graph(self):
        self.process_graph()
        self.valid_points.sort(key=lambda pt: pt.index,reverse = False)
        sys.stdout.write("V "+str(self.valid_points[-1].index + 1)+'\n')


        #for v in self.valid_points:
            #sys.stdout.write(str(v)+"\n")
        #sys.stdout.write("}\n")
        # sys.stdout.write("E {")
        # for i in range(0,len(self.valid_edges)-1):
        #     sys.stdout.write(str(self.valid_edges[i])+",")
        #     #sys.stdout.flush()
        # if len(self.valid_edges)>0:
        #     sys.stdout.write(str(self.valid_edges[-1])+"}\n")
        str_line = "E {"
        
        if len(self.valid_edges)>0:
            for i in range(0,len(self.valid_edges)-1):
                str_line += str(self.valid_edges[i])+","
            str_line += str(self.valid_edges[-1])
        str_line += "}\n"
        sys.stdout.write(str_line)

        

    def get_coordinates(self,str_read):
        # return {"A":(a,b),"B":(c,d)}
        cord =  re.findall(r'(\(\s*[-+]?[0-9]*\.?[0-9]+\s*,\s*[-+]?[0-9]*\.?[0-9]+\s*\)\s*)',str_read)
        try:
            #might have invalid input so that can't eval
            vertices = []
            for val in cord:
                cor = eval(val)
                p = Point(cor[0],cor[1],self.uniq_v_index)
                if not p.is_in(self.point_history):  # a brand new
                    self.uniq_v_index = self.uniq_v_index + 1
                    self.point_history.append(p)
                else:  # not a brand new
                    for ph in self.point_history:
                        if p == ph:
                            p.index = ph.index
                            break
                vertices.append(p)
            return vertices
        except:
            sys.stderr.write("Error: invalid coordinates")
            return None

    def get_lines(self,vi_l):
        #vi_l is a dictionary. return a list:[(1,2),(2,3),(3,4)]
        ei_l = []
        rg = range(0,len(vi_l)-1)
        for i in rg:
            l = Line(vi_l[i],vi_l[i+1])
            ei_l.append(l)
        return ei_l

    def process_cmd(self,str_read):
        cmd_ac = re.search(r'\s*([ac])\s+"([a-zA-Z\s]+)"\s+(\(\s*[-+]?[0-9]*\.?[0-9]+\s*,\s*[-+]?[0-9]*\.?[0-9]+\s*\)\s*)+',str_read)
        if cmd_ac != None and cmd_ac.group(0) == str_read:
            vi_l = self.get_coordinates(str_read)
            ei_l = self.get_lines(vi_l)
            str_list = cmd_ac.groups()
            if str_list[0] == "a":               
                self.add_street(str_list[1],vi_l,ei_l)
            elif str_list[0] == "c":
                self.change_street(str_list[1],vi_l,ei_l)
        else:
            cmd_r = re.search(r'^\s*[r]\s+"(.*?)"\s*$',str_read)
            if cmd_r != None:
                self.delete_street(cmd_r.group(1))
            else:
                cmd_g = re.search(r'^\s*g\s*$',str_read)
                if cmd_g != None:
                    self.text_graph()
                else:
                    sys.stderr.write("Error from a1: no match for the line.**"+str_read+'***\n')

    def add_if_not_in(self,some_list,some_storage):
        for i in some_list:
            if not i.is_in(some_storage):
                some_storage.append(i)

    def process_graph(self):
        #process valid_points
        del self.valid_edges[:]
        del self.valid_points[:]
        for l_o in self.eb_dc_l.keys():
            for l_n in self.eb_dc_l[l_o]:
                del l_n.intersections[:]
        for i in self.eb_dc_l.keys():
            for j in self.eb_dc_l.keys():
                if i!=j:
                    for l1 in self.eb_dc_l[i]:
                        for l2 in self.eb_dc_l[j]:
                            p_l = intersect_on_segment(l1,l2,self.uniq_v_index)
                            if p_l != None:
                                for p in p_l:
                                    if not p.is_in(self.point_history):# a brand new
                                        self.uniq_v_index = self.uniq_v_index + 1
                                        self.point_history.append(p)
                                    else:#not a brand new, but may not previously in line.intersections
                                        for ph in self.point_history:
                                            if p==ph:
                                                p.index = ph.index
                                                break
                                    self.add_if_not_in([p,l1.src,l1.dst,l2.src,l2.dst],self.valid_points)
                                    self.add_if_not_in([p],l1.intersections)
                                    self.add_if_not_in([p],l2.intersections)
        #if p_l!=None, then you can expect valid edges
        for i_i in self.eb_dc_l.keys():
            for l_i in self.eb_dc_l[i_i]:
                if len(l_i.intersections)>0: #at this time, l2 has been compared with all the lines
                    v_p2 = [l_i.src, l_i.dst]
                    v_pn2 = list(set(v_p2+l_i.intersections))
                    v_pn2.sort(key=lambda pt: pt.x, reverse = False)
                    v_pn2.sort(key=lambda pt: pt.y, reverse = False)
                    for ix in range(0, len(v_pn2) - 1):
                        if not v_pn2[ix].__eq__(v_pn2[ix+1]):
                            self.add_if_not_in([Line(v_pn2[ix], v_pn2[ix + 1])],self.valid_edges)
    
class Point(object):
    def __init__ (self, x, y, index):
        self.x = float(x)
        self.y = float(y)
        self.index = index
    def __str__ (self):
        return str(self.index)+':(' + str(self.x) + ',' + str(self.y) + ')'

    def __eq__ (self, other):
        return self.x == other.x and self.y == other.y

    def __ge__ (self, other):
        return self.x >= other.x

    def __le__ (self, other):
        return self.x <= other.x

    def is_in(self,some_storage):
        for i in some_storage:
            if i.x == self.x and i.y == self.y:
                return True
            else:
                continue
        return False

class Line(object):
    def __init__ (self, src, dst):
        self.src = src
        self.dst = dst
        self.intersections = []

    def __str__ (self):
        return "<"+str(self.src.index) + ',' + str(self.dst.index)+">"

    def __ge__ (self,other):
        ge1 = self.src <= other.src and self.src <= other.dst and self.dst >= other.src and self.dst >= other.dst
        ge2 = self.dst <= other.src and self.dst <= other.dst and self.src >= other.src and self.dst >= other.dst
        return any([ge1, ge2])

    def __eq__ (self,other):
        return self.src == other.src and self.dst == other.src

    def is_in(self,some_storage):
        for i in some_storage:
            g1 = i.src.index == self.src.index and i.dst.index == self.dst.index
            g2 = i.dst.index == self.src.index and i.src.index == self.dst.index
            if any([g1,g2]) == True:
                return True
            else:
                continue
        return False
    
def intersect_on_segment (l1, l2,new_index):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y
    #to determine whether the two lines would intersect on the 2 segments
    t_up = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4)
    u_up = -(x1-x2)*(y1-y3) + (y1-y2)*(x1-x3)
    denominator = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    #if they are parallel or coincident:
    if denominator == 0: 
        #coincident
        if (x1-x2) * (y2-y3) == (x2-x3) * (y1-y2):
            if l1.__ge__(l2):
                return [l2.src,l2.dst]
            elif l2.__ge__(l1):
                return [l1.src,l1.dst]
            else:
                return None
        #parallel        
        else:
            return None
    else:
        t = t_up / denominator
        u = u_up / denominator
        #if the intersection is on both segments
        if 0 <= t and t <= 1 and 0 <= u and u <= 1:
            xnum = ((x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4))
            xcoor =  xnum / denominator

            ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
            ycoor = ynum / denominator

            return [Point(xcoor, ycoor, new_index)]
        else:
            return None


def main():
    ### YOUR MAIN CODE GOES HERE
    try:
        ns = Street()
        while True:
            line = sys.stdin.readline()
            if line == '':
                break
            ns.process_cmd(line)
    except exception1:
        sys.stderr.write("Error detected. Please double-check your input!")
    # print 'Finished reading input'
    # return exit code 0 on successful termination
    sys.exit(0)

if __name__ == "__main__":
    main()
