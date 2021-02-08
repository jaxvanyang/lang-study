package algs4;

public class Counter {

  int value = 0;
  String id;

  public Counter(String id) {
    this.id = id;
  }

  public void increament() {
    ++value;
  }

  public int tally() {
    return value;
  }

  // String toSting() {
  // return id + ": " + value;
  // }
}
