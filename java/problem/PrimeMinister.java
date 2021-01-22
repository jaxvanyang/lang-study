import java.util.Scanner;

public class PrimeMinister {
    public static void main(String[] args) {
        final var scanner = new Scanner(System.in);

        
        int n = scanner.nextInt();
        int alice = scanner.nextInt();
        int total = alice;
        int coalition = alice;
        int[] ans = new int[n];
        int k = 0;
        ans[k++] = 1;
        for (int i = 2; i <= n; i++) {
            int tmp = scanner.nextInt();
            total += tmp;
            if (2 * tmp <= alice) {
                coalition += tmp;
                ans[k++] = i;
            }
        }
        if (2 * coalition > total) {
            System.out.println(k);
            System.out.print(ans[0]);
            for (int i = 1; i < k; i++) {
                System.out.print(" " + ans[i]);
            }
            System.out.println();
        } else {
            System.out.println(0);
        }
        
        scanner.close();
    }
}
/**
 * @from CodeForce
 * 
 * @input n = party 的数量，a[i] = party[i] 的席位数
 * 
 * @output 0 或所有可以合并的序号
 * 
 * @analysis 成功的条件是： 1. 联盟席位数大于总席位的一半; 2. Alice 的席位数至少是联盟内其他党派席位数的两倍 只要席位数小于
 *           Alice 的二分之一都可以联盟，所以可以逐个判断
 *
 */