# -*- coding: utf-8 -*-
import codecs
import sys

f = codecs.open('input', 'r+', encoding='utf-8')
line = f.readlines()
line[0] = line[0].rstrip('\n')
line[1] = line[1].rstrip('\n')
if line[0].lower() == line[1].lower():
    print(1)
else:
    print(0)
f.close()