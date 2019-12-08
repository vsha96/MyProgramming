public class Power2 {
    public static void power2(int exp){
        int result = 1;
        for (int i = 1; i <= exp; i++){
            result = 2*result;
        }
        System.out.println("2 to the "+exp+" = "+result);
    }
    //there is overloaded method
    public static void power(double base, double exp){
        double result = 1;
        for (int i = 1; i <= exp; i++) {
            result = base*result;
        }
        System.out.println(base + " to the "+exp+" = "+result);
    }
    public static void power(int base, int exp){
        double dbase = base;
        double dexp = exp;
        power(dbase,dexp);
    }

    public static void main(String[] args){

        power(3,3);
    }
}
