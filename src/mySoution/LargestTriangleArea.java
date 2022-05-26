package mySoution;
//S=(x1y2-x1y3+x2y3-x2y1+x3y1-x2y2)
//int t = points[i][0]*points[left][1]-points[i][0]*points[right][1]+points[left][0]*points[right][1]-points[left][0]*points[i][1]+points[right][0]*points[i][1]-points[left][0]*points[left][1];


public class LargestTriangleArea {
    public double largestTriangleArea(int[][] points) {
        double area = 0;
        for(int i = 0;i < points.length-2 ;i++){
            for(int j = i+1;j < points.length-1 ;j++){
                double x1 = points[j][0] - points[i][0];
                double y1 = points[j][1] - points[i][1];

                for(int k = j+1;k < points.length ;k++){
                    double x2 = points[k][0] - points[i][0];
                    double y2 = points[k][1] - points[i][1];

                    area = Math.max(area, Math.abs(x1 * y2 - x2 * y1)/2);
                }
            }
        }
        return area;
    }

    public static void main(String[] args) {
        LargestTriangleArea t = new LargestTriangleArea();
        double area = t.largestTriangleArea(new int[][]{{0,0},{0,1},{1,0},{0,2},{2,0}});
        //double area = t.largestTriangleArea(new int[][]{{1,0},{0,0},{0,1}});
        System.out.println(area);
    }
}
