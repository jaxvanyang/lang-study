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
        if (year < 1900) return -1;
        int ret = (year - 1900) * 365;
        ret += (year - 1) / 4 - 1899 / 4;
        ret -= (year - 1) / 100 - 1899 / 100;
        ret += (year - 1) / 400 - 1899 / 400;
        for (int i = 1; i < month; ++i) ret += getDays(year, month);
        return ret;
    }

    // 1900 年 1 月 1 号 是星期一，据此推算某年某月第一天是星期几
    public static int getWeek(int year, int month) {
        return (countDays(year, month) + 1) % 7;
    }

    public static void main(String[] args) {
        int year = 1900, month = 1;
        System.out.println(year + " is leap ? " + isLeap(year));
        System.out.println(year + "." + month + " has " + getDays(year, month));
        System.out.println(year + "." + month + " first day is " + weeks[getWeek(year, month)]);
    }
}
