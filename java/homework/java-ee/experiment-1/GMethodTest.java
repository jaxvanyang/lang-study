import java.util.Collections;
import java.lang.Comparable;
import java.util.ArrayList;

class Circle implements Comparable<Circle> {
	private double radius;

	public Circle(double radius) {
		this.radius = radius;
	}

	@Override
	public String toString() {
		return "Circle radius: " + radius;
	}

	@Override
	public boolean equals(Object o) {
		Circle c = (Circle) o;
		return radius == c.radius;
	}

	public int compareTo(Circle c) {
		if (radius > c.radius) {
			return 1;
		} else if (radius < c.radius) {
			return -1;
		} else {
			return 0;
		}
	}
}

public class GMethodTest {
	public static <E extends Comparable<E>> ArrayList<E> removeDuplicates(ArrayList<E> list) {
		Collections.sort(list);

		ArrayList<E> ret = new ArrayList<>();

		int l = 0;

		while (l < list.size()) {
			int r = l;

			while (r < list.size() && list.get(l).equals(list.get(r))) {
				++r;
			}

			ret.add(list.get(l));

			l = r;
		}

		return ret;
	}

	public static <E extends Comparable<E>> E max(E[] list) {
		if (list.length == 0) {
			return null;
		}

		E ret = list[0];

		for (int i = 1; i < list.length; ++i) {
			if (list[i].compareTo(ret) > 0) {
				ret = list[i];
			}
		}

		return ret;
	}

	public static void main(String[] args) {
		ArrayList<Integer> list = new ArrayList<Integer>();
		ArrayList<Circle> circles = new ArrayList<>();

		list.add(14);
		list.add(24);
		list.add(14);
		list.add(12);

		circles.add(new Circle(3));
		circles.add(new Circle(2.9));
		circles.add(new Circle(5.9));
		circles.add(new Circle(3));

		ArrayList<Integer> newList = removeDuplicates(list);
		ArrayList<Circle> newCircles = removeDuplicates(circles);

		System.out.println(newList);
		System.out.println(newCircles);

		Integer[] numbers = {1, 2, 3};
		System.out.println(max(numbers));

		Circle[] c = {new Circle(3), new Circle(2.9), new Circle(5.9)};
		System.out.println(max(c));
	}
}
