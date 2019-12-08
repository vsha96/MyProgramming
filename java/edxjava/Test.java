import java.util.Scanner;
public class Test {

    public static int puzzle(int i, int j) {
        if (i == j) {
            return 0;
        } else {
            return 1 + puzzle(i-2, j-1);
        }
    }


    public static void main(String[] rags){
        /*
        Scanner input = new Scanner(System.in);
        int x = input.nextInt();
        String y = "";
        if (x < 30){
            x++;
            System.out.println(x);
        } else {
            System.out.println(x);
        }
        */
        //int z;
        /*
        String ar = "hello";
        System.out.println(ar.charAt(1));
        */
        /*
        int l=0;

        int x;
        for (x = 0;  x <= 7; x += 7) {
            System.out.println("Here");
        }
        System.out.println(x);

        System.out.println(l);
         */
        /*
        System.out.println(Math.ceil(2.1));
        System.out.println(Math.random()*10);
         */
        System.out.println(puzzle(22,11));

    }
}
