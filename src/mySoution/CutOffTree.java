package mySoution;

import java.util.*;
import java.util.stream.Collectors;

public class CutOffTree {
    int[][] move ={{-1,0},{1,0},{0,1},{0,-1}};
    public int cutOffTree(List<List<Integer>> forest) {
        List<int[]> list=new ArrayList<>();
        list.add(new int[]{0,0,forest.get(0).get(0)});
        for(int i=0;i<forest.size();i++){
            for(int j=0;j<forest.get(i).size();j++){
                int a=forest.get(i).get(j);
                if(a>1){
                    list.add(new int[]{i,j,a});
                }
            }
        }
        Collections.sort(list,(a, b)->a[2]-b[2]);
        int ans=minSteps(new int[]{0,0},list.get(0),forest);
        if(ans==-1){return -1;}
        for(int i=1;i<list.size();i++){
            int d=minSteps(list.get(i-1),list.get(i),forest);
            if(d==-1){return -1;}
            ans+=d;
        }
        return ans;
    }
    public int minSteps(int[] a, int[] b, List<List<Integer>> forest){
        //BFS计算从a到b点需要的最短路程，假如无法到达，则返回-1；
        if(a[0]==b[0]&&a[1]==b[1]){return 0;}//0,0是否最小
        Queue<int[]> q=new LinkedList<>();
        boolean[][] cameBefore =new boolean[55][55];
        q.add(a);
        cameBefore[a[0]][a[1]]=true;
        int ans=0;
        while(q.size()>0){
            ans++;
            int size=q.size();
            for(int i=0;i<size;i++){
                int[] p =q.poll();
                for(int j=0;j<4;j++){
                    int x=p[0]+move[j][0],y=p[1]+move[j][1];
                    if(x>=0&&x<forest.size()&&y>=0&&y<forest.get(0).size()&&forest.get(x).get(y)!=0&&!cameBefore[x][y]){
                        if(x==b[0]&&y==b[1]){return ans;}
                        q.add(new int[]{x,y});
                        cameBefore[x][y]=true;
                    }
                }
            }
        }
        return -1;
    }
}


class CutTree{// 就最近的最小砍，遇树必砍(有死循环)
    int[][] step = new int[][]{{1,0},{0,1},{-1,0},{0,-1}};

    public int cutTree(List<List<Integer>> forest) {
        int needCut = 0;
        int[] ans = new int[]{0,-1};
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest.get(i).size(); j++) {
                if( forest.get(i).get(j) > 1){
                    needCut += forest.get(i).get(j) - 1;
                }
            }
        }

        dfs(forest,ans,needCut,0,0);

        //System.out.println(ans[0]+" "+needCut );

        if( needCut == ans[0])
            return ans[1];
        else
            return -1;
    }

    private void dfs(List<List<Integer>> forest,int[] ans,int needCut,int l,int r) {
//        if(forest.get(l).get(r).equals(0)){
//            return ;
//        }

        if(forest.get(l).get(r) > 1)
            ans[0] += forest.get(l).get(r) - 1;
        System.out.println(ans[0]+" "+forest.get(l).get(r)+" "+l+" "+r);
        System.out.println(forest);

        forest.get(l).set(r, -1);
        ans[1]++;

        int minL = l ,minR = r;
        for(int i = 0 ;i < step.length;i++){
            int tL = l + step[i][0];
            int tR = r + step[i][1];
            if(tL >= 0 && tR >= 0 && tL < forest.size() && tR < forest.get(0).size()){
                if(!(forest.get(tL).get(tR).equals(0))) {
                    if (minL == l && minR == r) {
                        minL = tL;
                        minR = tR;
                    }
                    if( (forest.get(minL).get(minR) == 1 || forest.get(minL).get(minR) == -1) && forest.get(tL).get(tR)!= -1){
                        minL = tL;
                        minR = tR;
                    }
                    if (forest.get(tL).get(tR) < forest.get(minL).get(minR) && forest.get(tL).get(tR) != 1 && forest.get(tL).get(tR) != -1) {
                        minL = tL;
                        minR = tR;
                    }
                }
            }
        }

        if(ans[0] == needCut)
            return ;

        if(minL == l && minR == r)
            return ;
        else
            dfs(forest,ans,needCut,minL,minR);

        //forest.get(l).set(r, 1);
    }

    public static void main(String[] args) {
        CutTree t = new CutTree();
        //int[][] tmp = new int[][]{{1,2,3},{0,0,4},{7,6,5}};
        int[][] tmp = new int[][]{{1,2,3},{0,0,0},{7,6,5}};
        //int[][] tmp = new int[][]{{2,3,4},{0,0,9},{8,7,6}};
        List<List<Integer>> nums = new ArrayList<>();
        for (int[] ints : tmp) {
            nums.add(Arrays.stream(ints).boxed().collect(Collectors.toList()));
        }

        int count = t.cutTree(nums);
        System.out.println(count);
    }
}