#!/usr/bin/env python3

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 6
"""

def is_even(n):
    if n == 0:
        return True
    else:
        return is_odd(n-1)

def is_odd(n):
    if n == 0:
        return False
    else:
        return is_even(n-1)

def set_equal(set_a, set_b):
    for i in set_a:
        if not isinstance(i, list) and i not in set_b:
            return False
        else:
            return set_subset(set_a, set_b)

def set_subset(set_a, set_b):
    target = len(set_b)
    count = 0
    for i in set_a:
        if isinstance(i, list):
            for j in set_b:
                if isinstance(j, list):
                    if set_equal(i, j):
                        return True
        else:
            if i in set_b:
                count += 1
    if count == target:
        return True
    else:
        return False

def main():
    print(set_equal([1,[2,[3,4]]],[[[4,3],2],1]))                               # True
    print(set_equal([1,[2,5,[3,[4,6]]]],[[[[4,6],3],5,2],1]))                   # True
    print(set_equal([[7,8,9],1,[[5,6],2,[3,4]]],[[[4,3],[5,6],2],1,[7,8,9]]))   # True
    print(set_equal([1,[2,[3,4]]],[[4,3,2],1]))                                 # False
    print(set_equal([1,[2,[3,4]]],[[4,3],2,1]))                                 # False
    
    
if __name__ == "__main__":
    main()