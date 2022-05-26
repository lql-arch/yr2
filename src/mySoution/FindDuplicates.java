package mySoution;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class FindDuplicates {
    public static List<Integer> findDuplicates(int[] nums) {
        List<Integer> ans = new ArrayList<>();
        for(int i = 0;i < nums.length;i++){
            int t = Math.abs(nums[i]) -1;
            if(nums[t]<0){
                ans.add(Math.abs(nums[i]));
            }
            else{
                nums[t] = -nums[t];
            }
        }
        for (int i:nums) {
            System.out.print(i+" ");
        }
        System.out.println();

        return ans;
    }

    public static void main(String[] args) {
        int[] nums = {4,3,2,7,8,2,3,1};
        List<Integer> ans =findDuplicates(nums);
        System.out.println(ans);
    }

//    public List<Integer> findDuplicates(int[] nums) {
//        List<Integer> rs = new ArrayList<>();
//        for(int i=0;i<nums.length;i++) {
//            if(nums[Math.abs(nums[i])-1]<0) {
//                rs.add(Math.abs(nums[i]));
//            }else {
//                nums[Math.abs(nums[i])-1]*=-1;
//            }
//        }
//
//        return rs;
//    }
}
