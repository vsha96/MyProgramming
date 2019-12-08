# -*- coding: utf-8 -*-
import codecs

s = [".", ",", "!", "?", ":", ";", "-", '"', "'", "(", ")"]
f = codecs.open('input', 'r', encoding='utf-8')
text = f.read().strip('\n').strip().strip('\a').strip('\b').strip('\f').strip('\t').strip('\v')
for i in s:
    text = text.replace(i, ' ')
text = text.split()
print(len(text))