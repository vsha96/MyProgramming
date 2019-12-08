# -*- coding: utf-8 -*-

def number_of_ways(tree,id): # размер таблицы смежности, таблица смежности, id последней точки
    count = 0 #кол-во смежных вершин
    number = 0 #кол-во путей до вершины
    temp = 0
    ids = [] # id смежных вершин
    for i in range(len(tree)):
        if id in tree[i]:
            count += 1
            ids.append(i)
    if count == 0:
        return number + 1
    else:
        for i in range(len(ids)):
            temp += number + number_of_ways(tree, ids[i])
        return temp


a, b, c, d, e, f, g = range(7)
tree = [
    [b, c], #a
    [d, e], #b
    [b, f], #c
    [f, g], #d
    [g], #e
    [g], #f
    [] #g
]

print(number_of_ways(tree,6))

"""
id = 5
ids = []
for i in range(len(tree)):
    if id in tree[i]:
        ids.append(i)

print(ids)
"""