package tset;

import java.util.*;

//entryMap
public class test3 {
    public static void main(String[] args) {
        Map<String,Integer> map = new HashMap<>();
        map.merge("itisavalue",1, Integer::sum);
        map.merge("itisavalu",2, Integer::sum);
        for (Map.Entry<String,Integer> t: map.entrySet()) {
            System.out.println(t.getKey()+" "+t.getValue());
        }
        System.out.println();

        Set<String> set = map.keySet();
        for(String t:set){
            System.out.println(t+" "+map.get(t));
        }
        System.out.println();

        Iterator<Map.Entry<String,Integer>> it = map.entrySet().iterator();
        while(it.hasNext()){
            Map.Entry<String,Integer> entry = it.next();
            System.out.println(entry.getKey()+" "+entry.getValue());
        }
        System.out.println();

        Set<Map.Entry<String,Integer>> entrySet = map.entrySet();
        for (Map.Entry<String, Integer> entry:entrySet) {
            System.out.println(entry.getKey()+" "+entry.getValue());
        }
        System.out.println();

    }


}
