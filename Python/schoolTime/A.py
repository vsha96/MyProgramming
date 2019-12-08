# -*- coding: utf-8 -*-

size = int(input())

def input_array(size):
    array = [int(j) for j in input().split()]
    return array

scroll = input_array(size)

s = 0

for i in range (len(scroll)):
   s += scroll[i]*(size-i)*(i+1)

print(s)
