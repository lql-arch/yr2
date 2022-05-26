package mySoution;

import java.util.Arrays;
import java.util.List;

public class aslist {
    public static void main(String[] args){

        //1、对象类型(String型)的数组数组使用asList()，正常
        String[] strings = {"aa", "bb", "cc"};
        List<String> stringList = Arrays.asList(strings);
        System.out.print("1、String类型数组使用asList()，正常：  ");
        for(String str : stringList){
            System.out.print(str + " ");
        }
        System.out.println();


        //2、对象类型(Integer)的数组使用asList()，正常
        Integer[] integers = new Integer[] {1, 2, 3};
        List<Integer> integerList = Arrays.asList(integers);
        System.out.print("2、对象类型的数组使用asList()，正常：  ");
        for(int i : integerList){
            System.out.print(i + " ");
        }
//        for(Object o : integerList){
//            System.out.print(o + " ");
//        }
        System.out.println();


        //3、基本数据类型的数组使用asList()，出错
        int[] ints = new int[]{1, 2, 3};
        List intList = Arrays.asList(ints);
        System.out.print("3、基本数据类型的数组使用asList()，出错(输出的是一个引用，把ints当成一个元素了)：");
        for(Object o : intList){
            System.out.print(o.toString()+" ");
        }
        System.out.println();

        System.out.print("   " + "这样遍历才能正确输出：");
        int[] ints1 = (int[]) intList.get(0);
        for(int i : ints1){
            System.out.print(i + " ");
        }
        System.out.println();

        //4、当更新数组或者List,另一个将自动获得更新
        System.out.print("4、当更新数组或者List,另一个将自动获得更新：  ");
        integerList.set(0, 5);
        for(Object o : integerList){
            System.out.print(o + " ");
        }
        System.out.print("\t\t");
        for(Object o : integers){
            System.out.print (o + " ");
        }
        System.out.println();

        //5、add()   remove() 报错
        System.out.println("5、add()   remove() 报错：  ");
        integerList.remove(0);
        integerList.add(3, 4);
        integerList.clear();
    }

}
