package mySoution;

public class MergeSort {
    public static void main(String[] args) {
        int[] ans = {6, 8, 4, 4, 6, 36, 673, 13, 6, 7, 3, 4, 6, 8, 3, 7, 5, 7, 9, 5};
        System.out.print("原数组：");
        for (int i = 0; i < ans.length; i++) {
            System.out.print(ans[i]+",");
        }
        System.out.println();
        mergeSort(ans);
        System.out.print("归并排序之后的数组：");
        for (int i = 0; i < ans.length; i++) {
            System.out.print(ans[i]+",");
        }
    }

    //sort方法的驱动程序
    private static void mergeSort(int[] ans) {
        sort(ans, 0, ans.length - 1);
    }

    //将tmp和Cctr当做参数传入，方便调用merge方法时获得这两个参数
    private static void sort(int[] ans, int left, int right) {
        int mid = (left + right) / 2;
        //当分到只剩下一个元素的情况,则退出递归程序
        if (left >= right) {
            return;
        }
        sort(ans, left, mid);
        sort(ans, mid + 1, right);
        merge(ans, left, mid, right);
    }

    private static void merge(int[] ans, int left, int mid, int right) {
        //声明三个计时器
        int Actr = left;
        int Bctr = mid + 1;
        int Cctr = 0;
        int lenA = mid - left + 1;
        int lenB = right - mid;
        //创建临时数组,长度为A，B数组长度之和
        int[] tmp = new int[right - left + 1];
        //循环A，B中长度较短的长度次数的二倍的次数
        while (Actr <= mid && Bctr <= right) {
            if (ans[Actr] <= ans[Bctr]) {
                tmp[Cctr++] = ans[Actr];
                Actr++;
            } else {
                tmp[Cctr++] = ans[Bctr];
                Bctr++;
            }
        }
        //如果左边的还有剩余，将左边剩余的归并
        while (Actr <= mid){
            tmp[Cctr ++] = ans[Actr ++];
        }
        //如果右边的还有剩余，将右边剩余的归并
        while (Bctr <= right){
            tmp[Cctr ++] = ans[Bctr ++];
        }
        //将临时数组更新到原数组
        for (int i = 0; i < tmp.length; i++) {
            ans[left++] = tmp[i];
        }
    }
}
