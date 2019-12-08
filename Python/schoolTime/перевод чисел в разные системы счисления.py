# -*- coding: utf-8 -*-

m = int(0)
ans = int(0)
b = int(0)

print("-введите число-")
a = int(input())
print("-введите сис счисления числа-")
i1 = int(input())
print("-введите сис счисления, в которую хотите перевести число-")
i2 = int(input())

def check(string, i):
    c = 0
    for x in string:
        if int(x) >= i:
            c += 1
        else:
            pass
    return c

if (i1 == 10) and (i1 > 1 and i2 > 1) and check(str(a),i1)==0 :
    if a < i2:
        ans = a
    else:
        while a >= 1:
            """print(a, a%i2, m , ans)"""
            ans += (10 ** m)*(a % i2)
            a = (a // i2)
            m += 1
elif (i2 == 10) and (i1 > 1 and i2 > 1) and check(str(a),i1)==0:
    if a < i2:
        ans = a
    else:
        while a != 0:
            """print(a, m, ans, i2)"""
            ans += (i1 ** m)*(a % 10)
            a = a // 10
            m += 1
elif ((i1 and i2) != 10) and (i1 > 1 and i2 > 1) and check(str(a),i1)==0:
    if a < i2:
        ans = a
    else:
        while a != 0:
            b += (i1 ** m)*(a % 10)
            a = a // 10
            m += 1
        m = 0
        while b >= 1:
            """print(a, a%i2, m , ans)"""
            ans += (10 ** m)*(b % i2)
            b = (b // i2)
            m += 1

if (ans == 0) or check(str(a),i1)!=0:
    print("Вы что-то не так ввели, проверьте")
else:
    print("\nответ:", ans)
