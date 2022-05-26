package mySoution;

import java.util.Arrays;

public class ThreeSumClosest {
    public static int threeSumClosest(int[] nums, int target) {
        Arrays.sort(nums);
        int sum = nums[0] + nums[1] + nums[nums.length-1];
        int ans = 0;
        int left = 1,right = nums.length-1;
        for(int i = 0 ;i < nums.length - 2 ;i++){
            left = i+1 ;
            right =nums.length - 1;
            while(left < right){
                ans = nums[left] + nums[right] + nums[i];
                if(Math.abs(ans - target) <= Math.abs(sum - target)){
                    sum = ans;
                }
                if (ans > target) {
                    right--;
                } else if (ans < target) {
                    left++;
                } else {
                    return ans;
                }
            }
        }

        return sum;
    }

    public static void main(String[] args) {
        int num = threeSumClosest(new int[]{-55,-24,-18,-11,-7,-3,4,5,6,9,11,23,33},0);
        System.out.println(num);
    }
//    [-1,0,1,1,55] 3 ,{1,-3,3,5,4,1},1
}
