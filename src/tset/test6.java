package tset;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class test6 {
    public static void main(String[] args) {
        int[] arr2 = {234, 2, 23, 777, 2};
        List<Integer> list2 = Arrays.stream(arr2).boxed().collect(Collectors.toList());
    }
}
