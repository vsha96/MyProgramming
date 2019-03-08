# -*- coding: utf-8 -*-
import codecs

f = codecs.open('input', 'r', encoding='utf-8')
text = f.read()
f.seek(0)
line = f.readlines()
line[0] = line[0].strip('\r').strip('\n').strip()
line[1] = line[1].strip('\r').strip('\n')
result = line[1].count(line[0])
print(result)
f.close()