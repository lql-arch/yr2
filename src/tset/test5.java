package tset;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;
import java.util.function.Supplier;

class Person {

    public enum Sex {
        MALE, FEMALE
    }

    String name;
    LocalDate birthday;
    Sex gender;
    String emailAddress;

    Person(String name){
        this.name = name;
    }

//    public int getAge() {
//        return age;
//    }

    public LocalDate getBirthday() {
        return birthday;
    }

    public static int compareByAge(Person a, Person b) {
        return a.birthday.compareTo(b.birthday);
    }
}


public class test5 {
    public static <T, SOURCE extends Collection<T>, DEST extends Collection<T>>
    DEST transferElements(SOURCE sourceCollection, Supplier<DEST> collectionFactory) {

        DEST result = collectionFactory.get();
        result.addAll(sourceCollection);
        return result;
    }

    public static void main(String[] args) {
        Collection<Person> roster = new ArrayList<>();
        roster.add(new Person("lei"));
        Set<Person> rosterSetLambda = transferElements(roster, () -> { return new HashSet<>(); });

        Set<Person> rosterSet = transferElements(roster, HashSet<Person>::new);
        //System.out.println(rosterSet+" "+rosterSetLambda);
        for (Person t:rosterSet) {
            System.out.println(t.name);
        }
        for (Person t:rosterSetLambda) {
            System.out.println(t.name);
        }
        for (Person t:roster) {
            System.out.println(t.name);
        }
    }
}
