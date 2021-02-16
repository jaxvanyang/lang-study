package algs4;

public class MySort {
    public static void main(String[] args) {
        int n = 100000;
        double min = 0.0, max = 1.0;
        String alg = "Insertion";
        if (args.length >= 1) {
            alg = args[0];
        }
        if (args.length >= 2) {
            n = Integer.parseInt(args[1]);
        }
        if (args.length >= 3) {
            min = Double.parseDouble(args[2]);
        }
        if (args.length == 4) {
            max = Double.parseDouble(args[3]);
        }

        Double[] arr = MyRandom.randomDoubleArray(n, min, max);
        StopWatch watch = new StopWatch();

        if (alg.equals("Insertion")) {
            insertionSort(arr);
        } else if (alg.equals("Shell")) {
            shellSort(arr);
        } else if (alg.equals("ShellPro")) {
            shellSortPro(arr);
        } else {
            selectionSort(arr);
        }

        double time = watch.elapsedTime();

        assert isSorted(arr);

        show(arr);

        System.out.println(alg + " 排序用时：" + time + " 秒");
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
