import java.util.Arrays;
import java.util.Scanner;

public class Majiang {
    public static void main(String[] args) {

        var scanner = new Scanner(System.in);
        var tiles = scanner.nextLine().split(" ");
        // System.out.println(Arrays.toString(tiles));

        // if (tiles[0].equals(tiles[1]) || tiles[0].equals[tiles[2] ||
        // tiles[1].equals(tiles[2])]) {
        // System.out.println(1);
        // }

        // System.out.println(code(tiles[0]));
        int[] codes = { 0, 0, 0 };
        for (int i = 0; i < 3; i++) {
            codes[i] = code(tiles[i]);
        }
        Arrays.sort(codes);
        // System.out.println(Arrays.toString(codes));

        if (codes[0] == codes[1] && codes[0] == codes[2]) { // 特判 koutsu
            answer(0);
        } else if (codes[0] == codes[1] || codes[0] == codes[2] || codes[1] == codes[2]) { // 两个牌一样
            answer(1);
        } else if (codes[0] + 1 == codes[1] && codes[1] + 1 == codes[2]) { // 特判 shuntsu
            answer(0);
        } else if (codes[0] + 1 == codes[1] || codes[1] + 1 == codes[2]) { // 有两个连续的
            answer(1);
        } else if (codes[0] + 2 == codes[1] || codes[1] + 2 == codes[2]) { // 两个中间刚好差一个
            answer(1);
        } else {
            answer(2);
        }

        scanner.close();
    }

    public static void answer(int ans) {
        System.out.println(ans);
    }

    public static int code(String str) {
        int index = str.charAt(0) - '0';
        int type = str.charAt(1) - 'm';
        return index + type * 10;
    }
}
