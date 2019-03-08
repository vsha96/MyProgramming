# -*- coding: utf-8 -*-

"функция ввода таблицы смежности"
def input_array(size):
    print("введите таблицу смежности")
    array = []
    for i in range(size):
        text = input().split()
        array.append([int(j) for j in text])
    return array
def output_array(array):
    for i in range(len(array)):
        for j in range(len(array[i])):
            print(array[i][j], end=' ')
        print()

def Dijkstra(size, chosen, matrix): # размер таблицы смежности, выбранная точка (<size) !!!нумерация нач с 0!!!, таблица смежности
    inf = 10 ** 10
    if chosen >= size:
        print("неправильно выбранна точка старта, size = ", size," chosen = ", chosen)
        return -1
    #------- несуществующие ребра = INF -------
    for i in range(size):
        for j in range(size):
            if matrix[i][j] == 0: matrix[i][j] = inf
    # --------------
    valid = [True]*size
    weight = [inf]*size
    weight[chosen] = 0 #источник

    for i in range(size):
        id_min = -1
        min = inf + 1
        for i in range(size):
            if valid[i] and weight[i] < min:
                min = weight[i]
                id_min = i
        for i in range(size):
            if weight[id_min] + matrix[id_min][i] < weight[i]:
                weight[i] = weight[id_min] + matrix[id_min][i]
        valid[id_min] = False
    return weight

size = int(input("введите размер, а затем таблицу смежности "))
cities = input_array(size)
print(Dijkstra(size,0,cities))