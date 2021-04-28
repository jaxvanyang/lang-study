
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class ShapeAndGeoArrayList {

    public static void main(String[] args) {
        ArrayList<Shape> p1 = new ArrayList<Shape>();
        p1.add(new Circle(2));
        p1.add(new Circle(3));
        p1.add(new Circle(1));

        ArrayList<Shape> p2 = new ArrayList<Shape>();
        p2.add(new Rectangle(1, 2));
        p2.add(new Rectangle(1, 4));
        p2.add(new Rectangle(1, 3));

        GeoArrayList lead = new GeoArrayList(p1);
        lead.insertGeoList(p2);
        lead.displayGeoList();
    }

}

class Shape {

    protected Shape() {
    }

    public double getArea() {
        double Area = 0;
        return Area;
    }

    public double getPerimeter() {
        double Perimeter = 0;
        return Perimeter;
    }

    public void printclassname() {
    }
}

class Circle extends Shape {
    private double r = 0;

    public Circle(double r) {
        this.r = r;
    }

    public double getArea() {
        double Area = 0;
        Area = r * r * Math.PI;
        return Area;
    }

    public double getPerimeter() {
        double Perimeter = 0;
        Perimeter = 2 * r * Math.PI;
        return Perimeter;
    }

    public void printclassname() {
        System.out.println("该类为Circle:面积为:" + getArea());
    }
}

class Rectangle extends Shape {
    private double longer = 0;
    private double wider = 0;

    public Rectangle(double longer, double wider) {
        this.longer = longer;
        this.wider = wider;
    }

    public double getArea() {
        double Area = 0;
        Area = longer * wider;
        return Area;
    }

    public double getPerimeter() {
        double Perimeter = 0;
        Perimeter = 2 * (longer + wider);
        return Perimeter;
    }

    public void printclassname() {
        System.out.println("该类为Rectangle:面积为:" + getArea());
    }
}

class GeoArrayList {

    private ArrayList<Shape> Geo;
    private int size;

    {
        Geo = new ArrayList<Shape>();
        size = 0;
    }

    public GeoArrayList(ArrayList<Shape> aa)// 含参构造
    {
        Geo = aa;
        size += aa.size();
        // Geo.compare();
        // Collections.sort(Geo);
        sortsort();
    }

    public void sortsort()// 升序按面积排列 排序方法
    {
        Collections.sort(Geo, new Comparator<Shape>() {
            @Override
            public int compare(Shape o1, Shape o2) {
                if (o1.getArea() >= o2.getArea()) {
                    return 1;
                } else {
                    return -1;
                }
            }
        });
    }

    public void insertGeoList(ArrayList<Shape> a)// 插入ArrayList
    {
        Geo.addAll(a);
        size += a.size();
        sortsort();
    }

    public void insertGeoShape(Shape a)// 插入图形对象
    {
        Geo.add(a);
        size++;
        sortsort();
    }

    public void reMove(Shape a)// 删除图形对象、
    {
        Geo.remove(a);
        size--;
    }

    public int getIndex(Shape a)// 得到对象在列表的位置、
    {
        return Geo.indexOf(a);
    }

    public Shape get(int index)// 读指定位置的对象、
    {
        return Geo.get(index);
    }

    public int Size()// 返回列表长度
    {
        return size;
    }

    public void Clear()// 清空列表、
    {
        Geo.clear();
    }

    public boolean Contains(Shape a)// 判断图形是否在列表中、
    {
        return Geo.contains(a);
    }

    public void displayGeoList()// 依次显示列表中的所有对象的面积及对象的类别名称
    {
        for (int i = 0; i < size; i++) {
            Geo.get(i).printclassname();
        }
    }

    public boolean compare(Shape o1, Shape o2) {
        if (o1.getArea() <= o2.getArea()) {// o1属性小于等于o2属性时，返回1
            return true;
        } else {
            return false;
        }
    }
}
