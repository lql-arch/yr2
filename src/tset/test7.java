package tset;

import com.sun.jdi.ObjectCollectedException;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class test7 {
    public static void s(String[] args) {
        List<Integer> nums = new ArrayList<>();
        nums = Arrays.asList(1,2,3,4,5,6,7);
//        nums = Arrays.stream(new int[]{0,1,3,2}).boxed().collect(Collectors.toList());
//        nums.remove(nums.get(2));
        System.out.println(nums);
//        nums.remove(2);
//        System.out.println(nums);
    }

    public static void lenStream() {
        List<String> list = Arrays.asList("scala","java", "python", "shell", "ruby");
        long num = list.parallelStream().filter(x -> x.length() < 5).count();
        List<String> ls = list.parallelStream().filter(x->x.length() < 5).collect(Collectors.toUnmodifiableList());
        System.out.println(num);
        System.out.println(ls);
    }

    public static void sortStream() {
        Stream<Integer> sortedStream = Stream.of(1,3,7,4,5,8,6,2).sorted();
        sortedStream.collect(Collectors.toList()).forEach(x -> System.out.print(x + " "));
        System.out.println();

        Stream<Integer> sortedReverseStream = Stream.of(1,3,7,4,5,8,6,2).sorted(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1 - o2;
            }
        });
        Stream<Integer> sortedReverseStreamV2 = Stream.of(1,3,7,4,5,8,6,2).sorted((Integer o1, Integer o2) -> o2 - o1);
        sortedReverseStreamV2.collect(Collectors.toList()).forEach(x -> System.out.print(x + " "));
    }

    public static void reductionStream() {
        Stream<String> wordList = Stream.of("bj","tj","sh","yy","yq").distinct();
        Optional<String> firstWord = wordList.filter(word -> word.startsWith("a")).findFirst();
        System.out.println(firstWord.orElse("no"));
    }

    public static void reduceTest() {
        Stream<Integer> list = Stream.of(1,2,3,4,5);
        Optional<Integer> result = list.reduce((x, y) -> x + y);//sum
        System.out.println(result);
        System.out.println(list);
    }

    public static void collectTest() {
        List<String> list = Stream.of("hello", "world", "hello", "java").collect(Collectors.toList());
        list.forEach(x -> System.out.print(x + " "));
        System.out.println();
        Set<String> set = Stream.of("hello", "world", "hello", "java").collect(Collectors.toSet());
        set.forEach(x -> System.out.print(x + " "));
        System.out.println();
        Set<String> treeSet = Stream.of("hello", "world", "hello", "java").collect(Collectors.toCollection(TreeSet::new));
        treeSet.forEach(x -> System.out.print(x + " "));
        System.out.println();
        String resultStr = String.join(",", "hello", "world", "hello", "java");
        //String resultStr = Stream.of("hello", "world", "hello", "java").collect(Collectors.joining(","));
        System.out.println(resultStr);
    }

    public static void distinct(){
        List<String> list = Arrays.asList("AA", "BB", "CC", "BB", "CC", "AA", "AA");
        long l = list.stream().distinct().count();
        System.out.println("No. of distinct elements:"+l);
        //String output = list.stream().distinct().collect(Collectors.joining(","));
        List<String> output = list.stream().distinct().collect(Collectors.toList());
        System.out.println(output);

    }


    public static void main(String[] args) {

        //lenStream();
        //sortStream();
        //reductionStream();
        //reductionStream();
        //collectTest();


    }
}


