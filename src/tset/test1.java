package tset;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class test1 {
    public static void main(String[] args) {
        List<String> str = new ArrayList<>();
        str.add("123");
        str.add("13");
        str.add("12");
        str.add("1");

        Iterator<String> iterator = str.iterator();
        while(iterator.hasNext()){
            System.out.println(iterator.next());
            //str.remove(2);
        }

        CopyOnWriteArrayList<String> s = new CopyOnWriteArrayList<>(str);
        System.out.println(s.get(1));
    }

}
