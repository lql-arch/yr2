package tset;

class Something {

    // constructor methods
    Something() {}

    Something(String something) {
        System.out.println(something);
    }

    // static methods
    static String startsWith(String s) {
        return String.valueOf(s.charAt(0));
    }

    // object methods
    String endWith(String s) {
        return String.valueOf(s.charAt(s.length()-1));
    }

    void endWith() {}
}

@FunctionalInterface
interface IConvert<F, T> {
    T convert(F form);
}

public class test4 {
    public static void main(String[] args) {
        // static methods
        IConvert<String, String> con = Something::startsWith;
        String converted = con.convert("123");
        System.out.println(converted);

        String s = Something.startsWith("123");


        // object methods
        Something something = new Something();
        IConvert<String, String> converter = something::endWith;
        String converted1 = converter.convert("Java");
        System.out.println(converted1);

        // constructor methods
        IConvert<String, Something> convert1 = Something::new;
        Something something1 = convert1.convert("constructors");


    }
}
