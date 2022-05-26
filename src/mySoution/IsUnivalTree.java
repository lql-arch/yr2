package mySoution;

import com.sun.source.tree.Tree;

import java.util.LinkedList;
import java.util.Queue;

public class IsUnivalTree {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {}
        TreeNode(int val) { this.val = val; }
        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    public boolean isUnivalTree(TreeNode root) {
        Queue<TreeNode> ans = new LinkedList<>();
        ans.add(root);

        while(ans.size() > 0){
            TreeNode t = ans.poll();
            if(t.right != null && t.val == t.right.val ){
                ans.add(t.right);
            }else if(t.right == null){}
            else{
                return false;
            }
            if(t.left != null && t.val == t.left.val) {
                ans.add(t.left);
            }else if(t.left == null){}
            else{
                return false;
            }
        }

        return true;
    }

}
