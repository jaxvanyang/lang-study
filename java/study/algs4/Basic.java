package algs4;

public class Basic {
    public static void main(String[] args) {
        // 整数类型
        byte byte_max = 127;
        byte byte_min = -128;   // 一个字节
        short short_max = 3_2767;    // 两个字节
        short short_min = -32768;
        // 一个 16 进制位是 4 个 bit
        int int_max = 0x7fff_ffff;   // 四个字节
        int int_min = -int_max - 1;
        // 长整形字面量需要加 L
        long long_max = 922_3372_0368_5477_5807L;    // 八个字节
        long long_min = -long_max - 1;
        System.out.println("这些是整数类型：");
        System.out.println("byte: " + byte_max + " ~ " + byte_min);
        System.out.println("short: " + short_max + " ~ " + short_min);
        System.out.println("int: " + int_max + " ~ " + int_min);
        System.out.println("long: " + long_max + " ~ " + long_min);
        
        // 浮点型
        float float_max = 3.4e38f;  // 大约
        double double_max = 1.79e308;
        System.out.println("这些是浮点型：");
        System.out.println(float_max);
        System.out.println(double_max);

        // 布尔类型，通常 JVM 内部会表示成 4 字节整数
        boolean bool_1 = true;
        boolean bool_2 = false;
        // boolean 不能用 + 和字符连接
        // System.out.println(bool_1 + ' ' + bool_2);
        System.out.println("这些是布尔型：");
        System.out.println(bool_1 + " " + bool_2);

        // 字符类型
        char ch1 = 'A';
        char ch2 = '中';
        // char ch3 = '😃'; Java 的 char 只有 16 bit，不能表示 32 位的 Unicode
        char ch3 = '\uffff';
        System.out.println("这些是字符型：");
        System.out.println(ch1 + ch2);  // 字符会自动转换为 int
        System.out.println(ch1 + " " + ch2 + " " + ch3);

        // 除了上述基本类型，剩下的都是引用类型
        // 字符串
        // Java的编译器对字符串做了特殊照顾，可以使用+连接任意字符串和其他数据类型，这样极大地方便了字符串的处理。
        String str = "😃😜😍";
        String mutiple_line = """
                              你好
                              这是第二行
                              """;
        println(str + 2020);
        System.out.println(mutiple_line);
        mutiple_line = null;
        System.out.println(mutiple_line);   // 打印 null

        int a = 72;
        int b = 105;
        int c = 65281;
        System.out.println("" + (char)a + (char)b + (char)c);
        
        // 常量
        final float PI = 3.14f;
        System.out.println("PI = " + PI);

        // var 关键字
        var sb = new StringBuilder();
        sb.append("😃");
        sb.append("😜😍");
        println(sb);

        // 数组类型
        String[] names = new String[3]; // 初始化为 null
        // String[] names = new String[] {"Steve", "Alex", "Jax"};
        // String[] names = {"Steve", "Alex", "Jax"};
        int len = names.length;
        for (int i = 0; i < len; i++) {
            println(names[i]);
        }
        names[0] = "Steve";
        names[1] = "Alex";
        names[2] = "Jax";
        for (int i = 0; i < len; i++) {
            println(names[i]);
        }

        // 格式化输出
        System.out.printf("integer = %d, hex = %08x, float=%.2f, science = %e, str=%s\n", int_max, short_max, float_max, double_max, names[0]);
        // System.out.printf("%.2f", double_max);
    }
    public static void print(char ch) {
        System.out.print(ch);
    }
    public static void print(String str) {
        System.out.print(str);
    }
    public static void println(char ch) {
        System.out.println(ch);
    }
    public static void println(String str) {
        System.out.println(str);
    }

    public static void println(StringBuilder sb) {
        System.out.println(sb);
    }
}