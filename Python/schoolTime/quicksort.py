def sort(array):
    less = []
    equal = []
    greater = []

    if len(array) > 1:
        item = array[0]
        for x in array:
            if x < item:
                less.append(x)
            if x == item:
                equal.append(x)
            if x > item:
                greater.append(x)
        return sort(less)+equal+sort(greater)
    else:
        return array

"""
arr = input()

print(sort(arr))
"""