package mySoution;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class UniqueSubstringsinWraparoundString {
    public int findSubstringInWraproundString(String p) {
        if(p.length() <= 1){
            return 1;
        }

        int[] nums =new int[26];
        int maxL = 0;
        int count = 0;
        for (int i = 0; i < p.length(); i++) {
            if(i>0 && Case(p.charAt(i-1),p.charAt(i))){
                maxL++;
            }else{
                maxL = 1;
            }
            nums[p.charAt(i) - 'a'] = Math.max(nums[p.charAt(i) - 'a'], maxL);
        }

        for(int i = 0;i < 26;i++){
            count += nums[i];
        }
        return count;
    }

    public static boolean Case(char n,char m){
        if(n + 1 == m){
            return true;
        }else if( n == 'z' && m == 'a'){
            return true;
        }

        return false;
    }

}
