package one_way;

//抽象
//abstract方法只能声明，不能实现
//不允许使用final和abstract同时修饰一个方法或者类，也不允许使用static修饰abstract方法


abstract class GirlFriend{ //抽象类，封装了两个行为标准

    abstract void speak();

    abstract void cooking();

}

class ChinaGirlFriend extends GirlFriend{

    void speak(){

        System.out.println("你好");

    }

    void cooking(){

        System.out.println("水煮鱼");

    }

}

class AmericanGirlFriend extends GirlFriend{

    void speak(){

        System.out.println("hello");

    }

    void cooking(){

        System.out.println("roast beef");

    }

}

class boy{

    GirlFriend friend;

    boy(){}

    boy(GirlFriend f){
        friend=f;
    }

    void setGirlFriend(GirlFriend f){

        friend=f;

    }

    void showGirlFriend(){

        friend.speak();

        friend.cooking();

    }

}



public class abstractTest{

    public static void main(String[] args){

        GirlFriend girl =new ChinaGirlFriend(); //这里girl是上转型对象

        boy boy=new boy(girl);

        boy.showGirlFriend();

        girl=new AmericanGirlFriend();//girl 是上转型对象

        boy.setGirlFriend(girl);

        boy.showGirlFriend();

    }

}