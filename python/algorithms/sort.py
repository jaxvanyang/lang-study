# TODO: add type check
def insertion_sort(arr: list, reverse: bool = False, _cmp=lambda a, b, reverse: a < b if reverse else a > b):
    """
    在原数组上操作
    默认按升序排序
    """
    size = len(arr)
    for i in range(1, size):
        key = arr[i]
        p = i - 1
        while p >= 0 and _cmp(arr[p], key, reverse):
            arr[p + 1] = arr[p]
            p -= 1
        arr[p + 1] = key
    return arr


def main():
    arr = [1, 3, 2]
    sorted = insertion_sort(arr, True)
    print(arr)
    print(sorted)


if __name__ == '__main__':
    main()
