# -*- coding: utf-8 -*-
import csv
import time

def read_time():
    file = open('10ф1 Thu.csv')
    f = csv.reader(file)
    h = int(time.strftime('%H'))
    m = int(time.strftime('%M'))
    count_of_class = 0

    '''стартовая позиция чтения дня, сейчас должна принять нуль'''
    start = 0


    f = list(f)
    print(f,"\n")

    for i in range(start,len(f)):
        count_of_class += 1
    print(count_of_class)

    for i in range(start , start + count_of_class):
        pass






print(read_time())
