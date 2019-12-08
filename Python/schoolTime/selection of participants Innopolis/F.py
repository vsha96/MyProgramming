# -*- coding:utf-8 -*-
import codecs
from collections import Counter
import sys

f = codecs.open('input', 'r', encoding='utf-8')
text_list = f.read().strip('\n').strip().strip('\a').strip('\b').strip('\f').strip('\t').strip('\v')
f.seek(0)
text_array = f.read().strip('\n').strip().strip('\a').strip('\b').strip('\f').strip('\t').strip('\v')
text_list = text_list.lower()
text_array = text_array.lower()
text_list = text_list.split()
array = Counter(text_list)
to_find_list = array.most_common(1)
if to_find_list[0][1] == 1:
    print(-1)
    sys.exit()
to_find_word = to_find_list[0][0]
for i in range(len(text_list)):
    if text_list[i] == to_find_word:
        print(i)
        sys.exit()