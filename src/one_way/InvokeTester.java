package one_way;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;



/*
    一、Construction代表类中的一个构造方法，这个类封装了类的定义。

    其中包括了访问修饰符，方法名，参数列表。

    二、Constructor的常用方法

    1.String getName();获得方法名。

    2.int getModifiers();获得修饰符。

    3.Class[] getParamenterTypes();获得构造方法的参数类型。

    4.newInstance(Object...args);使用当前的构造方法来创建一个对象。

    三、如何获得Constructor

    1.Constructor getConstructor(Class..c);获得某个公共的构造方法。

    2.Constructor[] getConstructors();获得所有的构造方法。

    3.Constructor getDeclaredConstructor(Class..c);获得某个构造方法。

    4.Constructor[] getDeclaredConstructors();获得所有的构造方法。
*/

public class InvokeTester
{
    public int add(int param1, int param2)
    {
        return param1 + param2;

    }

    public String echo(String message)
    {
        return "Hello: " + message;
    }

    public static void main(String[] args) throws Exception
    {

        // 以前的常规执行手段
        InvokeTester tester = new InvokeTester();
        System.out.println(tester.add(1, 2));
        System.out.println(tester.echo("Tom"));
        System.out.println("---------------------------");

        // 通过反射的方式

        // 第一步，获取Class对象
        // 前面用的方法是：Class.forName()方法获取
        // 这里用第二种方法，类名.class

        //Class<?> classType = InvokeTester.class;
        Class<?> classType = Class.forName("one_way.InvokeTester");

        //Constructor<?> con = classType.getConstructor();
        Constructor<?> con = classType.getDeclaredConstructor();
        Object invokeTester = con.newInstance();
        // 生成新的对象：用newInstance()方法
        //Object invokeTester = classType.newInstance();
        System.out.println(invokeTester instanceof InvokeTester); // 输出true

        // 通过反射调用方法
        // 首先需要获得与该方法对应的Method对象
        Method addMethod = classType.getMethod("add", new Class[] { int.class, int.class });
        // 第一个参数是方法名，第二个参数是这个方法所需要的参数的Class对象的数组

        // 调用目标方法
        Object result = addMethod.invoke(invokeTester, 1, 2);
        System.out.println(result); // 此时result是Integer类型

        //调用第二个方法
        Method echoMethod = classType.getDeclaredMethod("echo", new Class[]{String.class});
        Object result2 = echoMethod.invoke(invokeTester, "Tom");
        System.out.println(result2);

    }
}