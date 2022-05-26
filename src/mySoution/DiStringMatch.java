package mySoution;

public class DiStringMatch {
//    public static int[] diStringMatch(String s) {
//        int len = s.length();
//        int[] nums = new int[len+1];
//        int[] t = new int[2*len+1];
//        for (int i:t) {
//            i = 0;
//        }
//
//        for(int i = len-1;i >= 0 ;i--) {
//            if (i == len - 1) {
//                nums[len] = len;
//                t[len] = 1;
//            }
//
//            if (s.charAt(i) == 'I') {
//                for (int j = 1; ; j++) {
//                    if (t[nums[i + 1] - j] != 1) {
//                        nums[i] = nums[i + 1] - j;
//                        t[nums[i + 1] - j] = 1;
//                        break;
//                    }
//                }
//            }
//            else if (s.charAt(i) == 'D') {
//                for (int j = 1; ; j++) {
//                    if (t[nums[i + 1] + j] != 1) {
//                        nums[i] = nums[i + 1] + j;
//                        t[nums[i + 1] + j] = 1;
//                        break;
//                    }
//                }
//            }
//        }
//
//        int min = nums[0];
//        for(int i = 1;i<len+1;i++){
//            if( nums[i] < min){
//                min = nums[i];
//            }
//        }
//
//        for(int i = 0;i < len+1;i++) {
//            nums[i] -= min;
//        }
//
//        return nums;
//    }

    public static int[] diStringMatch(String s){
        int len = s.length();
        int[] nums = new int[len+1];
        int r = len,l = 0;
        int index = 0;
        while(index < len){
            nums[index] = s.charAt(index) == 'I' ? l++:r--;
            index++;
        }
        nums[index] = l;

        return nums;
    }

    public static void main(String[] args) {
        int[] nums = diStringMatch("IDID");
        System.out.println("result:");
        for (int i:nums) {
            System.out.print(i+" ");
        }

    }

}
