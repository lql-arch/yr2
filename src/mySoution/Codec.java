package mySoution;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

//class TreeNode {
//     int val;
//     TreeNode left;
//     TreeNode right;
//     TreeNode(int x) { val = x; }
//}

//public class Codec {
    // Encodes a tree to a single string.
//    public static String serialize(TreeNode root) {
//        if(root==null){return "#";}
//        Queue<TreeNode> q=new LinkedList<>();
//        q.add(root);
//        StringBuilder ans=new StringBuilder();
//        while(q.size()>0){
//            TreeNode t=q.poll();
//            ans.append("#");
//            if(t!=null){
//                ans.append(t.val);
//                q.add(t.left);
//                q.add(t.right);
//            }
//        }
//        return ans.toString();
//    }
//
//    // Decodes your encoded data to tree.
//    public static TreeNode deserialize(String data) {
//        if(data.equals("#")){return null;}
//        String[] s =data.split("#",-1);
//        TreeNode ans=new TreeNode(Integer.parseInt(s[1]));
//        Queue<TreeNode> q=new LinkedList<>();
//        q.add(ans);
//        for(int i=3;i<s.length;i+=2){
//            TreeNode t=q.poll();
//            if(s[i-1].length()>0){
//                t.left=new TreeNode(Integer.parseInt(s[i-1]));
//                q.add(t.left);
//            }
//            if(s[i].length()>0){
//                t.right=new TreeNode(Integer.parseInt(s[i]));
//                q.add(t.right);
//            }
//        }
//        return ans;
//    }


//    static String str = "";
//    // Encodes a tree to a single string.
//    public static String serialize(TreeNode root) {
//        if(root == null){
//            return str;
//        }
//        Queue<TreeNode> q = new LinkedList<>();
//        q.add(root);
//        while(q.size() > 0){
//            TreeNode t = q.poll();
//            str += t.val + "#";
//            if(t.left != null)
//                q.add(t.left);
//            if(t.right != null)
//                q.add(t.right);
//        }
//
//        return str;
//    }
//
//    // Decodes your encoded data to tree.
//    public static TreeNode deserialize(String data) {
//        if(data.equals("")){
//            return null;
//        }
//        String[] s = data.split("#",0);
//        TreeNode nums = new TreeNode(Integer.parseInt(s[0]));
//        Queue<TreeNode> q = new LinkedList<>();
//        q.add(nums);
//        for(int i = 1;i < s.length  ;i += 2) {
//            TreeNode t = q.poll();
//            t.left = new TreeNode(Integer.parseInt(s[i]));
//            q.add(t.left);
//            if(i + 1 < s.length) {
//                t.right = new TreeNode(Integer.parseInt(s[i + 1]));
//                q.add(t.right);
//            }
//        }
//
//
//        return nums;
//    }
//
//    public static TreeNode creat(int[] nums){
//        TreeNode num = new TreeNode(nums[0]);
//        Queue<TreeNode> q = new LinkedList<>();
//        q.add(num);
//        for(int i=1;i < nums.length ;i += 2){
//            TreeNode t=q.poll();
//            t.left=new TreeNode(nums[i]);
//            q.add(t.left);
//            if(i + 1 < nums.length) {
//                t.right = new TreeNode(nums[i + 1]);
//                q.add(t.right);
//            }
//        }
//
//        return num;
//    }
//
//    public static void Print(TreeNode tree){
//        Queue<TreeNode> q = new LinkedList<>();
//        q.add(tree);
//        while(q.size() > 0){
//            TreeNode t = q.poll();
//            System.out.print(t.val+" ");
//            if(t.left != null)
//                q.add(t.left);
//            if(t.right != null)
//                q.add(t.right);
//        }
//        System.out.println();
//    }
//
//    public static void main(String[] args) {
//        TreeNode tree = creat(new int[]{2,1,5,6});
//        String r = serialize(tree);
//        TreeNode ans = deserialize(r);
//
//        Print(tree);
//
//        System.out.println(str);
//
//        Print(ans);
//
//    }
//
//
//}


//public class Codec {
//
//    // Encodes a tree to a single string.
//    public String serialize(TreeNode root) {
//        if(root==null){return "#";}
//        Queue<TreeNode> q=new LinkedList<>();
//        q.add(root);
//        StringBuilder ans=new StringBuilder();
//        while(q.size()>0){
//            TreeNode t=q.poll();
//            ans.append("#");
//            if(t!=null){
//                ans.append(t.val);
//                q.add(t.left);
//                q.add(t.right);
//            }
//        }
//        return ans.toString();
//    }
//
//    // Decodes your encoded data to tree.
//    public TreeNode deserialize(String data) {
//        if(data.equals("#")){return null;}
//        String s[]=data.split("#",-1);
//        TreeNode ans=new TreeNode(Integer.parseInt(s[1]));
//        Queue<TreeNode> q=new LinkedList<>();
//        q.add(ans);
//        for(int i=3;i<s.length;i+=2){
//            TreeNode t=q.poll();
//            if(s[i-1].length()>0){
//                t.left=new TreeNode(Integer.parseInt(s[i-1]));
//                q.add(t.left);
//            }
//            if(s[i].length()>0){
//                t.right=new TreeNode(Integer.parseInt(s[i]));
//                q.add(t.right);
//            }
//        }
//        return ans;
//    }
//}
