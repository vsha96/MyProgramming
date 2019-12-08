# coding: utf8
import codecs
import nltk
import sys
f = codecs.open('input', 'r', encoding='utf-8')
text = f.read()
text = text.strip('\a').strip('\b').strip('\f').strip('\t').strip('\v').strip('\n')


