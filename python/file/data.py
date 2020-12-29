from os import sep
import random

# TMP_DIR = 'D:/repos/lang-study/tmp/'
TMP_DIR = '/repos/lang-study/tmp/'


def get_random_int_list(size: int = 100, min: int = 0, max: int = 100):
    return [random.randint(min, max) for i in range(size)]


def write_list_to_file(list, name: str = 'data', separator: str = ' ', extension: str = 'tmp', dir: str = TMP_DIR, has_dot: bool = True):
    '''
    参数
    list: list to be write\n
    name: file name 默认是 'data'\n
    separator: string between list items 默认是 ' '\n
    extension: file type extension name 默认是 'tmp'\n
    dir: file dir 默认是全局变量 $TMP_DIR\n
    has_dot: whether to insert a dot between file name and file extension\n
    最终写入的文件是: $TMP_DIR/$name.$extension
    '''
    dest = dir + name + ('.' if has_dot else '') + extension
    file = open(dest, 'w')
    file.write(separator.join(map(str, list)))


def compare_file(name_1: str = 'data-1', name_2: str = 'data-2', extension: str = 'tmp', dir: str = TMP_DIR, has_dot: bool = True):
    '''
    parameters
    name_1, name_2: name of file to be compared
    extension: type extension
    dir: file dir
    has_dot: whether file destination has a dot between name and extension
    '''
    dest_1 = TMP_DIR + name_1 + ('.' if has_dot else '') + extension
    dest_2 = TMP_DIR + name_2 + ('.' if has_dot else '') + extension
    file_1, file_2 = open(dest_1, 'r'), open(dest_2, 'r')
    data_1, data_2 = file_1.read(), file_2.read()
    return data_1 == data_2

def main():
    name_1 = 'data-1'
    name_2 = 'data-2'
    list_1, list_2 = get_random_int_list(), get_random_int_list()
    write_list_to_file(list_1, name_1, '\n')
    write_list_to_file(list_2, name_2, '\n')
    print(compare_file(name_1, name_2))


if __name__ == '__main__':
    main()
