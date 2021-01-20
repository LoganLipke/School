#!/usr/bin/env python3
import math

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 3
"""

def Jug(jug_size1, jug_size2, goal_amount):
    if jug_size1 > jug_size2:
        temp = jug_size1
        jug_size1 = jug_size2
        jug_size2 = temp
    gcd = math.gcd(jug_size1, jug_size2)
    if not (goal_amount % gcd) and (jug_size1 > goal_amount or jug_size2 > goal_amount):
        fill_jugs(0, 0, jug_size1, jug_size2, goal_amount)
    else:
        raise ValueError("Target amount (%d) cannot be made with jug values (%d, %d)" % (goal_amount, jug_size1, jug_size2))

def fill_jugs(jug1, jug2, jug_size1, jug_size2, goal_amount):
    if jug2 == goal_amount:
        print("(%d, %d)" % (jug1, jug2))
        return
    else:
        if jug1 <= 0:
            jug1 = jug_size1
        elif jug2 <= 0:
            jug2 = jug1
            jug1 = 0
        elif jug2 == jug_size2:
            jug2 = 0
        elif jug1 > 0 and jug2 > 0:
            cap = jug_size2 - jug2
            if cap < jug1:
                jug2 += cap
            else:
                jug2 += jug1
            if jug1 - cap > 0:
                jug1 -= cap
            else:
                jug1 = 0
        print("(%d, %d)" % (jug1, jug2), end=" -> ")
        fill_jugs(jug1, jug2, jug_size1, jug_size2, goal_amount)
    

def main():
    Jug(21, 26, 3)
    Jug(4, 3, 2)
    
if __name__ == "__main__":
    main()