import java.util.Scanner;

public class DrinksChoosing {
    public static void main(String[] args) {
        final var scanner = new Scanner(System.in);

        final int n = scanner.nextInt(), k = scanner.nextInt();
        final int[] typeCnts = new int[k + 1];
        for (int i = 0; i < n; i++) {
            ++typeCnts[scanner.nextInt()];
        }
        int ans = 0;
        for (int i = 1; i <= k; i++) {
            ans += 2 * (typeCnts[i] / 2);
        }
        // System.out.println(ans);
        ans += (n - ans + 1) / 2;
        System.out.println(ans);

        scanner.close();
    }
}
/**
 * @from CodeForce
 */