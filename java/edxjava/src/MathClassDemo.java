public class MathClassDemo {
    public static void main(String[] args) {
        //Pythagorean theorem
        int a = 3, b = 4;
        double aSq = Math.pow(a, 2);
        double bSq = Math.pow(b, 2);
        double c = Math.sqrt(aSq + bSq);
        System.out.println("hypotenuse c = " + c);
    }
}
