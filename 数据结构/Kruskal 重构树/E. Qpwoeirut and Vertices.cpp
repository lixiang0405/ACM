/*
给出 n 个点， m 条边的不带权连通无向图， q 次询问至少要加完编号前多少的边，才能使得 [l,r] 中的所有点两两连通。

思考 Kruskal 重构树的最基本的功能是什么：
它可以帮助我们求出带权图上的连通两点之间的所有路径中最大边权的最小值（或者最小边权的最大值）。

那么在本题中，我们可以把每条边的边权看做它的编号。这样一来，对于每个询问，若 l=r ，显然答案是 0；
否则，答案就是 l,l+1,...,r这 r-l+1个点在 Kruskal 重构树上的最近公共祖先。

注意到 LCA 运算具有交换律和结合律，所以直接用线段树维护

不难发现，原图中两个点之间的所有简单路径上最大边权的最小值 = 最小生成树上两个点之间的简单路径上的最大值 = Kruskal 重构树上两点之间的 LCA 的权值。
*/

int n,q,par[N][M+1],depth[N],fa[N];
vector<int> e[N];
 
struct Tree{
	int l,r;
	int val;
}tre[400000];
 
void dfs(int u,int f){
	depth[u]=depth[f]+1;
	for(auto v:e[u]){
		if(v==f) continue;
		par[v][0]=u;
		dfs(v,u);
	}
}
 
int LCA(int u,int v){
	if(depth[u]>depth[v]) swap(u,v);
	int d=depth[v]-depth[u];
	for(int i=M;i>=0;--i){
		if(d&(1<<i)){
			v=par[v][i];
		}
	}
	if(u==v)
	return u;
	for(int i=M;i>=0;--i){
		if(par[u][i]!=par[v][i]){
			u=par[u][i],v=par[v][i];
		}
	}
	return u==v?u:par[u][0];
}
 
int find(int u){
    return u==fa[u]?u:fa[u]=find(fa[u]);
}
 
void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	a.val=LCA(b.val,c.val);
}
 
void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,x};
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}
 
int query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r;
	if(l==x&&y==r){
		return tre[k].val;
	}else{
		int m=(l+r)/2;
		if(y<=m) return query(k+k,x,y);
		else if(x>m) return query(k+k+1,x,y);
		else{
			return LCA(query(k+k,x,m),query(k+k+1,m+1,y));
		}
	}
}
 
int t;
 
void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=n+m;++i) e[i].clear(),fa[i]=i;
    int tot;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        u=find(u),v=find(v);
        if(u==v) continue;
        fa[u]=fa[v]=n+i;
        e[n+i].push_back(u);
        e[n+i].push_back(v);
        tot=n+i;
    }
    dfs(tot,0);
	for(int i=1;i<=M;++i){
		for(int u=1;u<=n+m;++u){
			par[u][i]=par[par[u][i-1]][i-1];
		}
	}
    build(1,1,n);
    while(q--){
        int l,r;
        cin>>l>>r;
        if(l==r) cout<<0<<" ";
        else cout<<query(1,l,r)-n<<" ";
    }
    cout<<endl;
}
 
 
