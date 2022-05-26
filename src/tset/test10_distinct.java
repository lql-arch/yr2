package tset;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Stream;

public class test10_distinct {

    public static void main(String[] args) {
//        List<test10_Book> list = new ArrayList<>();
//        {
//            list.add(new test10_Book("Core Java", 200));
//            list.add(new test10_Book("Core Java", 200));
//            list.add(new test10_Book("Learning Freemarker", 150));
//            list.add(new test10_Book("Spring MVC", 300));
//            list.add(new test10_Book("Spring MVC", 300));
//        }
//        long l = list.stream().distinct().count();
//        System.out.println("No. of distinct books:"+l);
//        //list.stream().distinct().forEach(b -> System.out.println(b.getName()+ "," + b.getPrice()));
//        list.stream().filter(distinctByKey(e->e.getName())).forEach((e)->System.out.println(e.getName()+" "+e.getPrice()));
    }

    static <T> Predicate<T> distinctByKey(Function<? super T, ?> keyExtractor) {
        Map<Object,Boolean> seen = new ConcurrentHashMap<>();
        return t -> seen.putIfAbsent(keyExtractor.apply(t), Boolean.TRUE) == null;
    }



    static{
        List<book> list = new ArrayList<>();
        {
            list.add(new book("Core Java", 200));
            list.add(new book("Core Java", 200));
            list.add(new book("Learning Freemarker", 150));
            list.add(new book("Spring MVC", 300));
            list.add(new book("Spring MVC", 300));
        }
        //Stream<book> str = Stream.of(new book("123",12));
        list.stream().filter(book.distinct(book::getName)).forEach((e)->System.out.println(e.getName()));
    }
}
class book{
    private String name;
    private int num;

    book(String name,int num){
        this.name = name;
        this.num = num;
    }

    public String getName(){
        return this.name;
    }

    public static <T>  Predicate<T> distinct(Function<? super T, ?> t){
        Map<Object,Boolean> map = new ConcurrentHashMap<>();
        return e -> Boolean.TRUE.equals(map.putIfAbsent(t.apply(e), true));
    }
}