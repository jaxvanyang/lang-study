public class Student {

    private int id; // 表示学生的序号

    private String name; // 表示学生的姓名

    private boolean sex; // 表示学生的性别

    private double account; // 表示学生的账户余额

    public Student() {
    }

    public Student(int id, String name) {

        this.id = id;

        this.name = name;

        this.sex = true;

        this.account = 0;

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean isMale() {
        return sex;
    }

    public void setMale(boolean sex) {
        this.sex = sex;
    }

    public double getAccount() {
        return account;
    }

    public void setAccount(double account) {
        this.account = account;
    }

    public void f1() {

        System.out.println("f1 method");

    }

    public void f1(String s) {

        System.out.println("f1 method " + s);

    }

    public String f1(String s, Integer i) {

        return ("f1 method " + s + " " + i);

    }

}