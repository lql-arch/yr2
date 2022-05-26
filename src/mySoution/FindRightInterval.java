package mySoution;

public class FindRightInterval {
    public int[] findRightInterval(int[][] intervals) {
        int len = intervals.length;
        int[] nums = new int[len];
        for(int i = 0;i < len;i++){
            nums[i] = -1;
        }
        for(int i = 0; i < len;i++){
            for(int j = 0;j < len;j++){
                if(intervals[i][1] <= intervals[j][0]){
                    if(nums[i] == -1)
                        nums[i] = j;
                    else
                        if(intervals[j][0] < intervals[nums[i]][0])
                            nums[i] = j;
                }
            }
        }

        return nums;
    }
}
