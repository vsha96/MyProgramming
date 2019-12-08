# -*- coding:utf-8 -*-
import codecs
import nltk
from nltk.corpus import stopwords
from collections import Counter
from pymystem3 import Mystem

f = codecs.open('train.csv', 'r', encoding='utf-8')
result_text = []
line = f.readlines()
stopwords = stopwords.words('russian')
for i in range(len(line)):
    line[i] = line[i].strip('\n').strip().strip('\a').strip('\b').strip('\f').strip('\t').strip('\v')
for i in range(len(line)):
    line[i] = line[i].split(',')
for i in range(1, len(line)):
    line[i][1] = line[i][1].split()
    if line[i][2] == '15':
        for j in range(len(line[i][1])):
            if line[i][1][j] not in stopwords:
                result_text.append(line[i][1][j])



for i in range(len(result_text)):
    result_text[i] = result_text[i].lower()

m = Mystem()
for i in range(len(result_text)):
    result_text[i] = m.lemmatize(result_text[i])

result_text_2 = []
for i in range(len(result_text)):
    result_text_2.append(result_text[i][0])
array = Counter(result_text_2)
print(array)