# -*- coding: utf-8 -*-
import quicksort

l = quicksort.sort(input())

a = ''.join(l)
b = a[::-1]

print(a)
print(b)

cn = ''
c = str(int(b) - int(a))
print(c)
print(quicksort.sort(c))

while c != cn:
    cn = c
    a = ''.join(quicksort.sort(c))
    b = a[::-1]
    c = str(int(b) - int(a))


print(c)

