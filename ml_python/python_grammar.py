# -*- coding: utf-8 -*-
"""
Created on Wed Apr  4 15:30:17 2018

@author: xiaodong
"""
def fib(n):
    a, b = 0, 1
    while a < n:
        print(a, end=' ')
        a, b = b, a + b
    print()

def fib2(n):
    result = []
    a, b = 0, 1
    while a < n:
        result.append(a)
        a, b = b, a + b
    return result

def f(a, L=[]):
    """ 
    default value is evaluated only once 
    """
    L.append(a)
    return L

word = 'python'
print(word[-1])

"""
 indices
 +---+---+---+---+---+---+
 | P | y | t | h | o | n |
 +---+---+---+---+---+---+
 0   1   2   3   4   5   6
-6  -5  -4  -3  -2  -1
"""

# if/else
# x = int(input("please input an integer: "))
x = 10
if x < 0:
    x = 0
    print("negative number")
elif x == 0:
    print("Zero")
else:
    print("More")
    
# for/while has else clause
words = ["cat", "dog", "python"]
for w in words:
    print(w, len(w))
else:
    pass # pass does nothing

""" range is not a sequence, it is a iterator in order to save space. """
for i in range(5,10):
    print(i)

""" list operation """
words.append("turtle") # append single data
words.extend(["lion","tiger"]) # append multiple data
words.insert(1, "fish")
words.pop(2)
print("words.count=" + str(words.count("cat")))
words.sort()
words.reverse()
words.clear()
fib(10)
fib2(10)

""" will not clear L """
print(f(1))
print(f(2))
print(f(3))


""" lambda expression"""
pairs = [(1,'one'), (2, 'two'), (3, 'three'), (4, 'four')]
pairs.sort(key=lambda pair: pair[1])
print(pairs)

""" tuple is immutable """
t = 123, 'and', 456
""" set """
empty_set = set() # create empty set
basket = {'apple', 'orange', 'apple', 'peal', 'orange', 'banana'}
print(basket)
print('orange in basket?' + str('orange' in basket))
print('bear in basket?' + str('bear' in basket))
# demo union ...
a = set('abcdfgh')
b = set('cdefhijk')
print('a-b:'+str(a - b))
print('aUb:'+str(a | b))
print('a&b:'+str(a & b))
print('a^b:'+str(a ^ b))

""" dict """
tel = {'jack':1234, 'rose':4531, 'snape':8872}
tel['jack'] = 1038
print(tel)
del tel['snape']
print(tel)
tel['ron'] = 1048
print(list(tel.keys()))
print(dict(ron=1,harry=2,snape=4))
for k,v in tel.items():
    print(k,v)
    
questions = ['name', 'job', 'expertise']
answers = ['cai', 'engineer', 'sensors']
for q,a in zip(questions, answers):
    print('What is your {0}? It is {1}.' .format(q,a))
    
import fibo
print(fibo.fib(10))

with open('README.md') as f:
    read_data = f.read()
print(read_data)