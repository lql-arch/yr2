package tset;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Function;
import java.util.function.Predicate;

public class test10_Book {
    private final String name;
    private final int price;
    public test10_Book(String name, int price) {
        this.name = name;
        this.price = price;
    }
    public String getName() {
        return name;
    }
    public int getPrice() {
        return price;
    }
    @Override
    public boolean equals(final Object obj) {
        if (obj == null) {
            return false;
        }
        if(!(obj instanceof test10_Book)){
            return false;
        }
        final test10_Book book = (test10_Book) obj;
        if (this == book) {
            return true;
        } else {
            return (this.name.equals(book.name) && this.price == book.price);
        }
    }

    @Override
    public int hashCode() {
        int hashno = 7;
        hashno = 13 * hashno + (name == null ? 0 : name.hashCode());
        return hashno;
    }

}
