import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;

public class Problem2 {
    public static <E extends Number> List<? super E> process(List<E> nums) {
        return new ArrayList<E>();
    }

    public static void main(String[] args) {
        // ArrayList<Integer> input = null; ArrayList<Integer> output = null;
        // ArrayList<Integer> input = null; List<Integer> output = null;
        // ArrayList<Integer> input = null; List<Number> output = null;
        // List<Number> input = null; List<Number> output = null;
        // List<Number> input = null; List<Number> output = null;
        List<Integer> input = null; List<Integer> output = null;
        
        System.out.println(process(input) instanceof List);

        output = process(input);
        
        System.out.println(process(input).getClass());
    }
}
