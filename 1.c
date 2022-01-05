double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    //合并奇偶数，若为奇数，left和right一样，若为偶数，mid=（left+right）/2
    //tmid从1开始
    int left=(nums1Size+nums2Size+1)/2;
    int right=(nums1Size+nums2Size+2)/2;
    return (erfen(nums1,0,nums1Size-1,nums2,0,nums2Size-1,left)+erfen(nums1,0,nums1Size-1,nums2,0,nums2Size-1,right))*0.5;
}

int erfen(int* nums1,int start1, int end1, int* nums2,int start2, int end2,int tmid){
    int len1=end1-start1+1;
    int len2=end2-start2+1;
    //将短的一个放在前面，减小代码复杂度(不乱（）)
    if (len1>len2) 
        return erfen(nums2,start2,end2,nums1,start1,end1,tmid);
    if (len1==0)
        return nums2[tmid+start2-1];
    if (tmid==1)
        return nums1[start1]<nums2[start2]?nums1[start1]:nums2[start2];
    
    int left=start1+(tmid/2<len1?tmid/2:len1)-1;
    int right=start2+(tmid/2<len2?tmid/2:len2)-1;

    if (nums1[left]>nums2[right])
        return erfen(nums1,start1,end1,nums2,right+1,end2,tmid-(right-start2+1));
    else 
        return erfen(nums1,left+1,end1,nums2,start2,end2,tmid-(left-start1+1));
}