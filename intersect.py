class Point(object):
    def __init__ (self, x, y):
        self.x = float(x)
        self.y = float(y)
    def __str__ (self):
        return '(' + str(self.x) + ',' + str(self.y) + ')'

class Line(object):
    def __init__ (self, src, dst):
        self.src = src
        self.dst = dst

    def __str__(self):
        return str(self.src) + '-->' + str(self.dst)
#return a Point object or None
def intersect_on_segment (l1, l2):
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
        #if coincident
        if (x1-x2) * (y2-y3) == (x2-x3) * (y1-y2):
            #if segment not overlap
            if (x1<x3 and x1<x4 and x2<x3 and x2<x4) or (x1>x3 and x1>x4 and x2>x3 and x2>x4):
                return None
            else:
                l = [(x1,y1),(x2,y2),(x3,y3),(x4,y4)]
                def cmpByX((a1,b1),(a2,b2)):
                    if (a1<a2) : return -1
                    else: return 1
                sorted(l,cmpByX)
                return Point(l[1]),Point(l[2])
        else:
            return None
    else:
        t1 = t1_up / denominator
        t2 = t2_up / denominator
        #if the intersection is on both segments
        if 0 <= t1 and t1 <= 1 and 0 <= t2 and t2 <= 1:
            xnum = ((x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4))
            xcoor =  xnum / denominator

            ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
            ycoor = ynum / denominator

            return Point (xcoor, ycoor)
        else:
            return None


    

if __name__ == '__main__':
    p1 = Point (1, 4)
    p2 = Point (5, 8)
    p3 = Point (5, 6)
    p4 = Point (3, 8)

    l1 = Line (p1, p2)
    l2 = Line (p3, p4)
    print 'Intersect of', l1, 'with', l2, 'is', intersect(l1, l2)
