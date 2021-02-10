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
        elif isinstance(i, list):
            for j in set_b:
                if isinstance(j, list):
                    set_subset(i, j)

def set_subset(sub_a, sub_b):
    print(sub_a, sub_b)
    for i in sub_a:
        print("sub", i, sub_b)
        if not isinstance(i, list) and i not in sub_b:
            return False
        elif isinstance(i, list):
            for j in sub_b:
                if isinstance(j, list):
                    set_equal(i, j)
        else:
            return True



def main():
    print(set_equal([1,[2,[3,4]]],[[[4,3],2],1]))
    
if __name__ == "__main__":
    main()