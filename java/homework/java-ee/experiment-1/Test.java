import java.lang.reflect.Field;

public class Test {
    public static void main(String[] args) throws Exception {
        Object student = new Student();

        Class stdClass = student.getClass();
        // System.out.println(stdClass.getDeclaredField("name"));

        Field fId = stdClass.getDeclaredField("id");
        fId.setAccessible(true);
        fId.set(student, 10);
        System.out.println(fId + ": " + fId.get(student));

        Field fName = stdClass.getDeclaredField("name");
        fName.setAccessible(true);
        fName.set(student, "小明");
        System.out.println(fName + ": " + fName.get(student));

        Field fSex = stdClass.getDeclaredField("sex");
        fSex.setAccessible(true);
        fSex.set(student, true);
        System.out.println(fSex + ": " + fSex.get(student));

        Field fAccount = stdClass.getDeclaredField("account");
        fAccount.setAccessible(true);
        fAccount.set(student, 12.34);
        System.out.println(fAccount + ": " + fAccount.get(student));
    }
}
