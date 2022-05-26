package mySoution;

public class MinDeletionSize {
        public static int minDeletionSize(String[] strs) {
            if(strs.length <= 1 ){
                return 0;
            }
            int count = 0;
            String[] t = new String[strs[0].length()];
            for(int i = 0; i < strs[0].length();i++){
                for(int j = 1; j < strs.length ;j++){
                    if(strs[j].charAt(i) < strs[j-1].charAt(i)){
                        count ++;
                        break;
                    }
                }
            }

                return count;
        }

    public static void main(String[] args) {
            int count = minDeletionSize(new String[]{"x","q"});
            System.out.println(count);
        //strs = ["cba","daf","ghi"] 1
        //strs = ["a","b"]
        //strs = ["zyx","wvu","tsr"] 3
    }

    public static class SubsetsWithDup {

    }
}
