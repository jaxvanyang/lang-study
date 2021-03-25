import java.util.Scanner;

public class PrintCalendar {
    public static String[] weeks = { "Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat" };

    public static boolean isLeap(int year) {
        return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
    }

    public static int getDays(int year, int month) {
        switch (month) {
        case 1, 3, 5, 7, 8, 10, 12:
            return 31;
        case 4, 6, 9, 11:
            return 30;
        }
        return isLeap(year) ? 29 : 28;
    }

    // 计算某年某月的第一天距 1900 年 1 月 1 号过去了多少天
    public static int countDays(int year, int month) {
        if (year < 1900)
            return -1;
        int ret = (year - 1900) * 365;
        ret += (year - 1) / 4 - 1899 / 4;
        ret -= (year - 1) / 100 - 1899 / 100;
        ret += (year - 1) / 400 - 1899 / 400;
        // System.out.println("year days = " + ret);
        for (int i = 1; i < month; ++i)
            ret += getDays(year, i);
        // System.out.println("total days = " + ret);
        return ret;
    }

    // 获取某年某月第一天星期几的代号
    // 1900 年 1 月 1 号 是星期一，据此推算某年某月第一天是星期几
    public static int getWeekdayNo(int year, int month) {
        return (countDays(year, month) + 1) % 7;
    }

    public static void printTable(int year, int month) {
        // 打印表头
        System.out.printf("%18d-%d", year, month);
        System.out.println();
        for (int i = 0; i < 7; ++i) {
            System.out.printf("%5s", weeks[i]);
        }
        System.out.println();

        // 获取月份开始日星期和一共的日子数
        int no = getWeekdayNo(year, month);
        int days = getDays(year, month);

        // 打印第一行
        // 先处理空缺
        for (int i = 0; i < no; ++i)
            System.out.print("     ");
        // 再打印第一行剩下的
        for (int i = 1; i <= 7 - no; ++i)
            System.out.printf("%5d", i);
        System.out.println();
        
        // 余下行只需打印剩下的日子
        int day = 8 - no;
        while (day <= days) {
            for (int i = 0; i < 7 && day <= days; ++i)
                System.out.printf("%5d", day++);
            System.out.println();
        }
    }

    public static void printYearTable(int year) {
        for (int i = 1; i <= 12; ++i) {
            printTable(year, i);
            System.out.println();
        }
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int year = scanner.nextInt();
            int month = scanner.nextInt();
            printTable(year, month);
            // System.out.printf("Below is %d's year calendar:\n", year);
            // printYearTable(year);
        }
    }
}
