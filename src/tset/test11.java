package tset;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

public class test11 {
    public static void main(String[] args) {
        List<Gen_Student> menu = Arrays.asList(
                new Gen_Student("刘一", 721, true, Gen_Student.GradeType.THREE),
                new Gen_Student("陈二", 637, true, Gen_Student.GradeType.THREE),
                new Gen_Student("张三", 666, true, Gen_Student.GradeType.THREE),
                new Gen_Student("李四", 531, true, Gen_Student.GradeType.TWO),
                new Gen_Student("王五", 483, false, Gen_Student.GradeType.THREE),
                new Gen_Student("赵六", 367, true, Gen_Student.GradeType.THREE),
                new Gen_Student("孙七", 499, false, Gen_Student.GradeType.ONE));

//        double aver = menu.stream().collect(Collectors.averagingDouble(Gen_Student::getTotalScore));
//        //Optional.ofNullable(aver).ifPresentOrElse(System.out::println,()->{System.out.println(0);});
//        System.out.println(Optional.of(aver).orElse(0.0));

        List<Gen_Student> sl = menu.stream().collect(Collectors.collectingAndThen(Collectors.toList(), Collections::unmodifiableList));
        for (Gen_Student i:sl) {
            System.out.println(i);
        };
    }
}


/**
 * 学生信息
 */
class Gen_Student {
    /** 姓名 */
    private String name;
    /** 总分 */
    private int totalScore;
    /** 是否本地人 */
    private boolean local;
    /** 年级 */
    private GradeType gradeType;

    /**
     * 年级类型
     */
    public enum GradeType {ONE,TWO,THREE}

    public Gen_Student(String name, int totalScore, boolean local, GradeType gradeType) {
        this.name = name;
        this.totalScore = totalScore;
        this.local = local;
        this.gradeType = gradeType;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", totalScore=" + totalScore +
                ", local=" + local +
                ", gradeType=" + gradeType +
                '}';
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getTotalScore() {
        return totalScore;
    }

    public void setTotalScore(int totalScore) {
        this.totalScore = totalScore;
    }

    public boolean isLocal() {
        return local;
    }

    public void setLocal(boolean local) {
        this.local = local;
    }

    public GradeType getGradeType() {
        return gradeType;
    }

    public void setGradeType(GradeType gradeType) {
        this.gradeType = gradeType;
    }
}
