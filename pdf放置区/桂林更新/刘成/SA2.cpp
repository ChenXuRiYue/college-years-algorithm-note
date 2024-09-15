string s, t;
int n, k;
ll ans  = 0;
ll pres[N], pret[N];
int ls[N], rs[N], stk[N];
int lens;
int que(ll* pre, int L, int R) {
    if (L > R)return 0;
    if (L == 0)return pre[R];
    return pre[R] - pre[L - 1];
}
void dfs(int u, int L, int R) {  
    ll Lnum = que(pres, L - 1, u - 1 );
    ll Rnum = que(pret, u , R );
    ans += Lnum * Rnum * max(0, height[u] - k);
    Lnum = que(pret, L - 1, u - 1);
    Rnum = que(pres, u , R);
    ans += Lnum * Rnum * max(0, height[u] - k);
    if (ls[u])dfs(ls[u], L, u - 1);
    if (rs[u])dfs(rs[u], u + 1, R);
}
void slove() {
    while (cin >> k) {
        if (k == 0)break;
        cin >> s >> t;
        k--;
        SA(s + "$" + t);
        n = s.length() + t.length() + 1;
        lens = s.length();
        for (int i = 1; i <= n; i++) {
            if (sa[i] <= lens)
                pres[i] = pres[i - 1] + 1, pret[i] = pret[i - 1];
            else
                pres[i] = pres[i - 1], pret[i] = pret[i - 1] + 1;
        }
        int top = 0;
        for (int i = 1; i <= n; i++)stk[i] = 0, ls[i] = 0, rs[i] = 0;
        for (int i = 1; i <= n; i++) {
            int k = top;
            while (k && height[i] <= height[stk[k]])k--;
            if (k)rs[stk[k]] = i;
            if (k < top)ls[i] = stk[k + 1];
            stk[++k] = i; top = k;
        }
        ans = 0;
        dfs(stk[1], 1, n);
        cout << ans << endl;
    }  
}
