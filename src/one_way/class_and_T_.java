package one_way;

//import static java.awt.color.ICC_Profile.getData;

//Class<T>和Class<?>
class Box<T> {
    private T t;

    public Box() {}

    public Box(T data) {
        this.t = data;
    }

    public T getT() {
        return t;
    }

    public void setT(T t) {
        this.t = t;
    }

}


class class_and_T_ {


    @SpringBootApplication
    public static <SpringApplication> void main(String[] args) throws Exception{

        //SpringApplication app = new SpringApplication(class_and_T_.class);
        //SpringApplication.run(class_and_T_.class, args);
        //app.run(args);
        Box<String> s=new Box<String>("abc");
        Box<Integer> i=new Box<Integer>(123);
        System.out.println("s class:" + s.getClass());
        System.out.println("i class:" + i.getClass());
        System.out.println(s.getClass() == i.getClass());
        getData(s);
        getData(i);
        getData1(s);
        getData1(i);
    }

    public static Box<?> getData(Box<?> data){
        //System.out.println("data :" + data.getT());
        return data;
    }

    public static  <T> Box<T> getData1(Box<T> data){
        //System.out.println("data :" + data.getT());
        return data;
    }
}


//<?>实际上和 泛型方法是等效的