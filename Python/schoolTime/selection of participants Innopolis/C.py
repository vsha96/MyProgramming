# coding: utf8
import codecs

f = codecs.open('input', 'r', encoding='utf-8')
text = f.read()
#print(text.split(',' or ' '))
print(len(text.split()))
