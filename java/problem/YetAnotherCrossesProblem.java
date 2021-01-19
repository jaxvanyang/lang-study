// import java.util.ArrayList;
// import java.util.Arrays;
import java.util.Scanner;

public class YetAnotherCrossesProblem {
    public static void main(String[] args) {
        final var scanner = new Scanner(System.in);

        final int times = scanner.nextInt();
        for (int t = 0; t < times; t++) {
            final int row = scanner.nextInt(), col = scanner.nextInt();
            scanner.nextLine();
            final var table = new char[row][];
            for (int i = 0; i < row; i++) {
                table[i] = scanner.nextLine().toCharArray();
            }

            // System.out.println(Arrays.deepToString(table));

            int rowCnt = 0, colCnt = 0;     // 用来记录最少的白块数量
            int[] rows = new int[row];      // 用于记录白块最少的是哪几行、列
            int rowBegin = 0, rowEnd = 0;   // 记录栈的开始和结束
            int[] cols = new int[col];      // 用于记录白块最少的是哪几行、列
            int colBegin = 0, colEnd = 0;   // 记录栈的开始和结束

            // 初始化栈
            // rows[rowEnd] = 0;
            rowEnd++;
            for (int i = 0; i < col; i++) {
                if (table[0][i] == '.') {
                    rowCnt++;
                }
            }
            // cols[colEnd] = 0;
            colEnd++;
            for (int i = 0; i < row; i++) {
                if (table[i][0] == '.') {
                    colCnt++;
                }
            }
            // System.out.println(Arrays.toString(cols));
            // System.out.println(rowCnt);
            // System.out.println(colCnt);

            for (int i = 1; i < row; i++) {
                int cnt = 0;
                for (int j = 0; j < col; j++) {
                    cnt += table[i][j] == '.' ? 1 : 0;
                }
                if (cnt == rowCnt) {
                    rows[rowEnd++] = i;
                } else if (cnt < rowCnt) {
                    rowCnt = cnt;
                    rowBegin = rowEnd;
                    rows[rowEnd++] = i;
                }
            }
            for (int i = 1; i < col; i++) {
                int cnt = 0;
                for (int j = 0; j < row; j++) {
                    cnt += table[j][i] == '.' ? 1 : 0;
                }
                if (cnt == colCnt) {
                    cols[colEnd++] = i;
                } else if (cnt < colCnt) {
                    colCnt = cnt;
                    colBegin = colEnd;
                    cols[colEnd++] = i;
                }
            }
            // System.out.print(Arrays.toString(cols));

            boolean notFound = true;    // 没有共同的空白
            for (int i = rowBegin; i < rowEnd; i++) {
                for (int j = colBegin; j < colEnd; j++) {
                    if (table[rows[i]][cols[j]] == '.') {
                        notFound = false;
                        break;
                    }
                }
                if (!notFound) {
                    break;
                }
            }
            if (notFound) {
                System.out.println(rowCnt + colCnt);
            } else {
                System.out.println(rowCnt + colCnt - 1);
            }
        }

        scanner.close();
    }
}
/**
 * @name Yet Another Crosses Problem
 * @from CodeForce
 * 
 * 大概的思路就是先找出白块数量最少的是哪几行和哪几列，然后再判断它们相交的地方是不是空白
 * 如果是空白，那就直接返回行列白块之和减一
 * 如果没有相交空白，那就返回行列白块之和
 * 
 * 这么做的依据是答案一定所在列和行的白块数量一定最少，可用反证法证明
 */