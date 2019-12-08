
a = [2,3]

for i in range(2,10):
    b = 3*a[i-1]-2*a[i-2]
    a.append(b)
print(a)