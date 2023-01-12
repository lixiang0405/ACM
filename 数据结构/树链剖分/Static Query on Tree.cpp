/*
在 X 国，有 n 个城市和 n-1 条单向道路，所有城市都可以到达城市 1。一次查询会给出 3 组城市 A、B、C。Alice 会在集合 A 中选择一个城市 x，选择
集合 C 中的一个城市 z，并从 x 步行到 z（如果 x 可以到达 z）。
Bob 将在集合 B 中选择一个城市 y，然后从 y 步行到 z（如果 y 可以到达 z）。
爱丽丝和鲍勃相遇的城市可能有多少个城市？
有 T 个测试用例，每个用例有 q 个查询。
*/

struct Tree{
	int l,r;
	int cnt[8];
    int t,c;
}tre[4*N];

int fa[N],l[N],r[N],sz[N],dep[N];
int hs[N],top[N],id[N],a[N];
int tot,n,m;
vector<int> e[N];

void push(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.c=0;
	b.c=1;
	c.c=1;
	b.cnt[0]=b.r-b.l+1;
	c.cnt[0]=c.r-c.l+1;
	b.t=c.t=0;
	for(int i=1;i<8;++i) b.cnt[i]=c.cnt[i]=0;
}

void pushdown(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	int d=a.t;
	for(int i=0;i<8;++i) {
		if((i|d)!=i){
			b.cnt[i|d]+=b.cnt[i],b.cnt[i]=0;
			c.cnt[i|d]+=c.cnt[i],c.cnt[i]=0;			
		}
	}
	b.t|=d;
	c.t|=d;
	a.t=0;
}

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	for(int i=0;i<8;++i) a.cnt[i]=b.cnt[i]+c.cnt[i];
}

void build(int k,int x,int y){
	tre[k].t=tre[k].c=0;
	if(x==y){
		tre[k]={x,y,1,0,0,0,0,0,0,0,0,0};
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}

void modify(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r;
	if(x==l&&y==r){
		if(tre[k].c){
			tre[k].c=0;
			if(x!=y){
				auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
				b.cnt[0]=(b.r-b.l+1);
				c.cnt[0]=(c.r-c.l+1);
				b.t=c.t=0;
				for(int i=1;i<=7;++i) b.cnt[i]=c.cnt[i]=0;
				b.c=1;
				c.c=1;
			}
		}
		tre[k].t|=d;
		for(int i=0;i<8;++i){
			if((i|d)!=i){
				tre[k].cnt[i|d]+=tre[k].cnt[i];
				tre[k].cnt[i]=0;
			}
		}
	}else{
		if(tre[k].c)
			push(k);
		if(tre[k].t)
			pushdown(k);
		int m=(l+r)/2;
		if(y<=m) modify(k+k,x,y,d);
		else if(x>m) modify(k+k+1,x,y,d);
		else modify(k+k,x,m,d),modify(k+k+1,m+1,y,d);
		update(k);
	}
}


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

void change(int x,int y,int col){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			modify(1,l[top[x]],l[x],col);
			x=fa[top[x]];
		}else{
			modify(1,l[top[y]],l[y],col);
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		modify(1,l[y],l[x],col);
	}else{
		// cout<<l[x]<<" "<<l[y]<<endl;
		modify(1,l[x],l[y],col);
	}
}

int t,A,B,C,q;

void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;++i) e[i].clear();
    tot=0;
    for(int i=2;i<=n;++i){
        int u;
        cin>>u;
        e[u].push_back(i);
		//e[i].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    while(q--){
        cin>>A>>B>>C;
        for(int i=1;i<=A;++i){
            int x;
            cin>>x;
            change(1,x,1);
        }
        for(int i=1;i<=B;++i){
            int x;
            cin>>x;
            change(1,x,2);
        }
        for(int i=1;i<=C;++i){
            int x;
            cin>>x;
            modify(1,l[x],r[x],4);
        }
		cout<<tre[1].cnt[7]<<endl;
        tre[1].c=1;
		tre[1].t=0;
		tre[1].cnt[0]=n;
		for(int i=1;i<8;++i) tre[1].cnt[i]=0;
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