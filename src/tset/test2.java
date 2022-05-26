package tset;

import java.util.HashSet;
import java.util.Set;


//hashCode
public class test2 {
    private int i;

    public int getI() {
        return i;
    }

    public void setI(int i) {
        this.i = i;
    }

    public boolean equals(Object object) {
        if (object == null) {
            return false;
        }
        if (object == this) {
            return true;
        }
        if (!(object instanceof test2)) {
            return false;
        }

        test2 other = (test2) object;
        if (other.getI() == this.getI()) {
            return true;
        }
        return false;
    }

    public int hashCode() {
        return i % 10;
    }

    public final static void main(String[] args) {
        test2 a = new test2();
        test2 b = new test2();
        a.setI(1);
        b.setI(1);
        Set<test2> set = new HashSet<>();
        set.add(a);
        set.add(b);
        System.out.println(a.hashCode() == b.hashCode());
        System.out.println(a.equals(b));
        System.out.println(set);
    }
}
