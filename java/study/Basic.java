public class ChStr {
    public static void main(String[] args) {
        char ch1 = 'A';
        char ch2 = '中';
        String str = "😃😜😍";
        // char ch3 = '😃'; Java 的 char 只有 16 bit，不能表示 32 位的 Unicode
        
        print(str);
    }
    public static void print(char ch) {
        System.out.print(ch);
    }
    public static void print(String str) {
        System.out.print(str);
    }
    public static void println(char ch) {
        System.out.println(ch);
    }
    public static void println(String str) {
        System.out.println(str);
    }
}