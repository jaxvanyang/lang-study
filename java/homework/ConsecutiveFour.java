import java.util.Arrays;

/**
 * @author 杨凯
 * @ID 201908130416
 */
public class ConsecutiveFour {
    public static boolean isConsecutiveFour(int[][] values) {
        int rowSize = values.length, colSize = values[0].length;
        if (rowSize < 4 && colSize < 4)
            return false;
        // check horizontal
        for (var row : values) {
            int l = 0;
            while (l < colSize) {
                int value = row[l];
                // System.out.println("?");
                int r = l;
                while (r < colSize && row[r] == value)
                    ++r;
                if (r - l >= 4)
                    return true;
                l = r;
            }
        }
        // System.out.println("Hello");
        // check vertical
        for (int i = 0; i < colSize; ++i) {
            int u = 0;
            while (u < rowSize) {
                int value = values[u][i];
                int d = u;
                while (d < rowSize && values[d][i] == value)
                    ++d;
                if (d - u >= 4)
                    return true;
                u = d;
            }
        }
        // check main diagonal line
        for (int i = 0; i < colSize - 3; ++i) {
            int r = 0, c = i;
            while (r < rowSize && c < colSize) {
                int value = values[r][c];
                int cnt = 0;
                while (r < rowSize && c < colSize && values[r][c] == value) {
                    ++cnt;
                    ++r;
                    ++c;
                }
                if (cnt >= 4)
                    return true;
            }
        }
        for (int i = 1; i < rowSize - 3; ++i) {
            int r = i, c = 0;
            while (r < rowSize && c < colSize) {
                int value = values[r][c];
                int cnt = 0;
                while (r < rowSize && c < colSize && values[r][c] == value) {
                    ++cnt;
                    ++r;
                    ++c;
                }
                if (cnt >= 4)
                    return true;
            }
        }

        // check right diagonal line
        for (int i = 3; i < colSize; ++i) {
            int r = 0, c = i;
            while (r < rowSize && c >= 0) {
                int value = values[r][c];
                int cnt = 0;
                while (r < rowSize && c >= 0 && values[r][c] == value) {
                    ++cnt;
                    ++r;
                    --c;
                }
                if (cnt >= 4) {
                    return true;
                }
            }
        }
        for (int i = 1; i < rowSize - 3; ++i) {
            int r = i, c = colSize - 1;
            while (r < rowSize && c >= 0) {
                int value = values[r][c];
                int cnt = 0;
                while (r < rowSize && c >= 0 && values[r][c] == value) {
                    ++cnt;
                    ++r;
                    --c;
                }
                if (cnt >= 4) {
                    return true;
                }
            }
        }
        return false;
    }

    public static boolean isValid(int[][] values, int r, int c) {
        return 0 <= r && r < values.length && 0 <= c && c < values[0].length;
    }

    public static final int[][] moves = { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, -1 } };

    public static int[] findConsecutiveFour(int[][] values, int r, int c, int[] move) {
        while (isValid(values, r, c)) {
            int cnt = 0;
            int value = values[r][c];
            while (isValid(values, r, c) && values[r][c] == value) {
                ++cnt;
                r += move[0];
                c += move[1];
            }
            if (cnt >= 4) {
                return new int[] { r - move[0] * cnt, c - move[1] * cnt };
            }
        }
        return null;
    }

    /**
     * 
     * @param values
     * @return ret[0] indicate the start position of consecutive four. ret[1]
     *         indicate the end position of consecutive four. ret[2] indicate the
     *         orientation of consecutive four.
     */
    public static int[][] getConsecutiveFour(int[][] values) {
        int rowSize = values.length, colSize = values[0].length;
        if (rowSize < 4 && colSize < 4)
            return null;

        int[] ret = null;
        for (int i = 0; i < rowSize; ++i) {
            ret = findConsecutiveFour(values, i, 0, moves[0]);
            if (ret != null)
                return new int[][] { ret, { ret[0], ret[1] + 3 }, { 0 } };
        }
        for (int i = 0; i < colSize; ++i) {
            ret = findConsecutiveFour(values, 0, i, moves[1]);
            if (ret != null)
                return new int[][] { ret, { ret[0] + 3, ret[1] }, { 1 } };
        }
        // check main diagonal line
        for (int i = 0; i < colSize - 3; ++i) {
            int r = 0, c = i;
            ret = findConsecutiveFour(values, r, c, moves[2]);
            if (ret != null)
                return new int[][] { ret, { ret[0] + 3, ret[1] + 3 }, { 2 } };
        }
        for (int i = 1; i < rowSize - 3; ++i) {
            int r = i, c = 0;
            ret = findConsecutiveFour(values, r, c, moves[2]);
            if (ret != null)
                return new int[][] { ret, { ret[0] + 3, ret[1] + 3 }, { 2 } };
        }

        // check right diagonal line
        for (int i = 3; i < colSize; ++i) {
            int r = 0, c = i;
            ret = findConsecutiveFour(values, r, c, moves[3]);
            if (ret != null)
                return new int[][] { ret, { ret[0] + 3, ret[1] - 3 }, { 3 } };
        }
        for (int i = 1; i < rowSize - 3; ++i) {
            int r = i, c = colSize - 1;
            ret = findConsecutiveFour(values, r, c, moves[3]);
            if (ret != null)
                return new int[][] { ret, { ret[0] + 3, ret[1] - 3 }, { 3 } };
        }
        return null;
    }

    public static void printConsecutiveFour(int[][] values) {
        var ans = getConsecutiveFour(values);
        if (ans == null) {
            System.out.println("null");
        } else {
            System.out.println(Arrays.deepToString(ans));
        }
    }

    public static void main(String[] args) {
        int[][] values = { { 0, 1, 2, 1 }, { 1, 0, 1, 4 }, { 1, 1, 0, 4 }, { 1, 2, 3, 1 } };
        // System.out.println(Arrays.deepToString(values));
        for (int i = 0; i < values.length; ++i) {
            for (int j = 0; j < values[i].length; ++j) {
                System.out.print(values[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println(isConsecutiveFour(values));
        // System.out.println(getConsecutiveFour(values));
        printConsecutiveFour(values);
    }
}