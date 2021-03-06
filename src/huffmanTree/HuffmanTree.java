package huffmanTree;

import java.util.*;
import java.io.*;

public class HuffmanTree {
    static HashMap<Byte, String> map = new HashMap<>();
    public static huffman create_HuffmanTree(PriorityQueue<huffman> ans) {
        huffman root = null;

        while(ans.size() > 1){
            root = create_line(ans.poll(), Objects.requireNonNull(ans.poll()));
            ans.add(root);
        }

//        Queue<huffman> q = new LinkedList<huffman>();
//        q.add(root);
//        while(!q.isEmpty()){
//            huffman t = q.poll();
//            if(t.getData()==null){
//                q.add(t.getTopLeft());
//                q.add(t.getTopRight());
//            }else{
//                System.out.print(t.getData()+" ");
//            }
//        }


        return root;
    }

    public static huffman create_line(huffman left, huffman right){
        huffman t = new huffman(null,left.getWeight()+right.getWeight());//父节点
        t.setHuffman(left,right);
        t.getTopLeft().setFather(t);
        t.getTopRight().setFather(t);
        return t;
    }

    public static PriorityQueue<huffman> rankCode(byte[] bytes){
        PriorityQueue<huffman> queue = new PriorityQueue<>();
        Map<Byte,Integer> code = new HashMap<>();

        for(byte b:bytes){
            code.merge(b, 1, Integer::sum);
        }
        Set<Byte> set = code.keySet();
        for (Byte data : set) {
            Integer wight= code.get(data);
            queue.add(new huffman(data, wight));
        }

        return queue;
    }

    public static File createFile(File file,boolean isZip) throws IOException {
        String s = file.getPath();
        File create_file;
        if(isZip)
            create_file = new File(s+".huf");
        else
            create_file = new File(s+".txt");
        File father = file.getParentFile();
        try {
            if (!father.exists()) {
                father.mkdirs();
            }
            if (!create_file.exists()) {
                create_file.createNewFile();
            }
        }catch (IOException ex){
            ex.printStackTrace();
        }

        return create_file;
    }

    public static void zipFile(String s) throws IOException {
        File file = new File(s);
        File zip_file = createFile(file,true);

        try(InputStream fis = new FileInputStream(file);
            OutputStream os = new FileOutputStream(zip_file);
            ObjectOutputStream oos = new ObjectOutputStream(os)
        ){
            byte[] bytes = new byte[(int)file.length()];
            fis.read(bytes);
            //System.out.println("处理前:");
            byte[] huffmanBytes = huffmanZip(bytes);
            oos.writeObject(huffmanBytes);
            oos.writeObject(map);
        }catch (Exception ex){
            ex.printStackTrace();
        }
    }

    public static void diszipFile(String s) throws IOException {
        File file = new File(s);
        File diszip_file = createFile(file,false);

        try(OutputStream os = new FileOutputStream(diszip_file);
            InputStream is = new FileInputStream(file);
            ObjectInputStream ois = new ObjectInputStream(is)

        ){
            byte[] huffmanBytes = (byte[])ois.readObject();
            Map<Byte,String> huffmanCodes = (Map)ois.readObject();
            byte[] bytes = disCode(huffmanCodes,huffmanBytes);
            System.out.println();
            os.write(bytes);
        }catch (IOException ex){
            ex.printStackTrace();
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public static byte[] disCode(Map<Byte,String> huffmanCodes,byte[] huffmanBytes){
        StringBuilder stb = new StringBuilder();
        List<Byte> list = new ArrayList<>();
        Map<String,Byte> huffMap = new HashMap<>();

        for(int i = 0; i < huffmanBytes.length; ++i) {
            byte t = huffmanBytes[i];
            String tmp =Integer.toBinaryString((t & 0xFF) + 0x100).substring(1);
            stb.append(tmp);
        }
        //System.out.println(stb);

        for(Map.Entry<Byte,String> t:huffmanCodes.entrySet()){
            huffMap.put(t.getValue(),t.getKey());
        }

        int count;
        for(int i = 0 ; i < stb.length(); i += count){
            count = 1;
            boolean flag = true;
            Byte b = null;

            while(flag && i+count <= stb.length()) {
                String k = stb.substring(i, i + count);
                b = huffMap.get(k);
                if (b == null) {
                    count++;
                } else {
                    flag = false;
                }
            }
            if(b != null)
                list.add(b);
        }

        byte[] nums = new byte[list.size()];

        for(int i = 0; i < nums.length;i++){
            nums[i] = (byte) list.get(i);
        }

        return nums;
    }


    public static byte[] huffmanZip(byte[] bytes){
        PriorityQueue<huffman> ans = rankCode(bytes);
        huffman huffmanRoot = create_HuffmanTree(ans);
        ready_getCode(huffmanRoot,"",new StringBuilder());
//        for (Map.Entry<Byte,String> t: map.entrySet()) {
//            System.out.print(t.getValue()+" ");
//        }
//        System.out.println();

        return second_zip(bytes,map);
    }

    public static void ready_getCode(huffman root,String t,StringBuilder sb){
        StringBuilder sb2 = new StringBuilder(sb);
        sb2.append(t);
        if (root != null) {
            if(root.getData() == null){
                start_getCode(root,"1", sb2);
            }else{
                map.put(root.getData(),sb2.toString());
            }
        }
    }

    public static void start_getCode(huffman root,String t,StringBuilder sb){
        StringBuilder sb2 = new StringBuilder(sb);
        sb2.append(t);
        if (root != null) {
            if(root.getData() == null){
                start_getCode(root.getTopLeft(),"0", sb2);
                start_getCode(root.getTopRight(),"1", sb2);
            }else{
                map.put(root.getData(),sb2.toString());
            }
        }
    }

    public static byte[] second_zip(byte[] bytes,HashMap<Byte,String> huffmanCodes){
        StringBuilder stringBuilder = new StringBuilder();
        int len;

        for(byte b:bytes){
            stringBuilder.append(huffmanCodes.get(b));
        }
        //System.out.println(stringBuilder);

        String str = stringBuilder.toString();

        if (str.length() % 8 == 0) {
            len = str.length() / 8;
        } else {
            len = str.length() / 8 + 1;
        }

        byte[] huffmanBytes = new byte[len];
        int index = 0;

        //System.out.println("_________");
        for(int i = 0; i < str.length(); i += 8) {
            String strByte;
            if (i + 8 > str.length()) {
                StringBuilder tmp = new StringBuilder(str.substring(i));
                for(int j = str.length() - i ;j < 8 ;j++){
                    tmp.append("0");
                }
                strByte = tmp.substring(0,8);
            } else {
                strByte = str.substring(i, i + 8);
            }

            huffmanBytes[index++] = (byte)Integer.parseInt(strByte, 2);
            //System.out.print(strByte);
        }

        return huffmanBytes;
    }
}
