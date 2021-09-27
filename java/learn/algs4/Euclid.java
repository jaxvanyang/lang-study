package algs4;

public class Euclid {
  public static void main(String[] args) {
    if (args.length >= 2) {
      int p = stringToInt(args[0]), q = stringToInt(args[1]);
      System.out.println(getGcd(p, q));
    } else {
      System.out.println("请用命令行参数指定要计算最大公约数的两个数！");
    }
  }

  // 使用欧几里得算法计算最大公约数
  public static int getGcd(int p, int q) {
    if (p > q) {
      return calculateGcd(p, q);
    } else if (p < q) {
      return calculateGcd(q, p);
    } else {
      return p;
    }
  }

  public static int calculateGcd(int p, int q) {
    int r = p % q;
    if (r == 0) {
      return q;
    }
    return calculateGcd(q, r);
  }

  public static int stringToInt(String s) {
    int ret = 0;
    for (int i = 0; i < s.length(); ++i) {
      ret = ret * 10 + s.charAt(i) - '0';
    }
    return ret;
  }
}