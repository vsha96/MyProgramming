public class RecursiveDemo {
    public static int factorial(int x){
        if (x == 1) {
            return 1;
        } else {
            return x * factorial(x - 1);
        }
    }
    public static int fibonacci(int n) {
        if (n == 1) {
            return 1;
        } else if (n == 2) {
            return 1;
        } else {
            return fibonacci(n-1) + fibonacci(n-2);
        }
    }
    public static void main(String[] args){
        int x = 6;
        System.out.println("factorial of " + x + " is " + factorial(x));
        System.out.println("fibonacci number at " + x + " is " + fibonacci(x));
    }
}
