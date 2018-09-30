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

class Line(object):
    intersections = []
    def __init__ (self, src, dst):
        self.src = src
        self.dst = dst

    def __str__ (self):
        return "<"+str(self.src.index) + ',' + str(self.dst.index)+">"

    def __ge__ (self,other):
        ge1 = self.src < other.src and self.src < other.dst and self.dst > other.src and self.dst > other.dst
        ge2 = self.dst < other.src and self.dst < other.dst and self.src > other.src and self.dst > other.dst
        return any([ge1, ge2])

    def __eq__ (self,other):
        return self.src == other.src and self.dst == other.src

#return a Point object or None
def intersect_on_segment (l1, l2, new_index):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y
    #to determine whether the two lines would intersect on the 2 segments
    t1_up = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4)
    t2_up = (x1-x2)*(y1-y3) - (y1-y2)*(x1-x3)
    denominator = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    #if they are parallel or coincident:
    # this condition might come across computational problems
    if denominator == 0: 
        #coincident
        if (x1-x2) * (y2-y3) == (x2-x3) * (y1-y2):
            if l1 >= l2:
                return [l2.src,l2,dst]
            elif l2 >= l1:
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


    

if __name__ == '__main__':
    p1 = Point (0, 1,0)
    p2 = Point (3, 1,1)
    p3 = Point (1, 0,2)
    p4 = Point (1, 8,3)

    l1 = Line (p1, p2)
    l2 = Line (p3, p4)
    print 'Intersect of', l1, 'with', l2, 'is:' 
    for i in intersect(l1, l2):
        print i
