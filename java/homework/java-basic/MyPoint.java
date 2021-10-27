public class MyPoint {
    public double x, y;

    public MyPoint(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public void set(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double x() {
        return x;
    }

    public double y() {
        return y;
    }

    public double distance(MyPoint p) {
        return Math.sqrt(Math.pow(x - p.getX(), 2) + Math.pow(y - p.getY(), 2));
    }

    public static void main(String[] args) {
        var p = new MyPoint(10, 10);
        System.out.println("x = " + p.getX() + " y = " + p.getY());
    }
}
