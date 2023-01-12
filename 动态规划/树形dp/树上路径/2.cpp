/*给你一个 n(1≤n≤2000) 个点的树。

给你 m(1≤m≤2000) 条树上的简单路径，每个路径有个权值 ai(1≤ai≤109)。这里保证每条路径都是从一个点到它的祖先。

要求选择一些路径，使得每个点至少在一条路径上，并且路径的权值和最小。如果不存在，输出-1。*/

int n,m,dep[N];
ll dp[N][N];
vector<int> e[N];
vector<array<int,2>> path[N];

void merge(ll *a,ll *b,int len){
    static ll sufa[N],sufb[N];
    sufa[len+1]=inf;
    sufb[len+1]=inf;
    for(int i=len;i>=1;--i){
        sufa[i]=min(sufa[i+1],a[i]);
        sufb[i]=min(sufb[i+1],b[i]);
    }
    //printf("%d\n",a[len]);
    /*合并第一棵子树的时候
    a[i]=min(a[i]+sufb[i],b[i]) 
    sufa[i]=0,a[len]=0;
    a[len]=(sufb[len],b[len])=b[len]

    合并第二棵子树
    a[len]=min(b[len]+a[len],a[len]+b[len])
    ==a[len]+=b[len];

    合并k棵
    sufa[x]>=a[len]=(b1,b2,b3.....bk)[len]
    b[i]+sufa[i]：
    即保证至少每棵子树的所有点都会被取到
    的情况下，去找到从当前b子树到dep[1-len-1]的所有路径权值
    a[i]+sufb：
    b1...bk-1的到i的最小值+sufb[i]->保证bk这颗子树取到
    */
    for(int i=1;i<=len;++i){
        a[i]=min(b[i]+sufa[i],a[i]+sufb[i]);
    }
}

void dfs(int u){
    for(int i=1;i<=dep[u];++i) dp[u][i]=inf;
    for(auto [p,w]:path[u]){
        dp[u][dep[p]]=min(dp[u][dep[p]],1ll*w);
    }
    for(auto v:e[u]){
        dfs(v);
        merge(dp[u],dp[v],dep[v]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //memset(dp,-inf,sizeof(dp));
	scanf("%d%d",&n,&m);
    dep[1]=1;
    for(int i=2;i<=n;++i){
        int x;
        scanf("%d",&x);
        e[x].push_back(i);
        dep[i]=dep[x]+1;
    }
    for(int i=1;i<=m;++i){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        path[y].push_back({x,w});
    }
    dfs(1);
    if(dp[1][1]>=inf)
    printf("-1");
    else 
    printf("%lld",dp[1][1]);
	return 0;
}