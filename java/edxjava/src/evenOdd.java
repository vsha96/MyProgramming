import java.util.Scanner;
public class evenOdd {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        System.out.print("Type a number: ");
        int number = input.nextInt();
        if (number % 2 == 1){
            System.out.println("odd");
        } else {
            System.out.println("even");
        }
    }
}
