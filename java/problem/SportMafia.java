import java.util.Scanner;

public class SportMafia{
    public static void main(String[] args) {
        final var scanner = new Scanner(System.in);

        // n 是操作的次数，k 是剩下的糖果数量
        int n = scanner.nextInt(), k = scanner.nextInt();
        for (int i = 0; i <= n; i++) {
            if (2 * k == (1 + n - i) * (n - i) - 2 * i) {
                System.out.println(i);
                scanner.close();
                return;
            }
        }

        scanner.close();
    }
}
/**
 * @from CodeForce
 * 
 * @input n 是操作的次数，k 是剩下的糖果数量
 * 
 * @output ans = 吃掉的糖果数
 * 
 * @analysis 吃掉的糖果数就是吃的次数，所以放糖果的次数就是 n - ans
 * 一共放的糖果数是 (1 + n - ans) * (n - ans) / 2
 * 所以 k = (1 + n - ans) * (n - ans) / 2 - ans
 * 解得 ans 有两个解
 * 又吃掉的糖果数一定小于等于 n
 * 可以遍历 0 到 n 求解
 */