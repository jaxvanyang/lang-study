import java.util.Scanner;

public class Polygon {
    private MyPoint[] ps;
    private int n;

    public static void main(String[] args) {
        var polygon = new Polygon();
        System.out.println("area = " + polygon.calcArea());
    }

    public Polygon() {
        Scanner s = new Scanner(System.in);
        System.out.println("输入顶点数：");
        int n = s.nextInt();
        this.n = n;
        ps = new MyPoint[n + 1];
        System.out.println("顺时针输入顶点坐标：");
        for (int i = 0; i < n; ++i) {
            double x = s.nextDouble();
            double y = s.nextDouble();
            System.out.println("x = " + x + " y = " + y);
            ps[i] = new MyPoint(x, y);
        }
        s.close();    
        ps[n] = ps[0];
    }

    public double calcArea() {
        double s = 0;
        for (int i = 0; i < n; ++i) {
            s += (ps[i].x + ps[i + 1].x) * (ps[i + 1].y - ps[i].y);
        }
        return 0.5 * Math.abs(s);
    }
}