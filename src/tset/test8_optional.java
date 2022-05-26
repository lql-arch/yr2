package tset;

import mySoution.IsUnivalTree;

import java.util.Locale;
import java.util.Optional;
import java.util.function.Supplier;

public class test8_optional {

//    static {
//        Integer i = 5;
//        Integer getNum = Optional.ofNullable(1).orElse(i = null);
//        System.out.println(getNum);
//        System.out.println(i);
//    }


//    static {
//        Optional<String> stringOptional = Optional.of("张三");
//        System.out.println(stringOptional.orElseThrow());
//        //System.out.println(stringOptional.orElseThrow(CustomException::new));
//
//        Optional<String> emptyOptional = Optional.empty();
//        System.out.println(emptyOptional.orElseThrow());
////        String t = "自定义异常2";
////        System.out.println(emptyOptional.orElseThrow(()->new CustomException(t)));


////        Wo wo = CustomException::new;
////        CustomException tmp = wo.creat(t);
////        System.out.println(tmp.getMessage());
////        System.out.println(emptyOptional.orElseThrow(tmp));

//        }

    interface Wo{
        CustomException creat(String name);
    }
    private static class CustomException extends RuntimeException {
        private static final long serialVersionUID = -4399699891687593264L;

        public CustomException() {
            super("自定义异常");
        }

        public CustomException(String message) {
            super(message);
        }

    }

    public static void main(String[] args) {
//        Optional<Integer> opTest = Optional.of(1);
//        //opTest = Optional.ofNullable(null);
//        System.out.println(opTest.get());
//
//        //System.out.println(opTest.orElse(0));

        //OrElseThrow();

        //OrElseGet();

        //Filter();

        //Map();

        //FlatMap();

        //IfPresent();

//        Optional<String> str = Optional.of("we");
//        String string = str.orElse("no");
//        System.out.println(string);
        //Or();

    }
    public static void Or(){
        Optional<String> str = Optional.of("Wd");
        Optional<String> st = Optional.ofNullable("Sa");
        System.out.println(st.or(()->str));
    }

    public static void OrElseThrow() {
        // 有钱就没异常
        try {
            System.out.println(Optional.ofNullable("钱").orElseThrow(() -> new Exception()));  // 有钱不会抛异常
        } catch (Throwable throwable) {
            throwable.printStackTrace();
        }

        // 没钱就会抛异常
        try {
            System.out.println(Optional.ofNullable(null).orElseThrow(() -> new Exception()));  // 没钱抛异常
        } catch (Throwable throwable) {
            String t = "没钱";
            throwable.printStackTrace();
            //System.out.println(throwable.getMessage());
        }
    }

    public static void OrElseGet(){
        // orElseGet 它可以传入一个supplier接口，里面可以花样实现逻辑
        System.out.println(Optional.ofNullable("宝马").orElseGet(()->"走路"));  // 有宝马就不用走路
        System.out.println(Optional.ofNullable(null).orElseGet(()->"自行车"));  // 没宝马，可以骑自行车
        System.out.println(Optional.ofNullable(null).orElseGet(()->"电动车"));  // 没宝马，也可以骑电动车

    }

    public static void Filter(){
        String t1 = Optional.of("zhang shan").filter(e->e.length() > 5).orElse("wang wu");
        System.out.println(t1);
        Optional<String> t2 = Optional.empty();
        System.out.println(t2.filter(e->e.length() > 5).orElse("wang wu"));

    }

    public static void Map(){
        //如果创建的Optional中的值存在，对该值执行提供的Function函数调用
        Optional<String> st = Optional.of("zhang san");
        System.out.println(st.map(e->e.toUpperCase(Locale.CHINA)).orElse("faile"));
        //Locale 针对区域的转换规则
        //Root是两个空字符串初始化的对象，表示所有语言环境的基本语言环境，并且用于语言/国家无关的区域设置，用于区域设置敏感的操作。

        st = Optional.ofNullable("wang wu");
        System.out.println(st.map(e -> e.toUpperCase(Locale.getDefault())).orElse("faile"));
    }

    public static void FlatMap(){
        //map方法中的lambda表达式返回值可以是任意类型，在map函数返回之前会包装为Optional。
        //但flatMap方法中的lambda表达式返回值必须是Optional实例
        Optional<String> stringOptional = Optional.of("zhang san");
        System.out.println(stringOptional.flatMap(e -> Optional.of("lisi".toUpperCase())).orElseGet(()->"失败"));

        stringOptional = Optional.empty();
        System.out.println(stringOptional.flatMap(e -> Optional.empty()).orElse("失败"));
    }

    public static void IfPresent(){
        //ifPresent方法的参数是一个Consumer的实现类，Consumer类包含一个抽象方法，该抽象方法对传入的值进行处理，只处理没有返回值。
        Optional<String> str = Optional.ofNullable(null);//("zhangsan");
        str.ifPresentOrElse(e-> System.out.println("我被处理了..."+e), () -> {System.err.println("user 对象为null");});
        //System.out.println(str.isPresent());
    }
}