#!/usr/bin/env python3

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 7
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
                if edge_pair[1] not in vertices:
                    vertices.append(edge_pair[1])
        for edge_pair in self.edges:
            for edge in edge_pair:
                if edge not in vertices:
                    return

        for name in vertices:
            self.vertices[name] = Vertice(name)

    def connect_edges(self):
        for edge_pair in self.edges:
            self.vertices[edge_pair[0]].connections.append(self.vertices[edge_pair[1]])
            self.vertices[edge_pair[1]].connections.append(self.vertices[edge_pair[0]])


    def check_color(self):
        color_count = 1
        used_colors = []
        for vertice in self.vertices.values():
            con_colors = []
            cur_color = 1
            for n in vertice.connections:
                con_colors.append(n.color)
            while cur_color in con_colors:
                cur_color += 1
                if cur_color not in used_colors:
                    color_count += 1
                    used_colors.append(cur_color)
            vertice.color = cur_color
        return color_count

    def check_euler(self):
        path = []
        num_odd_degree = 0
        start = None
        for vertice in self.vertices.values():
            if (len(vertice.connections)) % 2 != 0:
                num_odd_degree += 1
                start = vertice
        if num_odd_degree == 0 or num_odd_degree == 2:
            if num_odd_degree == 0:
                start = list(self.vertices.values())[0]
            while len(start.connections) != 0:
                i = 0
                temp = start
                if len(start.connections[i].connections) > 0:
                    start = start.connections[i]
                    path.append([temp.name, start.name])
                    temp.remove_connection(start)
                    start.remove_connection(temp)
                    i = 0
                else:
                    i += 1
        return path

    def check_hamilton(self):
        for vertice in self.vertices.values():
            start = vertice
            path = []
            visited = []
            i = 0
            while len(path) != len(self.vertices)-1:
                if start not in visited:
                    visited.append(start)
                if i < len(start.connections):
                    if start.connections[i] not in visited:
                        path.append([start.name, start.connections[i].name])
                        start = start.connections[i]
                        i = 0
                    else:
                        i += 1
                else:
                    start = self.vertices[path[-1][0]]
                    path.pop()
                    i = 0
                    if len(path) == 0 and len(start.connections) > i+1:
                        visited = []
                        i += 1
                    else:
                        break
            if len(path) == len(self.vertices)-1:
                return path
        if len(path) != len(self.vertices)-1:
            path = []
        return path


class Vertice:
    def __init__(self, name):
        self.name = name
        self.connections = []
        self.color = 0
    

    def remove_connection(self, connection):
        for vertice in self.connections:
            if vertice.name == connection.name:
                self.connections.remove(vertice)
    
    def add_connection(self, connection):
        if connection not in self.connections:
            self.connections.append(connection)

    def show_connections(self):
        if len(self.connections) > 0:
            for n in self.connections:
                print("%s -> %s" % (self.name, n.name))
        else:
            return None

def Coloring(edges):
    graph = Graph(edges=edges)
    graph.connect_edges()
    return graph.check_color()

def Euler(edges):
    graph = Graph(edges=edges)
    graph.connect_edges()
    return graph.check_euler()

def Hamilton(edges):
    graph = Graph(edges=edges)
    graph.connect_edges()
    return graph.check_hamilton()

def main():
    #       =======INPUT=======                                                                       ========OUTPUT=======
    print("=======COLORING=======")                                                                 # =======COLORING=======
    print(Coloring([ [1,2], [1,3], [3,4], [3,5], [4,5], [2,5] ]))                                   # 3
    print(Coloring([ [1,2], [1,4], [1,5], [2,3], [2,5], [3,4], [3,5], [4,5], [3,1]]))               # 4
    print(Coloring([ [1,2], [2,3], [3,4], [4,7], [7,6], [6,5], [5,1] ]))                            # 3
    print(Coloring([ [1,2], [2,3], [3,4], [4,7], [7,6], [6,5], [5,1], [4,8], [6,8] ]))              # 3
    print(Coloring([ [1,2], [2,3], [3,4], [4,7], [7,9], [7,6], [9,5], [5,1], [2,8], [8,6] ]))       # 3
    print("=======EULER=======")                                                                    # =======EULER======= 
    print(Euler([ [1,2], [1,3], [3,4], [3,5], [4,5], [2,5] ]))                                      # [[5, 3], [3, 1], [1, 2], [2, 5], [5, 4], [4, 3]]
    print(Euler([ [1,2], [2,3], [3,4], [4,7], [7,6], [6,5], [5,1] ]))                               # [[1, 2], [2, 3], [3, 4], [4, 7], [7, 6], [6, 5], [5, 1]]
    print(Euler([ [1,2], [2,3], [3,4], [4,7], [7,6], [6,5], [5,1], [4,8], [6,8] ]))                 # [[6, 7], [7, 4], [4, 3], [3, 2], [2, 1], [1, 5], [5, 6], [6, 8], [8, 4]]
    print(Euler([ [1,2], [2,3], [3,4], [4,7], [7,9], [7,6], [9,5], [5,1], [2,8], [8,6] ]))          # [[7, 4], [4, 3], [3, 2], [2, 1], [1, 5], [5, 9], [9, 7], [7, 6], [6, 8], [8, 2]]
    print(Euler([[1,2],[1,3],[1,4]]))                                                               # []
    print("=======HAMILTON=======")                                                                 # =======HAMILTON=======
    print(Hamilton([ [1,2], [1,3], [3,4], [3,5], [4,5], [2,5] ]))                                   # [[1, 2], [2, 5], [5, 3], [3, 4]]
    print(Hamilton([ [1,2], [2,3], [3,4], [4,7], [7,6], [6,5], [5,1] ]))                            # [[1, 2], [2, 3], [3, 4], [4, 7], [7, 6], [6, 5]]
    print(Hamilton([ [1,2], [2,3], [3,4], [4,7], [7,6], [6,5], [5,1], [4,8], [6,8] ]))              # [[3, 2], [2, 1], [1, 5], [5, 6], [6, 7], [7, 4], [4, 8]]
    print(Hamilton([ [1,2], [2,3], [3,4], [4,7], [7,9], [7,6], [9,5], [5,1], [2,8], [8,6] ]))       # [[4, 3], [3, 2], [2, 1], [1, 5], [5, 9], [9, 7], [7, 6], [6, 8]]
    print(Hamilton([ [1,2], [2,3], [3,4], [4,7], [7,6], [5,2] ]))                                   # []


    
if __name__ == "__main__":
    main()