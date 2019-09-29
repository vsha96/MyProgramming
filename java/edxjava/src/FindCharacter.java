import java.util.Scanner;
public class FindCharacter
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        String input = sc.next();
        char test = 'v';// Character input
        // Write the logic to find the given character is found in the given string using a while loop
        int i = 0;
        String answer = "Not Found";
        while (i < input.length()) {
            if (input.charAt(i) == test) {
                answer = "Found";
            }
            i++;
        }
        System.out.println(answer);
    }
}