import sys
from collections import defaultdict, deque

FRIEND_ID = 1009

class BipartiteGraph:

    def __init__(self, edges=[]):
        self.edges = set(edges)
        self.L = set()
        self.R = set()
        self.edge_map = defaultdict(set)
        for (l,r) in self.edges:
            self.L.add(l)
            self.R.add(r)
            self.edge_map[l].add(r)
            self.edge_map[r].add(l)
    
    def remove_vertice(self, vertice):
        edges = [ edge
                  for edge in self.edges
                  if vertice not in edge ]
        return BipartiteGraph(edges)
    
    def neighbors(self,v):
        return self.edge_map[v]
    
    def is_matching(self,g):
        vertices = set()
        for edge in self.edges:
            if edge not in g.edges:
                return False
            (l,r) = edge
            if l in vertices or r in vertices:
                return False
            vertices.add(l)
            vertices.add(r)
        return True
    
    @staticmethod
    def load_from_stream(stream):
        stream.readline()
        # we don't care much about the first line actually
        edges = set()
        for edge_line in stream.xreadlines():
            (a,b) = map(int,edge_line.split(" "))
            edge = (a,b) if a<b else (b,a)
            edges.add(edge)
        return BipartiteGraph(edges)
    
    def difference(self, subgraph):
        return BipartiteGraph(self.edges.difference(subgraph.edges))

def follow(seed, edge_set):
    if len(seed)==0:
        return set()
    return set.union(*[ edge_set.edge_map.get(v,set()) for v in seed ])

def bfs(g,m):
    q = deque()
    # the layer id, d stands for distance
    d = {}
    # we begin from point on the left
    # which are unmatched at the moment.
    for l in g.L:
        if l not in m:
            d[l] = 0
            q.append(l)
    
    found = False
    while len(q) > 0:
        l = q.popleft()
        #assert l in d
        # l is in L
        for r in g.neighbors(l):
            if r not in m:
                # right layer with unmatched vertex!
                # hurray
                d[ None ] = d[l] + 1
                found = True
            else:
                l2 = m[r]
                if l2 not in d:
                    # not already visited!
                    d[ l2 ] = d[l] + 1
                    q.append(l2)
    if found:
        # augmenting path do exists!
        return d
    else:
        return None

def dfs(g, m, d, v):
    if v is None:
        return True
    else:
        for u in g.neighbors(v):
            m_u = m.get(u,None)
            if m_u in d and d[ m_u ] == d[v] + 1 and dfs(g, m, d, m_u):
                m[u] = v
                m[v] = u
                return True
        del d[v]
        return False

def is_matching(m):
    for (k,v) in m.items():
        if m[v] != k:
            return False
    return True


def match(g):
    m = {}
    while True:
        d = bfs(g,m)
        if d is None:
            # termination!
            edges = set()
            for (l,r) in m.items():
                if l < r:
                    edges.add((l,r))
            return BipartiteGraph(edges)
        else:
            for v in g.L:
                if v not in m:
                    dfs(g,m,d,v)


def minimum_vertex_cover_knowing_matching(g, match):
    unmatch = g.difference(match)
    T = g.L.difference(match.L)
    T_L = T
    while True:
        S = len(T)
        T_R = follow(T_L, unmatch)
        T_L = follow(T_R, match)
        T = set.union(T, T_L, T_R)
        if len(T) == S:
            break
    return set.union( g.L.difference(T), g.R.intersection(T) )

def is_cover(vertices, g):
    for (l,r) in g.edges:
        if not (l in vertices or r in vertices):
            return False
    return True

def minimum_vertex_cover(g):
    matching = match(g)
    neighbors = dict( [ (l,g.edge_map[l]) for l in g.L ] )
    #matching2 = bipartiteMatch(neighbors)
    #assert len(matching.edges) == len(matching2[0])
    cover = minimum_vertex_cover_knowing_matching(g, matching)
    assert is_cover(cover, g)
    return cover

def minimum_vertex_cover_with_friend_if_possible(g):
    cover = minimum_vertex_cover(g)
    g_without_friend = g.remove_vertice(FRIEND_ID)
    cover_with_friend = set.union( minimum_vertex_cover(g_without_friend), [FRIEND_ID] )
    assert len(cover_with_friend) >= len(cover)
    if len(cover_with_friend) == len(cover):
        return cover_with_friend
    else:
        return cover


if __name__ == "__main__":
    g = BipartiteGraph.load_from_stream(sys.stdin)
    cover = minimum_vertex_cover_with_friend_if_possible(g)
    print len(cover)
    for vertex in cover:
        print vertex
