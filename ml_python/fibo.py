# -*- coding: utf-8 -*-
"""
Created on Tue Apr 17 16:47:44 2018

@author: xiaodong
"""
def fib(n):
    a, b = 0, 1
    while b < n:
        print(b, end=' ')
        a, b = b, a+b
    print()
    
def fib2(n):
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a+b
    return result
