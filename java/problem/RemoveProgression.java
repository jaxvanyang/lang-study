import java.util.Scanner;

public class RemoveProgression {
    public static void main(String[] args) {
        var scanner = new Scanner(System.in);

        int t = scanner.nextInt();
        for (int i = 0; i < t; i++) {
            int n = scanner.nextInt();
            int x = scanner.nextInt();
            System.out.println(find(n, x));
        }

        scanner.close();
    }

    public static int find(int n, int x) {
        // i = 0, n = n, kill = 0
        // i = 1, n = n - 1, kill = 1
        // ...
        // i = k, n = n - k, kill = k
        // i = k + 1, n = n - k - 1, (n - k - 1) < k + 1
        // n - 2 < 2 * k
        // k > n / 2 - 1
        // k = (n + 1) / 2
        return 2 * x;
    }
}
