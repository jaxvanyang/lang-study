package algs4;

public class Assignment {
  public static void main(String[] args) {
    // System.out.println(pow(2, 0));
    System.out.println(lg(10));
  }

  public static int lg(int n) {
    int res = 0;
    while (pow(2, res + 1) < n) {
      ++res;
    }
    return res;
  }

  public static int pow(int x, int n) {
    int res = 1;
    for (int i = 0; i < n; ++i) {
      res *= x;
    }
    return res;
  }
}
