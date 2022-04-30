/*
final修饰的变量 如果这个变量是一个"引用"会怎么样？
  final修饰的变量只能赋一次值
  "引用"是否是一个变量 ：是

  总结：final修饰的引用
       1.该引用只能指向1个对象 并且它只能永远指向该对象
       无法再指向其他对象
       2.在该方法执行过程中，该应用指向该对象之后，该对象不会          被垃圾回收器回收，直到当前方法结束，才会释放空间
       3.虽然final的引用指向对象A后，不能重新指向对象B
         但是对象A内部的数据可以被修改
*/
public class FinalTest01{
    public static void main(String[]args){
        //Person p=new Person(20);
        //System.out.println(p.age);
        //--------------------------------------
        // 代码不管怎么变化，p也是一个变量，只不过他是引用

        //错误：无法为最终变量p分配值 地址不能改变
        final Person p=new Person(30);//0x1234;
        p.setAge(40);//0x2589
        System.out.println(p.age);


    }

}

class Person{
    int age;
    public Person(){}
    public Person(int age){
        this.age = age;
    }

    public void setAge(int age){
        this.age = age;
    }

}
