package mySoution;

public class FindKthNumber {
    public int getCount(int n,int m,int mid){
        int min = Math.min(m,n);
        int max = Math.max(m,n);
        int sum = 0;
        for(int i = 1 ; i <= min;i++){
            if(i * max < mid)
                sum += max;
            else
                sum += mid / i;
        }

        return sum;
    }

    public int findKthNumber(int m, int n, int k) {
        int left = 1,right = m * n;
        while(right > left){
            int mid = left + (right - left)/2;
            int ans = getCount(n,m,mid);
            if(k <= ans){
                right = mid;
            }else{
                left = mid + 1;
            }
        }

        return right;
    }


}
