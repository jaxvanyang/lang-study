import java.util.Random;

public class WuKongAndPeach {
    private static Random random = new Random();
    private static int peachCount = 100;

    public static void main(String[] args) {

        Thread peachTree = new Thread() {
            @Override
            public void run() {
                try {
                    while (true) {
                        Thread.sleep(300);
                        int tmp = randomInt(10);
                        peachCount += tmp;
                        System.out.println("蟠桃树：我新长出了 " + tmp + " 个桃子");
                    }
                } catch (InterruptedException e) {
                }
            }
        };

        Thread fairy = new Thread() {
            @Override
            public void run() {
                try {
                    while (true) {
                        Thread.sleep(500);
                        System.out.println("仙女：现在有 " + peachCount + " 个桃子");
                    }
                } catch (InterruptedException e) {

                }
            }
        };

        Thread wuKong = new Thread() {
            @Override
            public void run() {
                try {
                    while (true) {
                        Thread.sleep(100);
                        System.out.println("孙悟空：我偷吃了一个桃子");
                    }
                } catch (InterruptedException e) {

                }
            }
        };

        peachTree.start();
        fairy.start();
        wuKong.start();

        //  测试五秒后结束所有线程
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            peachTree.interrupt();
            fairy.interrupt();
            wuKong.interrupt();
        }

        System.out.println("系统：最后还有 " + peachCount + " 个桃子");
    }

    private static int randomInt(int max) {
        return random.nextInt(max) + 1;
    }
}
