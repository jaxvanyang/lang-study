package algs4;

import edu.princeton.cs.algs4.StdOut;

/**
 * 接受一串括号序列，括号之间可以存在空格，判断括号是否匹配
 * 命令行参数可用引号包裹
 */
public class Parentheses {
    public static void main(String[] args) {
        var stack = new MyStack<Character>();
        for (var arg : args) {
            for (int i = 0; i < arg.length(); ++i) {
                char ch = arg.charAt(i);
                if (")]}".indexOf(ch) != -1) {
                    if (stack.isEmpty() || !isPair(stack.pop(), ch)) {
                        StdOut.println("括号不匹配");
                        return;
                    }
                } else {
                    stack.push(ch);
                }
            }
        }

        if (stack.isEmpty()) {
            StdOut.println("括号匹配");
        } else {
            StdOut.println("括号不匹配");
        }
    }

    public static boolean isPair(char a, char b) {
        if (a == '(' && b == ')' || a == '[' && b == ']' || a == '{' && b == '}') {
            return true;
        }
        return false;
    }
}
