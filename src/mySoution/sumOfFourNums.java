package mySoution;

import java.util.*;
import java.util.stream.Collectors;

public class sumOfFourNums {
    public static List<List<Integer>> subsetsWithDup(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        List<Integer> start = Arrays.stream(nums).boxed().collect(Collectors.toList());

        ans.add(new ArrayList<Integer>());
        start.sort(Integer::compareTo);

        int r = ans.size(),l = 0, len = 0;
        for(int i = 0; i < start.size();i++) {
            if( i != 0 && (Objects.equals(start.get(i), start.get(i - 1))))
                l = ans.size() - len;
            else
                l = 0;
            r = ans.size();
            len = r - l;
            for(int j = l;j < r;j++){
                System.out.println(r+" "+l);
                List<Integer> tmp = new ArrayList<>(ans.get(j));
                tmp.add(start.get(i));
                List<Integer> t = new ArrayList<>(tmp);
                ans.add(t);
                System.out.println(ans);
            }
        }

//        Set<List<Integer>> set = new HashSet<>(ans);
//        ans.clear();
//        ans.addAll(set);
//
//        System.out.println(ans);

        return ans;
    }

    public static void main(String[] args) {
         subsetsWithDup(new int[]{1,2,2});

    }
}
