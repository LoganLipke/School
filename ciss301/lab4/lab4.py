#!/usr/bin/env python3

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 4
"""

class Graph:
    def __init__(self, vertices, edges):
        self.vertices = {}
        self.traversed = []
        self.edges = edges
        for edge_pair in self.edges:
            for edge in edge_pair:
                if edge not in vertices:
                    raise ValueError("Attempted to create edge with non-existent vertice")

        for name in vertices:
            self.vertices[name] = Vertice(name)
        
    def connect_edges(self):
        for edge_pair in self.edges:
            self.vertices[edge_pair[0]].next_vertice.append(self.vertices[edge_pair[1]])
            self.vertices[edge_pair[1]].prev_vertice.append(self.vertices[edge_pair[0]])

    def check_tree(self):
        self.traversed.append(list(self.vertices.values())[0])
        for _,v in self.vertices.items():
            # v.show_next_connections()
            # v.show_prev_connections()
            for n in v.next_vertice:
                if n in self.traversed:
                    # print(n.name)
                    return False
                else:
                    self.traversed.append(n)

            for p in v.prev_vertice:
                if p not in self.traversed:
                    # print(p.name)
                    return False
        return True
            

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

def Tree(vertices, edges):
    graph = Graph(vertices, edges)
    graph.connect_edges()
    return graph.check_tree()

def main():
    print(Tree(["a","b","c","d","e","f"], [["a","b"], ["a","e"],["b","c"],["c","d"],["d","f"]]))
    print(Tree(['a','b','c'], [['a','b'],['a','c'],['b','c']]))
    print(Tree(['a','b','c','d','e'], [['a','b'],['a','c'], ['d','e']]))
    print(Tree(["a","b","c","d","e"], [["a","b"], ["a","e"],["b","c"],["c","d"],["d","e"]]))
if __name__ == "__main__":
    main()