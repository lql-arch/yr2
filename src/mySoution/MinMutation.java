package mySoution;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Queue;

public class MinMutation {
    //char[][] genetic = {{'T','C','G'},{'T','C','G'},{'A','C','G'},{'A','T','C'},{'A','T','G'}};

    public static int minMutation(String start, String end, String[] bank){
        if( start.equals(end)){
            return 0;
        }
        if(bank.length == 0 ){
            return -1;
        }

        int num;
        int count = 0;
        int len = start.length();
        Queue<String> q = new ArrayDeque<>();
        q.add(start);

        int[] flag = new int[bank.length];
        for (int i = 0; i < bank.length; i++) {
            flag[i] = 0;
        }

        while(!q.isEmpty()){
            int size = q.size();
            count++;
            for(int k = 0;k < size ;k++) {
                String t = q.poll();
                for (int i = 0; i < bank.length; i++) {
                    if(flag[i] == 0) {
                        num = 0;
                        for (int j = 0; j < len; j++) {
                            //assert t != null;
                            if (t.charAt(j) != bank[i].charAt(j)) {
                                num++;
                            }
                        }
                        if (num == 1) {
                            if (bank[i].equals(end)) {
                                return count;
                            }
                            flag[i] = 1;
                            q.add(bank[i]);
                        }
                    }
                }
            }
        }
        return -1;
    }

    public static void main(String[] args){
        int count = minMutation("AACCGGTT","AAACGGTA", new String[]{"AACCGGTA", "AACCGCTA", "AAACGGTA"});
        System.out.println(count);
    }
}