import java.util.Scanner;
public class DaysInMonth {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int month = input.nextInt();
        daysInMonth(month);
    }
    public static void daysInMonth(int month) {
        if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8)
                || (month == 10) || (month == 12)){
            System.out.println("31");
        } else if ((month == 2)) {
            System.out.println("28");
        } else {
            System.out.println("30");
        }
    }
}
