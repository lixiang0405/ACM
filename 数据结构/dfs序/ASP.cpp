/*给你一棵 N 个顶点的树。点 i 的颜色为 Ai
最初，树的根是顶点 1。
在这棵树上处理Q查询，每一种都是以下三种类型之一：
1 u c：对于每个点 x 使得 x 位于 u 的子树中，设置 Ax=c
2 u：将树的根改为u
3 u c：统计u的子树中颜色为c的顶点个数*/
 
int t;
int n,q,l[N],r[N],tot=0,a[N],id[N];
vector<int> e[N];
int par[N][M+1],depth[N];

struct Tree{
	int l,r;
	map<int,int> mp;
	set<int> st;
	int t;
}tre[4*N];

void pushdown(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	b.t=c.t=a.t;
	b.mp.clear();
	c.mp.clear();
	b.mp[a.t]=b.r-b.l+1;
	c.mp[a.t]=c.r-c.l+1;
	b.st.clear();
	c.st.clear();
	a.t=0;
}

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	set<int> tmp;
	for(auto cur:b.st){
		tmp.insert(cur);
	}
	for(auto cur:c.st){
		tmp.insert(cur);
	}
	for(auto cur:tmp){
		a.mp[cur]=0;
		if(b.mp.count(cur)) a.mp[cur]+=b.mp[cur];
		if(c.mp.count(cur)) a.mp[cur]+=c.mp[cur];
		if(a.mp[cur]==0) a.mp.erase(cur);
	}
	a.st=tmp;
	b.st.clear();
	c.st.clear();
}

void build(int k,int x,int y){
	tre[k].mp.clear();
	tre[k].st.clear();
	tre[k].t=0;
	if(x==y){
		tre[k].l=x,tre[k].r=y;
		tre[k].mp[a[id[x]]]++;
		tre[k].st.insert(a[id[x]]);
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}

void modify(int k,int x,int y,int d){
	if(x>y) return;
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		tre[k].t=d;
		for(auto [i,j]:tre[k].mp) tre[k].st.insert(i);
		tre[k].mp.clear();
		tre[k].mp[d]=tre[k].r-tre[k].l+1;
		tre[k].st.insert(d);
	}else{
		if(tre[k].t)
			pushdown(k);
		if(y<=m) modify(k<<1,x,y,d);
		else if(x>m) modify(k<<1|1,x,y,d);
		else modify(k<<1,x,m,d),modify(k<<1|1,m+1,y,d);
		update(k);
	}
}

int Q(int k,int x,int y,int d){
	if(x>y) return 0;
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==x&&r==y){
		if(tre[k].mp.count(d)) return tre[k].mp[d];
		else return 0;
	}else{
		if(tre[k].t)
			pushdown(k);
		if(y<=m) return Q(k+k,x,y,d);
		else if(x>m) return Q(k<<1|1,x,y,d);
		else return Q(k<<1,x,m,d)+Q(k<<1|1,m+1,y,d);
	}
}

void dfs(int u,int f){
	depth[u]=depth[f]+1;
    l[u]=++tot;
	id[l[u]]=u;
    for(auto v:e[u]){
        if(v==f) continue;
		par[v][0]=u;
        dfs(v,u);
    }
    r[u]=tot;
}

int query(int u,int v){
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
	return par[u][0];
}

int s(int u,int v){
	if(depth[u]>depth[v]) swap(u,v);
	int d=depth[v]-depth[u]-1;
	for(int i=M;i>=0;--i){
		if(d&(1<<i)){
			v=par[v][i];
		}
	}
	return v;
}

void solve(){
	int n,q;
	tot=0;
	cin>>n;
	rep(i,1,1+n) cin>>a[i];
	rep(i,1,1+n) e[i].clear();
	for(int i=0;i<n-1;++i){
        int u,v;
		cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
	build(1,1,n);
	for(int i=1;i<=M;++i){
		for(int u=1;u<=n;++u){
			par[u][i]=par[par[u][i-1]][i-1];
		}
	}
	cin>>q;
	int root=1;
	while(q--){
		int ty;
		cin>>ty;
		if(ty==1){
			int u,c;
			cin>>u>>c;
			if(u==root){
				modify(1,1,n,c);
			}else if(query(u,root)==root){
				modify(1,l[u],r[u],c);
			}else if(query(u,root)==u){
				int son=s(u,root);
				modify(1,1,l[son]-1,c);
				modify(1,r[son]+1,n,c);
			}else{
				modify(1,l[u],r[u],c);
			}
		}else if(ty==2){
			cin>>root;
		}else{
			int u,c;
			cin>>u>>c;
			if(u==root){
				cout<<Q(1,1,n,c)<<'\n';
			}else if(query(u,root)==root){
				cout<<Q(1,l[u],r[u],c)<<'\n';
			}else if(query(u,root)==u){
				int son=s(u,root);
				cout<<Q(1,1,l[son]-1,c)+Q(1,r[son]+1,n,c)<<'\n';
			}else{
				cout<<Q(1,l[u],r[u],c)<<'\n';
			}
		}
	}
	for(int i=0;i<=M;++i){
		for(int u=1;u<=n;++u){
			par[u][i]=0;
		}
	}
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>t;
    while(t--){
        solve();
    }
	return 0;
}