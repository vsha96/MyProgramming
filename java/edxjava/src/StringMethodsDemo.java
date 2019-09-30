public class StringMethodsDemo {
    public static void main(String[] args){
        String str = "abcde";
        for (int i = 0; i < str.length(); i++){
            System.out.println("the character at " + i + " is " + str.charAt(i));
        }
        System.out.println("the letter 'e' at index " + str.indexOf('e'));
        System.out.println("the letter 'A' at index " + str.indexOf('A'));
        str = str.toUpperCase();
        System.out.println(str);
        System.out.println("the letter 'A' at index " + str.indexOf('A'));
    }
}
