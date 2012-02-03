#!/usr/local/bin/python

# Facebook programming puzzle
# smallworld

import math
from pprint import pprint as pp
import sys

pairing_count = 0
cell_search_count = 0

class Neighborhood:

    def __init__(self, loc):
        # heuristic to divide it into 10x10 or finer grid
        self.Nx = 10
        self.Ny = 10
        if len(loc) > 2000:
            self.Nx = int(math.sqrt(len(loc)*5/100))
            self.Ny = self.Nx
        self.max_cx = self.Nx-1
        self.max_cy = self.Ny-1

        self.nb = [[[] for i in range(self.Ny)] for j in range(self.Nx)]

        # find the x,y span
        X = [x for x,y in loc]
        Y = [y for x,y in loc]
        self.x0 = min(X)
        self.xn = max(X)
        self.y0 = min(Y)
        self.yn = max(Y)
        self.span_x = self.xn-self.x0
        self.span_y = self.yn-self.y0
        self.cellx = self.span_x / self.Nx
        self.celly = self.span_y / self.Ny

        # assign points into neighborhood
        for i,(x,y) in enumerate(loc):
            cx, cy = self.get_cell_coord(x,y)
            self.nb[cx][cy].append(i)


    def get_cell_coord(self,x,y):
        cx = min(int((x-self.x0)/self.cellx), self.max_cx)
        cy = min(int((y-self.y0)/self.celly), self.max_cy)
        return cx,cy


    def get_neighbor_cells(self, x, y, step):
        cx, cy = self.get_cell_coord(x,y)

        x = x-self.x0
        y = y-self.y0

        # note: doesn't matter if cx or cy goes off the boundary
        north = (cy+1+step) * self.celly - y
        east = (cx+1+step) * self.cellx - x
        south = y - (cy - step) * self.celly
        west = x - (cx - step) * self.cellx

        boundary_distance = min([north, east, south, west])

        if step == 0:
            cells = [(cx,cy)]
        else:
            cells  = [(xi     , cy+step) for xi in range(cx-step, cx+step)] # North
            cells += [(cx+step, yi+1   ) for yi in range(cy-step, cy+step)] # East
            cells += [(xi+1   , cy-step) for xi in range(cx-step, cx+step)] # South
            cells += [(cx-step, yi     ) for yi in range(cy-step, cy+step)] # West
            # filter cells outside of neighborhood grid
            cells = [(cx,cy) for cx,cy in cells if
                        0 <= cx < self.Nx and
                        0 <= cy < self.Ny
                    ]

        return cells, boundary_distance*boundary_distance


    def __str__(self):
        out = []
        count = 100
        filled = 0
        max_count = 0
        for x, xlst in enumerate(self.nb):
            for y, lst in enumerate(xlst):
                if lst:
                    filled += 1
                    max_count = max(max_count, len(lst))
                for i in lst:
                    count -= 1
                    if count >= 0:
                        out.append('%s,%s - %s' % (x,y,i))
        out.insert(0,'%sx%s Neighborhood. Filled cells %s/%s max count %s' % (
            self.Nx,
            self.Ny,
            filled,
            self.Nx*self.Ny,
            max_count))
        return '\n'.join(out)


def find_n_closest(n,idx,loc,nb):
    assert len(loc) > n
    global pairing_count, cell_search_count

    x0,y0 = loc[idx]
    closest = []
    for step in xrange(sys.maxint):
        cells, boundary_distance2 = nb.get_neighbor_cells(x0,y0,step)
        cell_search_count += len(cells)
        if not cells:
            break
        for cx,cy in cells:
            for idx1 in nb.nb[cx][cy]:
                if idx1 == idx:
                    continue
                x1,y1 = loc[idx1]
                dx = x1-x0
                dy = y1-y0
                d2 = dx*dx + dy*dy
                pairing_count += 1
                closest.append((d2,idx1))
                closest.sort()
                closest = closest[:n]
        if len(closest) >= n:
            max_d2 = closest[-1][0]
            if max_d2 < boundary_distance2:
                return closest
    return closest


def find_n_closest_naive(n,idx,loc,nb):
    x0,y0 = loc[idx]
    closest = []
    for id2,(x1,y1) in enumerate(loc):
        if id2 == idx:
            continue
        dx = x1-x0
        dy = y1-y0
        d2 = dx*dx + dy*dy
        if not d2:
            continue
        closest.append((d2,id2))
        closest.sort()
        closest = closest[:n]

    return closest


def load(filename):
    loc = []
    fp = open(filename)
    try:
        for line in fp:
            line = line.strip()
            if not line:
                continute
            id,lat,lng = line.split()[:3]
            lat = float(lat)
            lng = float(lng)
            loc.append((lat,lng))
    finally:
        fp.close()
    return loc


def main(loc):
    nb = Neighborhood(loc)
    #print nb
    for i in range(len(loc)):
        closest = find_n_closest(3, i,loc, nb)
        #print i, '->', closest
        print '%s %s' % (i+1, ','.join(str(id+1) for d2,id in closest))


if __name__ =='__main__':
    filename = sys.argv[1]
    data = load(filename)
    main(data)
