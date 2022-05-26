package mySoution;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

class Student implements Comparable<Student>{
    int id;
    int age;
    String name;
    public Student(int id,int age,String name) {
        // TODO 自动生成的构造函数存根
        this.id = id;
        this.age = age;
        this.name = name;
    }
    //以下方法三个均是为了该类的封装性
    public int getId() {
        return id;
    }

    public int getAge() {
        return age;
    }

    public String getName() {
        return name;
    }
    //便于返回每个对象的信息
    public String toString() {
        return "Student{"+"id="+id+", age="+age+", name= "+name+"}";
    }
    //重点：重写该方法定义排序方式
    //@Override
    public int compareTo(Student o) {
        // TODO 自动生成的方法存根
        //return this.age - o.age;//按升序排列
        return o.age - this.age;//按降序排列
    }

}


public class collection {
    public static void main(String[] args) {
        // TODO 自动生成的方法存根
        ArrayList<Student> s = new ArrayList<Student>();
        Student s1 = new Student(1,24,"1");
        Student s2 =new Student(4,23,"2");
        Student s3 =new Student(2,22,"3");
        Student s4 = new Student(3,25,"4");
        Student s5 = new Student(5,24,"5");
        s.add(s1);
        s.add(s2);
        s.add(s3);
        s.add(s4);
        s.add(s5);

        System.out.println("排序前");
        for (Student student : s) {
            System.out.println(student.toString());
        }

        Collections.sort(s);
//第一种方法根据age来排序
        System.out.println("默认排序");
        for (Student student : s) {
            System.out.println(student.toString());
        }

//第二种方法根据id来排序
//Collections.sort(s, new Comparator<Student>() {
//
//	//@Override
//	public int compare(Student s1, Student s2) {
//		// TODO 自动生成的方法存根
//		//以下两种方法均可，但第二种破坏了封装性，故不采用
//		return s1.getId() - s2.getId();
//	    //return s1.id-s2.id;
//	}
//});

//第三种方法根据id来排序
//        s.sort(new Comparator<Student>() {//使用匿名类
//            //这样实现接口不用再专门写一格实现类了。
//            public int compare(Student s1, Student s2) {
//                // TODO 自动生成的方法存根
//                //return s1.getId() - s2.getId();//升序
//                return s2.getId() - s1.getId();//降序
//            }
//        });
        s.sort((s11, s21) -> {
            //return s1.getId() - s2.getId();//升序
            return s21.getId() - s11.getId();//降序
        });
        System.out.println("排序后");
        for (Student student : s) {
            System.out.println(student.toString());
        }
        //使用匿名类
//这样实现接口不用再专门写一格实现类了。
    }
}
