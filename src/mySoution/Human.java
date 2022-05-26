package mySoution;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Human {
    private String name;

    private int age;

    public Human() {
    }

    public Human(String name, int age) {

        this.name = name;

        this.age = age;

    }

    public String getName() {

        return name;

    }

    public void setName(String name) {//该方法方便初始化之后可以更改相关值

        this.name = name;

    }

    public int getAge() {

        return age;

    }

    public void setAge(int age) {

        this.age = age;

    }


    //这种初始的方法可以留意一下
    public static List<Human> getAInitHumanList() {

        return new ArrayList<Human>() {

            {

                add(new Human("guorao", 10));

                add(new Human("mako", 12));

                add(new Human("hel", 30));

                add(new Human("lin", 28));

            }

        };

    }

    @java.lang.Override

    public String toString() {

        return this.getName() + ":" + this.getAge();

    }

//    public class HumanComparetor implements Comparator<Human> {//内部类
//
//        @java.lang.Override
//
//        public int compare(Human h1, Human h2) {
//
//            return h1.getAge() - h2.getAge();
//            //return Integer.compare(h1.getAge(), h2.getAge());
//
//        }
//
//    }


//    public static void main(String[] args) {
//        // TODO 自动生成的方法存根
//        List<Human> humans = Human.getAInitHumanList();
//         //Collections.sort(humans, new HumanComparetor());
//        Human human1 = new Human();
//        HumanComparetor h = human1.new HumanComparetor();
//
//        /* 如果使用+处的代码，则会出现以下编译提示
//         *没有任何类型 Human 的外层实例可访问。
//         *必须用类型 Human 的外层实例（例如，x.new A()，
//         *其中 x 是 Human 的实例）来限定分配。
//         *所以应替换成如下+处的代码这是内部类调用的规则
//         *先创建一个外部类实例，再通过该实例实例化内部类
//         *Human human1 = new Human();
//         *HumanComparetor h = human1.new HumanComparetor();即可调用内部类的方法与实例变量*/
//
//        //Human human1 = new Human();
//        Collections.sort(humans, h);
//        for (Human human : humans) {
//            System.out.println(human.toString());
//        }
//    }

    public static void main(String[] args) {
        List<Human> humans = Human.getAInitHumanList();
//        class HumanComparetor implements Comparator<Human> {
//            @java.lang.Override
//            public int compare(Human h1, Human h2) {
//                return h1.getAge() - h2.getAge();
//            }
//        }
//        Collections.sort(humans, new HumanComparetor());

        humans.sort((o1,o2)->{
            return  o1.getAge() - o2.getAge();
        });
        for (Human human : humans) {
            System.out.println(human.toString());
        }
    }
}




