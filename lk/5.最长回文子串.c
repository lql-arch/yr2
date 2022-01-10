//   Dynamic programming,violent soulutions
// char * longestPalindrome(char * s){
//     int len=strlen(s);
//     int start=0;
//     int longth=1;
//     if (len<2){
//         return s;
//     }

//     int nums[len][len];//nums represents the position relationship from len to len.
//     memset(nums,0,len*sizeof(int));
//     for(int i=0;i<len;i++){
//         nums[i][i]=1;
//     }

//     for (int L=2;L<=len;L++)//L is the length of each string.
//     {
//         for (int i=0;i<len;i++){//i is the left boundary.
//             //j is the right boundary.
//             int j=L-1+i;

//             if (j>=len)
//             {
//                 break;
//             }
//             if (s[i]!=s[j])
//             {
//                 nums[i][j]=0;
//             }else
//             {
//                 if (L<3)
//                 {
//                     nums[i][j]=1;
//                 }else
//                 {
//                     nums[i][j]=nums[i+1][j-1];
//                 }
//             }

//             if (nums[i][j]==1&&L>longth){
//                 start=i;
//                 longth=L;
//             }
//         }
//     }
//     *(s+start+longth)='\0';
//     return (s+start);
// }


//        Center Diffusion Law
// char * longestPalindrome(char * s){
//     int len=strlen(s);
//     if (len<=1){
//         return s;
//     }
//     int start=0,end=0;
//     for (int i=0;i<len;i++){
//         int len1=testaroundchar(s,i,i);//check for odd numbers.
//         int len2=testaroundchar(s,i,i+1);//check for even numbers.
//         int L=len1>len2?len1:len2;//assign the long to the result.
        
//         if (L>end-start){
//             start=i-(L-1)/2;//reduces the range of movement by one.
//             end=i+L/2+1;
//         }
//     }
//     *(s+end)='\0';
//     return s+start;
// }

// int testaroundchar(char*s,int start,int end){
//     int len=strlen(s);
//     while(start>=0 && end<len && s[start]==s[end]){
//         start--;
//         end++;
//     }
//     return (end-1)-(start+1)+1;
// }

//       Manacher 算法
