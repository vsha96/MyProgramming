# -*- coding: utf-8 -*-
import csv

def read_timetable(number):
    file = open('10.csv')
    f = csv.reader(file)
    f = list(f)
    file.close()
    print(f)
    result = ''
    a = -1
    b = -1
    for i in range(len(f)):
        if f[i][0] == number:
            a = i
        elif f[i][0] == str(int(number) + 1):
            b = i
        else: return 'read_timetable ERROR'
    if a != -1 and b != -1:
        for i in range(a+1,b-1):
            result += f[i][0] + '\n'
    return result

#ошибка в чтение расписания
print(read_timetable('1'))

def read_class(numberofclass, numbersplit):
    number = '' + numbersplit.split()[0]
    file = open(number+'.csv')
    f = csv.reader(file)
    f = list(f)

    n = f[0].index(numberofclass)

    '''
    for i in range(len(f)):
        if number_begin in f[i]:
            index_begin = i
        else:
            index_begin = 0
    for i in range(len(f)):
        if number_end in f[i]:
            index_end = i
        else:
            index_end = 0
    '''

    result = ''

    for i in range(len(f)):
        if f[i][n] != '':
            result += f[i][n] + '\n'
    file.close()
    return result
