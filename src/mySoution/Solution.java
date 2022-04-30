package mySoution;
//import java.util.List;

//public class Solution {
//    public static void main(String[] args) {
//        int[] nums = {2, 1, 3, 3, 3, 4, 5};
//        Solu[] s = new Solu[10];
//        int len = s.length;
//        for(int i=0;i<10;i++)
//        {
//            s[i] = new Solu(nums);
//        }
//
//        for (Solu solu : s) {
//            System.out.println(solu.pick(3));
//        }
//    }
//}
//
//class Solu {
//
//    static int count = 0;
//    int[] obj = null ;
//    int num = 1;
//
//    public Solu(){
//        count++;
//    }
//
//    public Solu(int[] nums) {
//        obj = new int[nums.length];
//        System.arraycopy(nums,0,obj,0,nums.length);
//        java.util.Arrays.sort(obj);
//        count++;
//    }
//
//    public int pick(int target) {
//        int count = 0;
//        int mid = 0;
//        int left = 0, right = obj.length - 1;
//        int[] temp = new int[obj.length];
//
//        while (left <= right) {
//            mid = left + (right - left) / 2;
//            if (target == obj[mid]) {
//                temp[count++] = mid;
//                left = mid - 1;
//                right = mid + 1;
//                break;
//            } else if (target > obj[mid]) {
//                left = mid + 1;
//            } else {
//                right = mid - 1;
//            }
//        }
//        while (left >= 0 && obj[left] == target) {
//            temp[count++] = left;
//            left--;
//        }
//
//        while (right < obj.length && obj[right] == target) {
//            temp[count++] = right;
//            right++;
//        }
//        if(count != 0)
//            return temp[(int) (Math.random() * count)];
//        else
//            return 0;
//    }
//}


//import java.util.Date;
//
//public class Solution {
//    public static void main(String[] args){
//        long elapseTime = 0L;
//        Date time = new Date(elapseTime);
//        String s = time.toString();
//        System.out.println(s);
//        time.setTime(2000000000000L);
//        s = time.toString();
//        System.out.println(s);
//    }
//}


//import java.security.SecureRandom;

//public class Solution {
//    public static void main(String[] args){
//        SecureRandom rom = new SecureRandom();
//        System.out.println(rom.nextInt(100));
//    }
//}


//public class Solution {
//    public static void main(String[] args){
//
//    }
//}
//
//class Solution1 {
//    public int threeSumClosest(int[] nums, int target) {
//
//    }
//}


//public class Solution {
//    public static void main(String[] args){
//        person he = new person("Tom",13);
//        person she = new person();
//        System.out.println(he.getName()+" "+he.getAge());
//        System.out.println(she.getName()+" "+she.getAge());
//    }
//}
//
//class person{
//    private String name;
//    private int age;
//
//    person(){
//        this("bronya",16);
//    }
//
//    person(String name ,int age){
//        this.name = name;
//        this.age = age;
//    }
//
//    public String getName(){
//        return this.name;
//    }
//
//    public int getAge(){
//        return this.age;
//    }
//
//}


