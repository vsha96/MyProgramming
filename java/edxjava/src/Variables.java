public class Variables {
    public static void main(String[] args){
        //dataType variableName;
        int x = 10;
        System.out.println("My variable x contains " + x + 2*x);
        //x is local variable, it wont appears in other method
        //and now
        showClassConst();
    }
    //class constant (there is also convention about naming)
    public static final double PI = 3.14;
    public static final int MAX_SPEED = 80;
    public static void showClassConst(){
        System.out.println(PI);
        System.out.println("Max speed = " + MAX_SPEED);
    }
}
