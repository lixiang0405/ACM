/*
⼀张带边权带点权⽆向图。从某点出发，有初始声望。
每第⼀次到达⼀个点将获得点权等值的声望加成。
经过⼀条边需要满⾜边权等值的最低声望限制。
多次给出起点和初始声望，询问能达到的最⼤声望。
按照边权从⼩到⼤建⽴ Kruskal 重构树。每次询问都是从叶⼦
出发，在树上倍增。向上找到第⼀条不能通过的边（即，该边
下⾯的⼦树的 叶⼦点权和 加上 初始声望 ⼩于该边边权），把
下⾯⼦树的 叶⼦点权和 加上 初始声望 即为答案。
复杂度O((n + m)log m + q log n)
*/

int t,cnt=0,par[N][M+1],depth[N],val[N][M+1],a[N];
vector<pii> e[N];

struct DSU {
    vector<int> fa, sz;
	int n;
    DSU(int n) : fa(n+1), sz(n+1, 1),n(n){ 
		for(int i=0 ; i<=n ; ++i) fa[i] = i;    
    }
    int find(int x) {
        /*while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;*/
        return fa[x]==x?x:fa[x]=find(fa[x]);
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        sz[x] += sz[y];
        fa[y] = x;
        return true;
    }
    int size(int x) { return sz[find(x)]; }
	int size(){
		set<int> st; 
		for(int i=1;i<=n;++i){
			st.insert(find(i));
		}
		return st.size();
	}
};

void dfs(int u,int fa){
    depth[u]=depth[fa]+1;
    par[u][0]=fa;
    for(auto [v,w]:e[u]){
        dfs(v,u);
        a[u]+=a[v];
    }
    for(auto [v,w]:e[u]){
        val[v][0]=a[v]-w;
    }
}

void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    rep(i,1,1+n){
        cin>>a[i];
        ++cnt;
    }
    vector<array<int,3>> vt;
    rep(i,1,1+m){
        int u,v,w;
        cin>>u>>v>>w;
        vt.pb({w,u,v});
    }
    sort(all(vt));
    DSU d(n+m);
    for(auto [w,u,v]:vt){
        if(d.same(u,v)) continue;
        ++cnt;
        e[cnt].pb({d.find(v),w});
        e[cnt].pb({d.find(u),w});
        //cout<<cnt<<" "<<d.find(u)<<" "<<d.find(v)<<'\n';
        d.merge(cnt,v);
        d.merge(cnt,u);
    }
    dfs(cnt,0);
    for(int i=1;i<=M;++i){
		for(int u=1;u<=cnt;++u){
			par[u][i]=par[par[u][i-1]][i-1];
			val[u][i]=min(val[par[u][i-1]][i-1],val[u][i-1]);
		}
	}
    while(q--){
        int x,k;
        cin>>x>>k;
        per(i,0,M+1){
            if(par[x][i]&&val[x][i]+k>=0) x=par[x][i];
        }
        cout<<a[x]+k<<'\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	t=1;
	while(t--){
		solve();
	}
	return 0;
}
