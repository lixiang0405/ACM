//给一个 n 个点 m 条边的有向无环图，问每个点可以到达多少个点（包括自己）。

bitset<N> f[N];
VI e[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    scanf("%d%d",&n,&m);
    rep(i,1,1+m){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].pb(v);
    }
    per(u,1,1+n){
        f[u][u]=1;
        for(auto v:e[u]) f[u]|=f[v];
    }
    rep(i,1,1+n){
        printf("%d\n",f[i].count());
    }
    return 0;
}