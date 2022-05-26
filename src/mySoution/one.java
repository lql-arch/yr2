package mySoution;

import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Comparator;

public class one {
    public static void main(String[] args){
        String[] ArrayList;
        ArrayList = reorderLogFiles(new String[]{"dig1 8 1 5 1", "let1 art can", "dig2 3 6", "let2 own kit dig", "let3 art zero"});
        for (String e:ArrayList) {
            System.out.println(e);
        }
    }


//    public static String[] reorderLogFiles(String[] logs) {
//        ArrayList<String> nums = new ArrayList<>();
//        ArrayList<String> cases = new ArrayList<>();
//        for(String e:logs){
//            ArrayList<String> list = new ArrayList<>(Arrays.asList(e.split(" ")));
//            char ch = list.get(1).charAt(0);
//            if(Character.isDigit(ch))
//            {
//                nums.add(e);
//            }else{
//                cases.add(e);
//            }
//        }
//
//        int min;
//        ArrayList<String> ans = new ArrayList<>();
//        while(!cases.isEmpty()) {
//            min = 0;
//            for (int i = 1; i < cases.size(); i++) {
//                int t1 = cases.get(i).indexOf(' ');
//                int t2 = cases.get(min).indexOf(' ');
//
//                if (cases.get(i).substring(t1+1).compareTo(cases.get(min).substring(t2+1)) < 0) {
//                    min = i;
//                } else if (cases.get(i).substring(t1+1).compareTo(cases.get(min).substring(t2+1)) == 0) {
//                    if (cases.get(i).substring(0, t1).compareTo(cases.get(min).substring(0, t2)) < 0) {
//                        min = i;
//                    }
//                }
//            }
//            ans.add(cases.get(min));
//            cases.remove(min);
//        }
//
//        ans.addAll(nums);
//
//        String[] array =new String[ans.size()];
//        ans.toArray(array);
//        //String[] a = String.join(",",(String[])ans.toArray(a));
//        return array;
//    }

//    public static String[] reorderLogFiles(String[] logs) {
//        Arrays.sort(logs, one::compare);
//        //Arrays.sort(logs, (o1, o2)->compare(o1, o2));
////        Arrays.sort(logs, (o1, o2)-> {
////            return compare(o1, o2);
////        });
//
//        return logs;
//    }
//
//    private static int compare(String log1, String log2){
//        int s1 = log1.indexOf(' ') + 1;
//        int s2 = log2.indexOf(' ') + 1;
//        if(Character.isDigit(log1.charAt(s1)) && Character.isDigit(log2.charAt(s2))){
//            return 0;
//        }else if(Character.isDigit(log1.charAt(s1))){
//            return 1;
//        }else if(Character.isDigit(log2.charAt(s2))){
//            return -1;
//        }else{
//            int cmp = log1.substring(s1).compareTo(log2.substring(s2));
//            if(cmp == 0) return log1.compareTo(log2);
//            else return cmp;
//        }
//    }

    public static String[] reorderLogFiles(String[] logs) {
        strCompare cmp = new strCompare();
        Arrays.sort(logs,cmp);

        return logs;
    }

}

class strCompare implements Comparator<String> {

    @java.lang.Override
    public int compare(String log1, String log2) {
        int s1 = log1.indexOf(' ') + 1;
        int s2 = log2.indexOf(' ') + 1;
        if(Character.isDigit(log1.charAt(s1)) && Character.isDigit(log2.charAt(s2))){
            return 0;
        }else if(Character.isDigit(log1.charAt(s1))){
            return 1;
        }else if(Character.isDigit(log2.charAt(s2))){
            return -1;
        }else{
            int cmp = log1.substring(s1).compareTo(log2.substring(s2));
            if(cmp == 0) return log1.compareTo(log2);
            else return cmp;
        }
    }
}