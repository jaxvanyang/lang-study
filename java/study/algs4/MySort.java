package algs4;

public class MySort {
    public static void main(String[] args) {
        int n = 100, min = 1, max = 100;
        if (args.length >= 1) {
            n = Integer.parseInt(args[0]);
        }
        if (args.length >= 2) {
            min = Integer.parseInt(args[1]);
        }
        if (args.length == 3) {
            max = Integer.parseInt(args[2]);
        }

        Integer[] arr = MyRandom.randomIntegerArray(n, min, max);
        StopWatch watch = new StopWatch();

        insertionSort(arr);
        // selectionSort(arr);
        double time = watch.elapsedTime();

        assert isSorted(arr);
        
        show(arr);

        System.out.println("排序用时：" + time + " 秒");
    }

    // 插入排序的特点是对于有序数组效率特别高
    public static void insertionSort(Comparable[] arr) {
        int len = arr.length;
        for (int i = 1; i < len; ++i) {
            var key = arr[i];
            int j = i;
            for (; j > 0 && less(key, arr[j - 1]); --j) {
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
