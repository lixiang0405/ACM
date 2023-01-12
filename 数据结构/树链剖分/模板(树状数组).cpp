/*
1 x y z，表示将树从 x 到 y 结点最短路径上所有节点的值都加上 z。

2 x y，表示求树从 x 到 y 结点最短路径上所有节点的值之和。

3 x z，表示将以 x 为根节点的子树内所有节点值都加上 z。

4 x 表示求以 x 为根节点的子树内所有节点值之和
*/

int p;

template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){n=s;}

    T query(int x){
        assert(x<=n);
        T s=0;
        for(;x;x-=lowbit(x)){
            s=(s+c[x])%p;
        }
        return s;
    }

    void modify(int x,T s){
        assert(x!=0);
        for(;x<=n;x+=lowbit(x)){
            c[x]=(c[x]+s)%p;
        }
    }
 
    //树状数组上二分
    int ask(T s){
        int pos=0;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos+(1<<i)<=n&&c[pos+(1<<i)]<=s){
                pos+=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<ll> c,d;

//令所有的ai(l≤i≤r)加上d。
void modify(int l,int r,ll f){
    c.modify(l,f);
    c.modify(r+1,-f);
    d.modify(l,f*l%p);
    d.modify(r+1,-f*(r+1)%p);
}

//查询(∑(i=1-x)ai)
ll query(int l,int r){
    l--;
    return ((c.query(r)*(r+1)-d.query(r)-c.query(l)*(l+1)+d.query(l))%p+p)%p;
}

int fa[N],l[N],r[N],sz[N],dep[N],hs[N],top[N],id[N];
int tot,n,m;
vector<int> e[N];

void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	sz[u]=1;
	hs[u]=-1;
	for(auto v:e[u]){
		if(v==f) continue;
		fa[v]=u;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(hs[u]==-1||sz[v]>sz[hs[u]]) 
			hs[u]=v;
	}
}

void dfs2(int u,int f){//f:链头
	l[u]=++tot;
	top[u]=f;
	id[tot]=u;
	if(hs[u]!=-1){
		dfs2(hs[u],f);
	}
	for(auto v:e[u]){
		if(v!=fa[u]&&v!=hs[u])
		dfs2(v,v);
	}
	r[u]=tot;
}

ll ask(int x,int y){
    ll ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			ans=(ans+query(l[top[x]],l[x]))%p;
			x=fa[top[x]];
		}else{
            ans=(ans+query(l[top[y]],l[y]))%p;
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
        ans=(ans+query(l[y],l[x]))%p;
	}else{
        ans=(ans+query(l[x],l[y]))%p;
	}
    return ans;
}

void change(int x,int y,ll d){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			modify(l[top[x]],l[x],d);
			x=fa[top[x]];
		}else{
			modify(l[top[y]],l[y],d);
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		modify(l[y],l[x],d);
	}else{
		modify(l[x],l[y],d);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R;
    cin>>n>>m>>R>>p;
    c.resize(n);
    d.resize(n);
    vector<int> a(n+1);
    rep(i,1,n+1) cin>>a[i];
    rep(i,0,n-1){
        int u,v;
        cin>>u>>v;
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs1(R,0);
    dfs2(R,R);
    rep(i,1,n+1) modify(l[i],l[i],a[i]);
    while(m--){
        int ty;
        cin>>ty;
        if(ty==1){
            int u,v,d;
            cin>>u>>v>>d;
            change(u,v,d);
        }else if(ty==2){
            int u,v;
            cin>>u>>v;
            cout<<ask(u,v)<<endl;
        }else if(ty==3){
            int u,d;
            cin>>u>>d;
            modify(l[u],r[u],d);
        }else{
            int u;
            cin>>u;
            cout<<query(l[u],r[u])<<endl;
        }
    }
    return 0;
} 