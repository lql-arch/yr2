package mySoution;

import java.util.ArrayList;
import java.util.List;

public class LetterCombinations {
    String[] top = new String[]{"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    List<String> ans = new ArrayList<>();
    StringBuilder t = new StringBuilder();

    public  List<String> letterCombinations(String digits) {

        if(digits.length() == 0){
            return ans;
        }

        int[] nums = new int[digits.length()];

        for(int i = 0;i < digits.length();i++){
            nums[i] = digits.charAt(i) - '0';
        }

        backDigits(nums,0);

        return ans;
    }

    private  void backDigits(int[] nums,int size){
        if(size == nums.length){
            ans.add(String.valueOf(t));
            return ;
        }

        for(int i = 0; i < top[nums[size]].length() ; i++ ){
            t.append(top[nums[size]].charAt(i));
            backDigits(nums,size + 1);
            t.deleteCharAt(t.length() - 1);
        }
    }

//    public static void main() {
//        List<String> ans = letterCombinations("23");
//        System.out.println(ans);
//    }
}
