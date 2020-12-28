list = [31, 41, 59, 26, 41, 58]

isAscend = False
print(list)
i = 1
len = len(list)
for i in range(1, len):
    key = list[i]
    j = i - 1
    while j >= 0 and (list[j] > key if isAscend else list[j] < key):
        list[j + 1] = list[j]
        j -= 1
    list[j + 1] = key

print(list)
