package tset;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class test9 {
        public static void main(String[] args) {
            String arr[]=new String[]{"aaa","bbb","ccc"};
            List<String> list = Arrays.asList(arr);
            test9 test03=new test9();
            //引用实例方法，通过对象+::+方法名的方式
            list.forEach(test03::print);
        }
        public void print(String s){
            System.out.println(s);
        }


}


class Test08 {

    String name;

    public Test08(String name) {
        this.name = name;
    }
    public static void main(String[] args) {
        //构造器的参数要和接口的参数保持一致，同样使用类名+::+new的方式来引用
        Wo wo=Test08::new;
        Test08 test08 = wo.creat("hello world");
        System.out.println(test08.name);
    }

}
interface Wo{
        Test08 creat(String name);
}


class Test06 {
    public void test() {
        //引用构造器使用类名::new
        InterfaceExample com = Test06::new;
        Test06 bean = com.create();
        System.out.println(bean);
        System.out.println((new Test06()));
    }
}

interface InterfaceExample{
    Test06 create();
}

class Test07{
    public static void main(String[] args) {
        Test06 test06=new Test06();
        test06.test();
        System.out.println(test06);
    }
}




class Test04 extends Test04Fu {
    public  void test() {
        String[] arr =new String[]{"aaa","bbb","ccc"};
        List<String> list = Arrays.asList(arr);
        //引用父类方法，通过super+::+方法名的方式
        list.forEach(super::print);
    }
}
class Test04Fu{
    void print(String s){
        System.out.println(s);
    }
}
class Test05{
    public static void main(String[] args) {
        Test04 test04=new Test04();
        test04.test();
    }
}
