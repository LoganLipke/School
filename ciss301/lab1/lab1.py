#!/usr/bin/env python3

"""
Author: Logan Lipke
CISS 301 Winter 2021
Lab 1
"""


def Fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    elif n > 1:
        return Fib(n - 1) + Fib(n - 2)
    else:
        raise ValueError("Please choose a non-negative number")

def Luc(n):
    if n == 0:
        return 2
    elif n == 1:
        return 1
    elif n > 1:
        return Luc(n - 1) + Luc(n - 2)
    else:
        raise ValueError("Please choose a non-negative number")

def Pair(n):
    return Fib(n + 2) - Fib(n - 2)


def main():
    for i in range(10):
        print("=====================================================")
        print("i =", i)
        try:
            print("\tFib =", Fib(i), end=" ")
        except:
            pass
        try:
            print("\tLuc =", Luc(i), end=" ")
        except:
            pass
        try:
            print("\tPair =", Pair(i), end=" ")
        except:
            pass
        print("")
        

if __name__ == "__main__":
    main()