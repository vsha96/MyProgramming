# -*- coding: utf-8 -*-

text = input()
text = text.split()

n = int(text[0])
m = int(text[1])

def input_array(size):
    array = []
    for i in range(n):
        array.append(str(input()))
    return array

voc = input_array(n)
words = input_array(m)
print(voc)
print(words)

for i in range(len(words)):
    word = words[i]
    if word in voc:
        print(word)
    elif word:
        y = []
        mistake = 0
        for j in range(len(voc)):
            if len(voc[i]) == len(word):
                y.append(voc[i])
        print(y)
        for i in range(len(y)):
            wordvoc = y[i]
            for j in range(len(word)):
                if word[j] != wordvoc[j]:
                    mistake += 1
            if mistake == 1:
                print(wordvoc)
            else:
                print('?')

    else:
        print('?')

