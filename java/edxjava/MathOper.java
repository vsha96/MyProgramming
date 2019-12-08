public class MathOper {
    public static void main(String[] args){
        int x = 10, y = 15;
        System.out.println("x + y = " + (x + y));
        //shortcuts
        x++;
        y *= 3;
        System.out.println("x and y is " + (x*=10) + " and "+ y);
        System.out.println(x);
    }
}
