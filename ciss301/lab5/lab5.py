#!/usr/bin/env python3

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 5
"""

class Graph:
    def __init__(self, vertices=None, edges=None):
        self.vertices = {}
        self.traversed = []
        self.edges = edges
        if vertices is None:
            vertices = []
            for edge_pair in edges:
                if edge_pair[0] not in vertices:
                    vertices.append(edge_pair[0])
                elif edge_pair[1] not in vertices:
                    vertices.append(edge_pair[1])
        for edge_pair in self.edges:
            for edge in edge_pair:
                if edge not in vertices:
                    return

        for name in vertices:
            self.vertices[name] = Vertice(name)
        
    def connect_edges(self):
        for edge_pair in self.edges:
            self.vertices[edge_pair[0]].next_vertice.append(self.vertices[edge_pair[1]])
            self.vertices[edge_pair[1]].prev_vertice.append(self.vertices[edge_pair[0]])
    
    def check_reflexive(self):
        target = len(self.vertices)
        count = 0
        for v in self.vertices.values():
            if v in v.next_vertice:
                count += 1
        return count ==  target

    def check_symmetric(self):
        target = len(self.edges)
        count = 0
        for v in self.vertices.values():
            for n in v.next_vertice:
                if v in n.next_vertice:
                    count += 1
                if n in n.next_vertice:
                    count += 1

        return count == target
    
    def check_transitive(self):
        target = 0
        count = 0
        for v in self.vertices.values():
            v.show_next_connections()
            v.show_prev_connections()
            for n in v.next_vertice:
                target += 1
                for n2 in n.next_vertice:
                    if v in n2.prev_vertice:
                        count += 1

        print(count, target)
        return count == target


class Vertice:
    def __init__(self, name):
        self.name = name
        self.next_vertice = []
        self.prev_vertice = []
    
    def show_next_connections(self):
        if len(self.next_vertice) > 0:
            for n in self.next_vertice:
                print("%s -> %s" % (self.name, n.name))
        else:
            return None

    def show_prev_connections(self):
        if len(self.prev_vertice) > 0:
            for p in self.prev_vertice:
                print("%s <- %s" % (self.name, p.name))
        else: 
            return None



def Reflexive(L, S):
    """
    Input: a lists of pairs, L, and the set S over which the relation is defined.  
    Interpreting the input as a binary relation, return True if it is reflexive and False otherwise.
    Every vertice must have link to self
    """
    graph = Graph(S, L)
    graph.connect_edges()
    return graph.check_reflexive()


def Symmetric(L):
    """
    Input: a lists of pairs, L, and the set S over which the relation is defined.  
    Interpreting the input as a binary relation, return True if it is symmetric and False otherwise.
    Every vertice must point to something that points back to original vertice; A -> B -> A
    """
    graph = Graph(edges=L)
    graph.connect_edges()
    return graph.check_symmetric()

def Transitive(L):
    """
    Input: a lists of pairs, L. Interpreting the input as a binary relation, 
    return True if it is transitive and False otherwise.
    A -> B, B -> C, A -> C
    """
    graph = Graph(edges=L)
    graph.connect_edges()
    return graph.check_transitive()

def main():
    print(Reflexive([['a','a'],['b','a'],['b','b'], ['c','a'],['c','c']], ['a','b','c']))
    print(Symmetric([['a','b'],['b','a']]))
    print(Transitive([['a','b'],['b','c'],['a','c']]))
if __name__ == "__main__":
    main()