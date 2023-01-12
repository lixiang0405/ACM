/*给你一个 n(1≤n≤105) 个点的树。

对于每个点，求出包含这个点的连通块个数，答案对 m(2≤m≤109) 取模。m不一定是质数。*/

int n,m;
vector<int> e[N];
ll dp[N],dp2[N],ans[N];

void dfs(int u){
    dp[u]=1;
    for(auto v:e[u]){
        dfs(v);
        dp[u]=dp[u]*(dp[v]+1)%m;
    }
}

void dfs2(int u){
    int sz=e[u].size();
    if(sz==0) return;
    static ll pre[N],surf[N];
    pre[0]=1,surf[sz+1]=1;
    for(int i=1;i<=sz;++i){
        int v=e[u][i-1];
        pre[i]=pre[i-1]*(dp[v]+1)%m;
    }
    for(int i=sz;i>=1;--i){
        int v=e[u][i-1];
        surf[i]=surf[i+1]*(dp[v]+1)%m;
    }
    for(int i=1;i<=sz;++i){
        int v=e[u][i-1];
        dp2[v]=(pre[i-1]*surf[i+1])%m; 
        if(u!=1) dp2[v]=dp2[v]*(dp2[u]+1)%m;//此时dp2[u]将树倒过来的v的一棵子树
    }//dp2[v]表示以v点为根把树倒过来
    for(auto v:e[u]){
        ans[v]=(dp[v]*(dp2[v]+1))%m;//为什么要加一:因为dp2[v]表示的是所有u子树的连通块
        dfs2(v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i){
        int x;
        scanf("%d",&x);
        e[x].push_back(i);
    }
    dfs(1);
    dfs2(1);
    ans[1]=dp[1];
    for(int i=1;i<=n;++i)
    printf("%lld\n",ans[i]);
	return 0;
}