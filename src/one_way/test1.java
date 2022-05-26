package one_way;

import java.io.*;

public class test1 {
    public static class Person implements Serializable {
        private static final long serialVersionUID = 233858934995755239L;
        private String firstName;
        private String lastName;

        public Person(String firstName,String lastName){
            System.out.println("Init Person...");
            this.firstName = firstName;
            this.lastName = lastName;
        }
        public String toString() {
            return String.format("Pearson.toString(): firstName=%s,lastName=%s", firstName, lastName);
        }
    }

    public static void main(String[] args) {
        String firstName="Li",LastName="Kelly";
        Person person  = new Person(firstName, LastName);
        Person person2  = new Person("Mu", "lei");
        System.out.println("序列化前person："+person.toString());
        System.out.println("序列化前person2："+person2.toString());
        ObjectOutputStream outStream;
        ObjectInputStream inStream;
        ObjectOutputStream outStream2 ;
        ObjectInputStream inStream2;
        String filePath = "src/new_person/2.txt";
        String file = "src/new_person/1.txt";
        try {
            //创建一个ObjectOutputStream输出流
            outStream = new ObjectOutputStream(new FileOutputStream(filePath));
            outStream2 = new ObjectOutputStream(new FileOutputStream(filePath));
            //将对象序列化到文件filePath
            outStream.writeObject(person);
            outStream2.writeObject(person2);

            inStream = new ObjectInputStream(new FileInputStream(filePath));
            inStream2 = new ObjectInputStream(new FileInputStream(filePath));

            Person readObject = (Person)inStream.readObject();
            Person readObject2 = (Person)inStream2.readObject();
            System.out.println("反序列化后person："+readObject.toString());
            System.out.println("反序列化后person2："+readObject2.toString());
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
