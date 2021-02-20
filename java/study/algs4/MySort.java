package algs4;

import java.util.Arrays;

public class MySort {
    public static final String helpMsg = """
            使用方式：java algs4.MySort [alg=xx] [n=xx] [min=xx] [max=xx] [-s|-show] [-i|-Int] [m=xx]""";

    private static class Parameter {
        int n = 10000;
        double min = 0.0, max = 1.0;
        String alg = "Insertion";
        boolean show = false;
        String type = "Double";

        public Parameter(String[] args) {
            for (var p : args) {
                if (p.charAt(0) == '-') {
                    if (p.equals("-s") || p.equals("-show")) {
                        show = true;
                    } else if (p.equals("-i") || p.equals("-Int")) {
                        type = "Int";
                    }
                } else {
                    int i = p.indexOf('=');
                    if (i == -1 && p.equals("help")) {
                        help();
                        return;
                    }
                    String key = p.substring(0, i);
                    String value = p.substring(i + 1);
                    if (key.equals("alg")) {
                        alg = value;
                    } else if (key.equals("n")) {
                        n = Integer.parseInt(value);
                    } else if (key.equals("min")) {
                        min = Double.parseDouble(value);
                    } else if (key.equals("max")) {
                        max = Double.parseDouble(value);
                    } else if (key.equals("m")) {
                        Quick.M = Integer.parseInt(value);
                    }
                }
            }
        }

        public void help() {
            System.out.println(helpMsg);
        }

        public void run() {
            Comparable[] arr;
            // Double[] arr = MyRandom.randomDoubleArray(n, min, max);
            if (type == "Double") {
                arr = MyRandom.randomDoubleArray(n, min, max);
            } else {
                arr = MyRandom.randomIntegerArray(n, (int) min, (int) max);
            }
            StopWatch watch = new StopWatch();

            if (alg.equals("Insertion")) {
                insertionSort(arr);
            } else if (alg.equals("Shell")) {
                shellSort(arr);
            } else if (alg.equals("ShellPro")) {
                shellSortPro(arr);
            } else if (alg.equals("Merge")) {
                mergeSort(arr);
            } else if (alg.equals("MergeBU")) {
                mergeSortBU(arr);
            } else if (alg.equals("Quick")) {
                Quick.sort(arr);
            } else if (alg.equals("QuickInsertion")) {
                Quick.sortInsertion(arr);
            } else {
                selectionSort(arr);
            }

            double time = watch.elapsedTime();

            assert isSorted(arr);

            if (show)
                show(arr);

            System.out.println("For " + n + " Doubles ranging from " + min + " to " + max);
            System.out.println(alg + " 排序用时：" + time + " 秒");

        }
    }

    public static void main(String[] args) {
        // Integer[] arr = {1, 2, 3, 4};
        // Quick.partition(arr, 0, 3);
        // System.out.println(Arrays.toString(arr));
        Parameter p = new Parameter(args);
        p.run();
    }

    public static class Quick {
        private static int partition(Comparable[] arr, int left, int right) {
            var v = arr[left];
            int l = left, r = right + 1;
            while (true) {
                while (less(arr[++l], v))
                    if (l == right)
                        break;
                while (less(v, arr[--r]))
                    if (r == left)
                        break;
                if (l >= r)
                    break;
                swap(arr, l, r);
            }
            // !: 这里要和 [r] 交换，因为 [r] 才小于等于 v，才能和 v 交换
            swap(arr, left, r);
            return r;
        }

        public static void sort(Comparable[] arr) {
            sort(arr, 0, arr.length - 1);
        }

        private static void sort(Comparable[] arr, int left, int right) {
            if (left >= right)
                return;
            int mid = partition(arr, left, right);
            sort(arr, left, mid - 1);
            sort(arr, mid + 1, right);
        }

        private static int M = 10;

        private static void sortInsertion(Comparable[] arr, int left, int right) {
            if (right - left < M) {
                Insertion.sort(arr, left, right);
                return;
            }
            int mid = partition(arr, left, right);
            sort(arr, left, mid - 1);
            sort(arr, mid + 1, right);
        }

        public static void sortInsertion(Comparable[] arr) {
            sortInsertion(arr, 0, arr.length - 1);
        }
    }

    public static class Insertion {
        public static void sort(Comparable[] arr, int left, int right) {
            for (int i = right; i > left; --i) {
                var key = arr[right];
                int j = i;
                while (j > left && less(key, arr[j - 1])) {
                    arr[j] = arr[--j];
                }
                arr[j] = key;
            }
        }
    }

    private static Comparable[] helpArr;

    private static void merge(Comparable[] arr, int left, int mid, int right) {
        for (int i = left; i <= right; ++i) {
            helpArr[i] = arr[i];
        }
        int l = left, r = mid + 1, i = left;
        while (l <= mid && r <= right) {
            arr[i++] = less(helpArr[l], helpArr[r]) ? helpArr[l++] : helpArr[r++];
        }
        while (l <= mid) {
            arr[i++] = helpArr[l++];
        }
        while (r <= right) {
            arr[i++] = helpArr[r++];
        }
    }

    private static void mergeSort(Comparable[] arr, int left, int mid, int right) {
        if (left < mid) {
            mergeSort(arr, left, (left + mid) >> 1, mid);
        }
        if (mid + 1 < right) {
            mergeSort(arr, mid + 1, (mid + 1 + right) >> 1, right);
        }
        if (mid + 1 <= right && less(arr[mid + 1], arr[mid]))
            merge(arr, left, mid, right);
    }

    public static void mergeSort(Comparable[] arr) {
        helpArr = new Comparable[arr.length];
        mergeSort(arr, 0, arr.length >> 1, arr.length - 1);
    }

    // 自底向上的归并排序，不用递归
    public static void mergeSortBU(Comparable[] arr) {
        int len = arr.length;
        helpArr = new Comparable[len];
        for (int sz = 1; sz < len; sz += sz) {
            for (int l = 0; l < len - sz; l += sz + sz) {
                merge(arr, l, l + sz - 1, Math.min(l + sz + sz - 1, len - 1));
            }
        }
    }

    // 希尔排序
    public static void shellSort(Comparable[] arr) {
        int len = arr.length;
        int h = 1;
        while (h < len / 3) {
            h = 3 * h + 1;
        }
        while (h >= 1) {
            for (int i = h; i < len; ++i) {
                for (int j = i; j >= h && less(arr[j], arr[j - h]); j -= h) {
                    swap(arr, j, j - h);
                }
            }
            h /= 3;
        }
    }

    // 避免元素交换优化性能的希尔排序
    public static void shellSortPro(Comparable[] arr) {
        int len = arr.length;
        int h = 1;
        while (h < len / 3) {
            h = 3 * h + 1;
        }
        while (h >= 1) {
            for (int i = h; i < len; ++i) {
                var key = arr[i];
                int j = i;
                for (; j >= h && less(key, arr[j - h]); j -= h) {
                    arr[j] = arr[j - h];
                }
                arr[j] = key;
            }
            h /= 3;
        }
    }

    // 插入排序的特点是对于有序数组效率特别高
    // TODO: 奇怪的是插入排序测试下来比选择排序要慢
    public static void insertionSort(Comparable[] arr) {
        int len = arr.length;
        for (int i = 1; i < len; ++i) {
            var key = arr[i];
            int j = i;
            for (; j > 0 && less(key, arr[j - 1]); --j) {
                // swap(arr, j, j - 1);
                arr[j] = arr[j - 1];
            }
            arr[j] = key;
        }
    }

    // 选择排序
    public static void selectionSort(Comparable[] arr) {
        int len = arr.length;
        for (int i = 0; i < len - 1; ++i) {
            int min = i;
            for (int j = i + 1; j < len; ++j) {
                if (less(arr[j], arr[min])) {
                    min = j;
                }
            }
            swap(arr, i, min);
        }
    }

    public static boolean less(Comparable a, Comparable b) {
        return a.compareTo(b) < 0;
    }

    public static void swap(Comparable[] arr, int i, int j) {
        if (arr[i].compareTo(arr[j]) == 0) {
            return;
        }
        var tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    public static boolean isSorted(Comparable[] arr) {
        int len = arr.length;
        for (int i = 1; i < len; ++i) {
            if (less(arr[i], arr[i - 1])) {
                return false;
            }
        }
        return true;
    }

    public static void show(Comparable[] arr) {
        System.out.println(java.util.Arrays.toString(arr));
    }

    // TODO: 实现一个可视化的排序分析方法
}
