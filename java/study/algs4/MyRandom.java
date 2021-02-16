package algs4;

public class MyRandom {
    public final static double NEXT_DOWN = Math.nextDown(1.0);

    public static int[] randomIntArray(int size) {
        int[] ret = new int[size];
        for (int i = 0; i < size; ++i) {
            ret[i] = Integer.MAX_VALUE;
            ret[i] *= (Math.random() / NEXT_DOWN);
        }
        return ret;
    }

    public static Integer[] randomIntArray(int size, int min, int max) {
        Integer[] ret = new Integer[size];
        for (int i = 0; i < size; ++i) {
            double f = Math.random() / NEXT_DOWN;
            ret[i] = (int) (min * (1.0 - f) + max * f + 0.5);
        }
        return ret;
    }

    public static Integer[] randomIntegerArray(int size) {
        Integer[] ret = new Integer[size];
        for (int i = 0; i < size; ++i) {
            int tmp = Integer.MAX_VALUE;
            tmp *= Math.random() / NEXT_DOWN;
            ret[i] = tmp;
        }
        return ret;
    }

    public static void main(String[] args) {
        int size = 10, min = 1, max = 10;
        if (args.length == 3) {
            size = Integer.parseInt(args[0]);
            min = Integer.parseInt(args[1]);
            max = Integer.parseInt(args[2]);
        }
        var arr = randomIntArray(size, min, max);
        for (int i = 0; i < size; ++i) {
            System.out.print(arr[i] + " ");
        }
    }
}
