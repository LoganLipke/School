#!/usr/bin/env python3

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 2
"""

def One(n):
    """Returns sum of squares up to n, iteratively"""
    sum = 0
    for i in range(1, n+1):
        sum += i ** 2
    return sum

def Two(n):
    """Returns sum of squares up to n, recursively"""
    return TwoExtra(n, 0)

def TwoExtra(n, sum):
    """Helper function for Two, returns sum of squares calculated using recursion"""
    if n == 0:
        return sum
    else:
        return TwoExtra(n - 1, sum + n ** 2)
        
def Three(n):
    """Returns square of sums up to n, iteratively"""
    sum = 0
    for i in range(1,n+1):
        sum += i
    return sum ** 2

def Four(n):
    """Returns square of sums up to n, recursively"""
    return FourExtra(n, 0)

def FourExtra(n, sum):
    """Helper function for Four, returns square of sums calculated using recursion"""
    if n == 0:
        return sum ** 2
    else:
        return FourExtra(n - 1, sum + n)

def main():
    print("One: ", One(5))
    print("Two: ", Two(5))
    print("Three: ", Three(5))
    print("Four: ", Four(5))
    
if __name__ == "__main__":
    main()