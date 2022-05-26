package mySoution;

import static java.lang.Math.abs;

public class onceChange {
        public static boolean oneEditAway(String first, String second) {
            if(abs(first.length() - second.length()) >= 2){
                return  false;
            }
            int right = 0,left = 0;
            int count = 0;
            if(first.length() == second.length() ){
                while(right < first.length()){
                    if(first.charAt(right) != second.charAt(right)){
                        count++;
                    }
                    right++;
                }
            }else{
                int len1 = first.length();
                int len2 = second.length();
                while(left < first.length() && right < second.length()){
                    if(first.charAt(left) != second.charAt(right)){
                        count++;
                        if(len2 > len1){
                            right++;
                            len2--;
                            if(first.charAt(left) != second.charAt(right))
                                count++;
                        }else if(len2 < len1){
                            left++;
                            len1--;
                            if(first.charAt(left) != second.charAt(right))
                                count++;
                        }
                    }
                    right++;
                    left++;
                }
            }
            return count < 2;
        }

    public static void main(String[] args) {
        System.out.println(oneEditAway("t","bl"));
    }
}
