/*给你一个 n(1≤n≤2000) 个点的树。

给你 m(1≤m≤2000) 条树上的简单路径，每个路径有个权值 ai(1≤ai≤109)。

要求选择一些路径，使得每个点至多在一条路径上，并且路径的权值和最大。*/

int n,m,a[N],dep[N],fa[N];
ll dp[N],sdp[N];
vector<int> e[N];
vector<array<int,3>> path[N];

void dfs(int u){
    ll tmp=0;
    for(auto v:e[u]){
        dfs(v);
        tmp+=dp[v];
    }
    dp[u]=tmp;//包含这个点的路径
    sdp[u]=tmp;//不包含这个点的路径
    for(auto [x,y,w]:path[u]){
        tmp=sdp[u]+w;
        while(x!=u){
            tmp+=-dp[x]+sdp[x];
            x=fa[x];
        }
        while(y!=u){
            tmp+=sdp[y]-dp[y];
            y=fa[y];
        }
        dp[u]=max(dp[u],tmp);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //memset(dp,-inf,sizeof(dp));
	scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i){
        scanf("%d",&fa[i]);
        e[fa[i]].push_back(i);
        dep[i]=dep[fa[i]]+1;
    }
    for(int i=1;i<=m;++i){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        int c=x,d=y;
        while(x!=y){
            if(dep[x]>dep[y])
            x=fa[x];
            else y=fa[y];
        }
        path[x].push_back({c,d,w});
    }
    dfs(1);
    printf("%lld",dp[1]);
	return 0;
}