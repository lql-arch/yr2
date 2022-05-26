package one_way;

public class test2 {
    public static void main(String[] args) {
        byte tByte = 2;
        String tString = Integer.toBinaryString((tByte & 0xFF) + 0x100).substring(1);

        System.out.println(tString);
        System.out.println(0x100 +" "+0xFF );
    }
}
