import sys
sys.path[0] = '/repos/lang-study/python'
from file.data import *
from algorithms.sort import * 

def main():
    arr = get_random_int_list()
    arr_sorted = sorted(arr)
    arr_ = insertion_sort(arr)
    print(arr_sorted)
    print(arr_)
    print(arr_ == arr_sorted)

if __name__ == '__main__':
    main()
