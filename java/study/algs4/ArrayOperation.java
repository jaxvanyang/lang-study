package algs4;

import java.util.Arrays; // 包含数组排序和将数组转为字符串的函数

public class ArrayOperation {
    public static void main(String[] args) {
        int[] arr = { 28, 12, 89, 73, 65, 18, 96, 50, 8, 36 };

        var copy = arr.clone();

        // 使用冒泡排序，倒序
        for (int i = 0; i < copy.length - 1; i++) { // i 表示的是冒泡的次数
            boolean flag = true; // true 表示没发生过交换
            for (int j = 0; j < copy.length - 1 - i; j++) { // j 的 范围是还未确定的数
                if (copy[j] < copy[j + 1]) {
                    int tmp = copy[j];
                    copy[j] = copy[j + 1];
                    copy[j + 1] = tmp;
                    flag = false;
                }
            }
            if (flag) { // 没发生过交换就说明数组已经有序，不需要再冒泡了
                break;
            }
        }
        System.out.println(Arrays.toString(copy));

        // 使用 Java 标准库中的排序函数
        Arrays.sort(copy);
        System.out.println(Arrays.toString(copy));

        // 二维数组的定义形式
        int[][] _2d_arr = { { 1, 2, 3, 4 }, { 5, 6 }, { 7, 8, 9 } };    // 每一行长度可以不同
        System.out.println(Arrays.deepToString(_2d_arr)); // 对多维数组要使用深层转换
    }
}