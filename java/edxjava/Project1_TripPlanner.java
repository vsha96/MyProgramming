import java.util.Scanner;
public class Project1_TripPlanner {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        greeting(input);

    }
    public static void greeting(Scanner input){
        System.out.print("Hello. Welcome to Trip Planner!\nWhat is your name? ");
        String name = input.nextLine();
        System.out.print("Nice to meet you " + name + ", where are you travelling to? ");
        String destination = input.nextLine();
        System.out.println("Great! " + destination + " sounds like a great trip!");
        nextPart();

    }
    /*
    public static void calculateTravelTimeAndBudget(){

    }
    public static void timeDifference(){

    }
    public static void calculateCountryArea(){

    }
    */
    public static void nextPart(){
        System.out.println("************");
    }
}
