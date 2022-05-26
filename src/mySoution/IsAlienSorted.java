package mySoution;

import java.util.Comparator;

public class IsAlienSorted {
    public boolean compare(String s1,String s2,String order){
        int len = Math.min(s1.length(), s2.length());
        for(int i = 0 ;i < len ;i++){
            int i1 = order.indexOf(s1.charAt(i));
            int i2 = order.indexOf(s2.charAt(i));
            if(i1 == i2)
                continue;
            return i1 < i2;
        }

        return len == s1.length();
    }

    public boolean isAlienSorted(String[] words, String order) {
        if(words.length <= 1){
            return true;
        }

        boolean ans = true;
        for (int i = 0; i < words.length-1; i++) {
            ans = compare(words[i],words[i+1],order);
            if(!ans){
                return false;
            }
        }

        return ans;
    }
}
