import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

public class TestMethod {
    public static Object executeMethod(String className, String methodName, Object... args) throws Exception {
        Class c = Class.forName(className);

        Constructor constructor = c.getConstructor();

        Class[] types = new Class[args.length];
        for (int i = 0; i < args.length; ++i) {
            types[i] = args[i].getClass();
        }

        Method m = c.getDeclaredMethod(methodName, types);
        m.setAccessible(true);

        return m.invoke(constructor.newInstance(), args);
    }

    public static void test(Object... objs) {
        System.out.println(objs.getClass());
    }

    public static void main(String[] args) throws Exception {
        Object obj = new Student();

        Class c = obj.getClass();
        String className = c.getName();
        String methodName = "f1";

        executeMethod(className, methodName);
        executeMethod(className, methodName, "only one String argument");

        String res = (String) executeMethod(className, methodName, "this is a String", 10000);
        System.out.println(res);
    }
}
