package algs4;

public class SortCompare {
    public static double time(String alg, Double[] arr) {
        StopWatch timer = new StopWatch();
        if (alg.equals("Selection")) {
            MySort.selectionSort(arr);
        } else if (alg.equals("Insertion")) {
            MySort.insertionSort(arr);
        }
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

    public static void main(String[] args) {
        String alg1 = "Insertion";
        String alg2 = "Selection";
        int n = 1000, t = 100;
        if (args.length == 4) {
            alg1 = args[0];
            alg2 = args[1];
            n = Integer.parseInt(args[2]);
            t = Integer.parseInt(args[3]);
        }

        double t1 = timeRandomInput(alg1, n, t);
        double t2 = timeRandomInput(alg2, n, t);
        System.out.printf("For %d random Doubles\n%s is ", n, alg1);
        System.out.printf("%f times faster as %s\n", t2 / t1, alg2);
        System.out.printf("%s uses %f s, %s uses %f s\n", alg1, t1, alg2, t2);
    }
}
