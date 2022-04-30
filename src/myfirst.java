//继承
class teacher{             //声明一个teacher类为父类
	String name;      	   //定义父类的成员变量name、age   
	int age;
	void show(){           //定义父类成员方法，将成员变量输出
		System.out.println(name); 	  
		System.out.println(age); 
	}
}
class Student extends teacher {     //声明一个Student类为子类并继承父类
 }

public class myfirst {
	public static void main(String[] args) {
	System.out.println("学生");
	Student student=new Student();     //声明一个Student类的实例对象student
	student.name="Tom";                //子类调用父类的成员变量name并赋值
	student.age=19;                    //子类调用父类的成员变量age并赋值
	student.show();                    //子类调用父类的成员方法show
	}
}
