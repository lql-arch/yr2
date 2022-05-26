import java.io.*;
import java.util.Scanner;

public class TestFile {
    public static File creatFile(String path) {
        File one = new File(path);
        if(!one.exists()){
            System.exit(-1);
        }

        System.out.println(one.getAbsoluteFile());

        return one;
    }

    public static void main(String[] args) throws FileNotFoundException {
      //creatFile("/home/bronya/vs/untitled/src/new_person/1.txt");
        File file = creatFile("1.txt");

        try(PrintWriter output = new PrintWriter(file);) {
            output.println("This is a test.\n" +
                    "This is second test.");
            //output.close();
        }

        try(Scanner input = new Scanner(file);){
            while(input.hasNext()) {
                String str = input.nextLine();
                System.out.println(str);
            }
            //input.close();
        }


    }

}

