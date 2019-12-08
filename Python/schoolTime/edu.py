"""
a = True
b = False
w = a and b or not a and not b
print(w)
print('chetnoe ' * 2)
"""
"""
a = 5
b = 3
print(a + b)
print(a - b)
print(a * b)
print(a ** b) #степень
print(a // b) #целочисл дел
print(a % b) #остаток
print(a / b) #просто деление
print(5e-2) #умножить на десять в -2
"""
"""
if условие_1:
    что то
elif условие_2:
    что то
else: что то
"""
"""
a = int(input('введите мин время сна '))
b = int(input('введите макс время сна '))
h = int(input('введите сколько вы спите '))

if a <= h <= b:
    print('Это нормально')
elif h < a:
    print('Недосып')
else:
    print('Пересып')
"""
"""
year = int(input('введите год, определим високос или нет '))
if year % 4 == 0 and year % 100 != 0  or year % 400 == 0:
    print('Високосный')
else: print('Обычный')
"""
'''
print('string')
print("string")
print('multiple lines string')
print("""multiple lines string with double qoutes""")
w = 'abc' + 'a'
print(w)
print(len(w))
print('abc' == "abc") #True
print('abc' < 'ac') #True
print('abc' > 'ab') #True
print(' First line', '\n\n', 'Last line')
print("123"+"42")
'''
"""
a = float(input())
b = float(input())
c = float(input())
p = (a + b + c)/2
print((p*(p-a)*(p-b)*(p-c)) ** (1/2))
"""
"""
a = int(input())
print(-15<a<=12 or 14<a<17 or 19<=a)
"""
"""
a = float(input())
b = float(input())
string = str(input())
if string == 'mod':
    if b == 0: print('Деление на 0!')
    else: print(a % b)
if string == 'div':
    if b == 0: print('Деление на 0!')
    else: print(a // b)
if string == '/':
    if b == 0: print('Деление на 0!')
    else: print(a / b)
if string == '*':
    print(a*b)
if string == '+':
    print(a+b)
if string == '-':
    print(a-b)
if string == 'pow':
    print(a ** b)
"""
"""
for i in range(4):
    print(i*i)
range(5) #от 0 вкл до 5 не включая
range(5,7) #от 5 вкл до 7 не включая
range(0,10,2) #шаг добавился = 2

print('baa ',end='')
print('baa')

string =  str('0123456')
print(string)
print(string[2])
"""
