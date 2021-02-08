import edu.princeton.cs.algs4.*;
import algs4.*;

public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
    StdDraw.point(1, 1);
    StdDraw.line(0, 0, 1, 1);

    var counter = new Counter("001");
    System.out.println(counter.tally());
    f(counter);
    System.out.println(counter.toString());
    System.out.println(counter.tally());
  }

  public static void f(Counter counter) {
    counter.increament();
  }
}
