package one_way;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

//getDeclaredMethod*获取的是类自身声明的所有方法，包含public、protected和private方法

//getMethod*获取的是类的所有共有方法，这就包括自身的所有public方法，和从基类继承的、从接口实现的所有public方法。


class Person {

    private int age;
    private String name;

    public Person( String name,int age) {
        this.age = age;
        this.name = name;
    }

    public Person() {
    }


    //公有 有参方法
    public void public_show(String str,int i)
    {
        System.out.println("public show "+str+"..."+i);
    }

    //公有 无参方法
    public void public_prin()
    {
        System.out.println("public prin");
    }


    //私有 有参方法
    private void private_show(String str,int i)
    {
        System.out.println("private show "+str+"..."+i);
    }

    //私有 无参方法
    private void private_prin()
    {
        System.out.println("private prin");
    }

}


public class reflectionTest {
    public static void main(String[] args) throws Exception {

        //获取字节码文件中 方法 再取出其公有方法

//        String classname = "one_way.Person";
//        //寻找名称的类文件，加载进内存 产生class对象
//        Class<?> cl = Class.forName(classname);

//        //获取一个Person对象
//        System.out.println("获取一个Person对象:");
//        Object obj = cl.newInstance();

        Class<?> cl = Person.class;
        // 获得Constructor对象,此处获取第一个无参数的构造方法的
        Constructor<?> cons = cl.getConstructor(new Class[] {});
        // 通过构造方法来生成一个对象
        Object obj = cons.newInstance(new Object[] {});

        Class<?> cl1 = Person.class;
        Constructor<?> cons2 = cl1.getConstructor(String.class, int.class);
        Object obj1 = cons2.newInstance("ZhangSan",20);


        System.out.println();


        //1.获取 公有 无参方法 public void demo2.Person.public_prin()
        Method Person_public_prin = cl.getMethod("public_prin");
        System.out.println("获取执行 public void demo2.Person.public_prin() :");
        Person_public_prin.invoke(obj);

        System.out.println();

        //2.获取 公有 有参方法 public void demo2.Person.public_show(java.lang.String,int)
        Method Person_public_show = cl.getMethod("public_show", String.class, int.class);
        System.out.println("获取执行 public void demo2.Person.public_show(java.lang.String,int) :");
        Person_public_show.invoke(obj, "神奇的我", 12);

        System.out.println();

        //3.获取 私有 无参方法 private void demo2.Person.private_prin()
        Method Person_private_prin = cl.getDeclaredMethod("private_prin",null);
        Person_private_prin.setAccessible(true);
        System.out.println("获取执行 private void demo2.Person.private_prin() :");
        Person_private_prin.invoke(obj,  null);

        System.out.println();

        //4.获取 私有 有参方法 private void demo2.Person.private_show(java.lang.String,int)
        Method Person_private_show = cl.getDeclaredMethod("private_show", String.class, int.class);
        Person_private_show.setAccessible(true);
        System.out.println("获取执行 private void demo2.Person.private_show(java.lang.String,int) :");
        Person_private_show.invoke(obj, "神奇的私有", 23);

        System.out.println();

    }
}