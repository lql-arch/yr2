/*
一般情况下
实例变量如果还没有赋值的话，系统会赋默认值

final 修饰实例变量：
系统不负责赋默认值，要求程序员必须手动赋值，只能赋一次，
这个手动赋值，在变量后面赋值可以，在构造方法中赋值也可以



*/
public class FinalTest02{
    public static void main(String[]args){

    }
}


class User{
    //实例变量

    //错误： 变量age未在默认构造器中初始化
    //final int age;
    final int age=10;

    //在构造方法中赋值 weight只赋一次值
    final double weight;
    //构造方法
    public User(){
        this.weight=80;
        //系统赋默认值在这个时候,final修饰后，系统不会赋值
        //this.weight=0;
    }


}
