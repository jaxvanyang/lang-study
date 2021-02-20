package algs4;

/**
 * UnionFind
 */
public class UnionFind {

    private final int[] id;
    private int count;

    public UnionFind(int n) {
        id = new int[n];
        count = n;
        for (int i = 0; i < n; ++i) {
            id[i] = i;
        }
    }

    public int find(int p) {
        if (id[p] == p) {
            return p;
        }
        return find(id[p]);
    }

    public void union(int p, int q) {
        int pRoot = find(p), qRoot = find(q);
        if (pRoot != qRoot) {
            id[pRoot] = id[qRoot];
            --count;
        }
    }

    public int getCount() {
        return count;
    }
}