package one_way;


import java.util.*;

//泛型
public class its_T {

    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        String[] arr = {"ASD","asd","aszx","sad"};
        List<String> t = Generic.listAdd1(arr,list);
        for (String i:t) {
            System.out.print(i+"  ");
        }
    }
}

class Generic<T>{
    public List<T> listAdd(T  [] arr, List<T> list){
        for(T t:arr){
            list.add(t);
        }

        return list;
    }

    //非泛型类中的泛型方法
    public static <T> List<T> listAdd1(T[] arr, List<T> list) {
        list.addAll(Arrays.asList(arr));
        return list;
    }

    //非泛型类中的普通方法
    public static  List<String> listAdd2(String [] arr, List<String> list) {
        for (String t : arr) {
            list.add(t);
        }
        return list;
    }
}

