import edu.princeton.cs.algs4.*;
import algs4.*;

public class Main {
    public static void main(String[] args) {
        String formula = "(11 + 12) * 23 - 24 / 15.9";
        String formatedFormula = formatFormula(formula);
        String[] parsedFormula = formatedFormula.split("\\s+");
        for (var i : parsedFormula) {
            StdOut.println(i);
        }
        MyStack<String> ops = new MyStack<>();
        MyStack<Double> vals = new MyStack<>();

        for (var item : parsedFormula) {
            if (item.length() == 0) {
                continue;
            }
            if (")".equals(item)) {
                double y = vals.pop();
                double x = vals.pop();
                String opt = ops.pop();
                vals.push(calculate(x, y, opt));
            } else if ("+-*/".indexOf(item) != -1) {
                ops.push(item);
            } else if ("(".equals(item)) {
                continue;
            } else {
                vals.push(Double.parseDouble(item));
            }
        }

        for (var op : ops) {
            StdOut.print(op + " ");
        }
        StdOut.println();

        // for (var val : vals) {
        //     StdOut.print(val + " ");
        // }

        while (!ops.isEmpty()) {
            StdOut.println("ops.size = " + ops.getSize() + " val.size = " + vals.getSize());
            double y = vals.pop();
            double x = vals.pop();
            String opt = ops.pop();
            vals.push(calculate(x, y, opt));
        }

        assert vals.getSize() == 1;
        StdOut.print(vals.pop());
    }

    public static String formatFormula(String formula) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < formula.length(); ++i) {
            char ch = formula.charAt(i);
            if ("+-*/()".indexOf(ch) != -1) {
                sb.append(" " + ch + " ");
            } else {
                sb.append(ch);
            }
        }
        return sb.toString();
    }

    public static double calculate(double x, double y, String opt) {
        switch (opt) {
            case "+":
                return x + y;
            case "-":
                return x - y;
            case "*":
                return x * y;
            case "/":
                assert y != 0;
                return x / y;
            default:
                throw new RuntimeException("未定义的操作符！");
        }
    }
}
