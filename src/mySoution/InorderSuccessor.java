package mySoution;

import new_person.TestFile;

import java.util.LinkedList;
import java.util.Queue;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}


public class InorderSuccessor {
    public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
        Queue<TreeNode> q = new LinkedList<>();
        TreeNode prev = null;
        TreeNode first = root;

        while(first != null || !q.isEmpty()){
            while(first != null){
                q.add(first);
                first = first.left;
                System.out.println(q);
            }

            first = q.poll();

            if(prev == p){
                return first;
            }
            prev = first;
            first = first.right;

        }

        return null;
    }
}
