import java.util.Scanner;

public class Input {
    public static void main(String[] args) {
        final var scanner = new Scanner(System.in);
        while (true) {
            menu();
            final var input_int = scanner.nextInt();
            switch (input_int) {
                case 1:
                    repeatInput();
                    break;
                case 2:
                    compareScore();
                    break;
                default:
                    return;
            }
        }        
    }

    final static Scanner scanner = new Scanner(System.in);

    final static String MSG = """
                    请输入选项选择选项：
                    0. 退出
                    1. 重复输入
                    2. 计算成绩提高的百分比
                    """;
    static void menu() {
        System.out.println(MSG);
    }

    static void repeatInput() {
        while (true) {
            final var input = new StringBuilder(scanner.nextLine()).toString();
            // java 的 == 对引用类型是判断引用而不是值
            // if (input == "exit") {
            if (input.equals("exit")) {
                break;
            }
            System.out.println("You typed this: " + input);
        }
    }

    static void compareScore() {
        System.out.println("请输入第一次的成绩：");
        var score_1 = scanner.nextFloat();
        var score_2 = scanner.nextFloat();
        System.out.println("第一次的成绩是：" + score_1 + " 第二次的成绩是：" + score_2);
        System.out.printf("提升了：%.2f%%\n", (score_2 - score_1) / score_1 * 100);
    }
}