#!/usr/bin/env python3

def Fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    elif n > 1:
        return Fib(n - 1) + Fib(n - 2)

def Luc(n):
    if n == 0:
        return 2
    elif n == 1:
        return 1
    elif n > 1:
        return Luc(n - 1) + Luc(n - 2)

def Pair(n):
    return Fib(n + 2) - Fib(n - 2)


def main():
    print("Fibonacci Sequence at 7 is ", Fib(7))
    print("Lucas Sequence at 6 is ", Luc(6))
    print("Pair Sequence at 6 is ", Pair(6))

if __name__ == "__main__":
    main()