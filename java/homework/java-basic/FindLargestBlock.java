import java.util.Scanner;

public class FindLargestBlock {
    // 只记录一个最大方阵
    public static int[] findLargestBlock(int[][] m) {
        int[] ret = { 0, 0, 0 };
        int rowSize = m.length, colSize = m[0].length;
        int[][] dp = new int[rowSize + 1][colSize + 1];
        for (int row = rowSize - 1; row >= 0; --row) {
            for (int col = colSize - 1; col >= 0; --col) {
                if (m[row][col] == 1) {
                    int size = dp[row + 1][col + 1];
                    boolean flag = true;
                    for (int i = 1; i <= size; ++i)
                        if (m[row][col + i] == 0) {
                            flag = false;
                            break;
                        }
                    for (int i = 1; i <= size; ++i)
                        if (m[row + i][col] == 0) {
                            flag = false;
                            break;
                        }
                    if (flag)
                        dp[row][col] = size + 1;
                    if (dp[row][col] > ret[2]) {
                        ret[0] = row;
                        ret[1] = col;
                        ret[2] = dp[row][col];
                    }
                }
            }
        }
        return ret;
    }

    public static int[][] getInputMatrix() {
        try (var scanner = new Scanner(System.in)) {
            System.out.println("请输入方阵大小：");
            int size = scanner.nextInt();
            int[][] ret = new int[size][size];
            for (int i = 0; i < size; ++i) {
                String s = scanner.next();
                for (int j = 0; j < s.length(); ++j) {
                    if (s.charAt(j) == '1')
                        ret[i][j] = 1;
                }
            }
            return ret;
        }
    }

    public static void main(String[] args) {
        // int[][] m = { { 1, 0, 0 }, { 0, 1, 1 }, { 1, 1, 1 } };
        int[][] m = getInputMatrix();
        int[] ans = findLargestBlock(m);
        System.out.printf("最大方阵位置：(%d, %d)，方阵长度：%d\n", ans[0], ans[1], ans[2]);
    }
}
