package mySoution;

import java.util.Arrays;

public class MinStickers {
    int M = 1 << 20, INF = 50;
    int[] f = new int[M];
    String[] ss;
    String t;
    int dfs(int state) {
        int n = t.length();
        if (state == ((1 << n) - 1))
            return 0;
        if (f[state] != -1)
            return f[state];
        int ans = INF;
        for (String s : ss) {
            int nstate = state;
            out:for (char c : s.toCharArray()) {
                for (int i = 0; i < n; i++) {
                    if (t.charAt(i) == c && ((nstate >> i) & 1) == 0) {
                        nstate |= (1 << i);
                        continue out;
                    }
                }
            }
            if (nstate != state) ans = Math.min(ans, dfs(nstate) + 1);
        }
        return f[state] = ans;
    }
    public int minStickers(String[] stickers, String target) {
        ss = stickers;
        t = target;
        Arrays.fill(f, -1);
        int ans = dfs(0);
        return ans == INF ? -1 : ans;
    }
}
