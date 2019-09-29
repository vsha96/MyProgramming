import java.util.Scanner; //1
public class LearnScanner {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in); //2
        System.out.println("Hi\nWhats your name?");
        String name = input.next(); //3
        System.out.println("Hi " + name);
        int count = input.nextInt();
        double weight = input.nextDouble();
        System.out.println("count of fruits is " + count + " and weight of it is " + weight);
    }
}
