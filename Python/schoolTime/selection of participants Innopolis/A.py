# coding: utf8
import codecs

f = codecs.open('input', 'r', encoding='utf-8')
line = f.readlines()
for i in range(len(line)):
    line[i] = line[i].strip('\n').strip()
n = int(line[0])
print(len(line[n + 1]))