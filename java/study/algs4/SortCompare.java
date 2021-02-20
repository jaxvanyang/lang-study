package algs4;

public class SortCompare {
    public static double time(String alg, Double[] arr) {
        StopWatch timer = new StopWatch();
        if (alg.equals("Selection")) {
            MySort.selectionSort(arr);
        } else if (alg.equals("Insertion")) {
            MySort.insertionSort(arr);
        } else if (alg.equals("Shell")) {
            MySort.shellSort(arr);
        } else if (alg.equals("ShellPro")) {
            MySort.shellSortPro(arr);
        } else if (alg.equals("Merge")) {
            MySort.mergeSort(arr);
        } else if (alg.equals("MergeBU")) {
            MySort.mergeSortBU(arr);
        } else if (alg.equals("Quick")) {
            MySort.Quick.sort(arr);
        } else if (alg.equals("QuickInsertion")) {
            MySort.Quick.sortInsertion(arr);
        }
        assert MySort.isSorted(arr) : "arr is not sorted";
        return timer.elapsedTime();
    }

    public static double timeRandomInput(String alg, int n, int t) {
        // 使用算法 alg 将 t 个长度为 n 的数组排序
        double total = 0.0;
        Double[] arr = new Double[n];
        for (int i = 0; i < t; ++i) {
            for (int j = 0; j < n; ++j) {
                arr[j] = Math.random();
            }
            total += time(alg, arr);
        }
        return total;
    }

    // 命令行参数分别为：
    // algs1：算法1； algs2：算法2； n：数组大小； t：排序次数
    public static void main(String[] args) {
        String alg1 = "Insertion";
        String alg2 = "Selection";
        int n = 10000, t = 10;

        if (args.length >= 1) {
            alg1 = args[0];
        }
        if (args.length >= 2) {
            alg2 = args[1];
        }
        if (args.length >= 3) {
            n = Integer.parseInt(args[2]);
        }
        if (args.length >= 4) {
            t = Integer.parseInt(args[3]);
        }

        double t1 = timeRandomInput(alg1, n, t);
        double t2 = timeRandomInput(alg2, n, t);
        System.out.printf("For %d random Doubles and running for %d times\n%s is ", n, t, alg1);
        System.out.printf("%f times faster as %s\n", t2 / t1, alg2);
        System.out.printf("%s uses %f s, %s uses %f s\n", alg1, t1, alg2, t2);
    }
}
