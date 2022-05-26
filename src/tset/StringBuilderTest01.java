package tset;

public class StringBuilderTest01 {
    public static void main(String[] args) {
        StringBuilder s = new StringBuilder("hello java");
        int cap = s.capacity();
        System.out.println(s+" cap:"+cap);
        s.append(" 114514191981011111111111111111111111");
        int len = s.length();
        cap = s.capacity();
        s.delete(17, len);
        System.out.println(s+" cap:"+cap);
        len = s.length();
        s.replace(0, len, "12");
        System.out.println(s);
        //s.delete(0, 2);
        //System.out.println(s);
        s.reverse();
        s.setCharAt(0, '9');
        s.trimToSize();// 重设容量
        cap = s.capacity();
        System.out.println(s+" cap:"+cap);
        System.out.println(s.substring(1,2));
        s.setLength(0);

//        //代码1
//        String sa = "ab";
//        String sb = "cd";
//        String sab=sa+sb;
//        String s="abcd";
//        System.out.println(sab==s); // false
//        //代码2
//        String sc="ab"+"cd";
//        String sd="abcd";
//        System.out.println(sc==sd); //true
//
//        String s1 = "lrj";
//        String s2 = "lrj";
//        String s3 = new String(s1.toCharArray());
//        System.out.println(s3);

    }
}

