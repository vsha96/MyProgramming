# -*- coding:utf-8 -*-
import codecs
import nltk
from nltk.corpus import stopwords
from collections import Counter
from pymystem3 import Mystem

#f = codecs.open('train.csv', 'r', encoding='utf-8')

text = 'погашение'
text = Mystem().lemmatize(text)

print(text)