package algs4;

public class StopWatch {
    private long start;

    public StopWatch() {
        start = System.currentTimeMillis();
    }

    public double elapsedTime() {
        long now = System.currentTimeMillis();
        return (now - start) / 1000.0;
    }

    public void refresh() {
        start = System.currentTimeMillis();
    }

    public static void main(String[] args) {
        int n = 100_0000;
        if (args.length == 1) {
            n = Integer.parseInt(args[0]);
        }
        int[] arr = new int[n];
        StopWatch w = new StopWatch();
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
        double time = w.elapsedTime();
        System.out.println("判断、自增、赋值各 " + n + "次，共 " + 3 * n + "次");
        System.out.println("一共耗时：" + time + " 秒，平均每次操作耗时： " + time / 3 / n + " 秒");

        w.refresh();
        System.out.println("刷新停表后的计时：" + w.elapsedTime());
    }
}
