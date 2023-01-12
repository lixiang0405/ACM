/*
在一片土地上有 n 个城市，通过 n−1 条无向边互相连接，形成一棵树的结构，
相邻两个城市的距离为1，其中第 i 个城市的价值为 wi。
不幸的是，这片土地常常发生地震，并且随着时代的发展，城市的价值也往往会发生变动。
接下来你需要在线处理 M 次操作：

0 x k 表示发生了一次地震，震中城市为 x，影响范围为 k，
所有与 x 距离不超过 k 的城市都将受到影响，
该次地震造成的经济损失为所有受影响城市的价值和。

1 x y 表示第 x 个城市的价值变成了 y。
为了体现程序的在线性，操作中的 x,y,k 都需要异或你程序上一次的输出来解密，

如果之前没有输出，则默认上一次的输出为 0。
*/

#define lowbit(x) x&(-x)
template<class T>
struct BIT{
    vector<T> c;
    int n;
    void resize(int s){
        n=s+1;
		c.resize(n+1);
    }

    T query(int x){
		x++;
		if(x<=0) return 0;
        T s=0;
		x=min(x,n);
        for(;x;x-=lowbit(x)){
            s+=c[x];
        }
        return s;
    }

    void modify(int x,T s){
        x++;
        for(;x<=n;x+=lowbit(x)){
            c[x]+=s;
        }
    }
 
    //树状数组上二分 查询最大的T(0≤T≤n)满足∑(i=1-T) ai≤s。
    int ask(T s){
        int pos=n;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos-(1<<i)<=n&&c[pos-(1<<i)]<=s){
                pos-=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<int> c[2*N];
int tot=0;
vector<int> e[N];
int sz[N],del[N],maxs[N],w[N];
int root,maxx;
vector<array<int,3>> b[N];

void dfs1(int u,int fa,int s){
    sz[u]=1;
    maxs[u]=0;
    for(auto v:e[u]){
        if(del[v]||v==fa) continue;
        dfs1(v,u,s);
        sz[u]+=sz[v];
        maxs[u]=max(maxs[u],sz[v]);
    }
    maxs[u]=max(maxs[u],s-sz[u]);
    if(maxs[u]<maxx){
        maxx=maxs[u];
        root=u;
    }
}

void dfs(int u,int s){
    maxx=s+1;
    dfs1(u,0,s);
    del[root]=1;
	int d1=0,d2=0;
    int t1=tot++;
	b[root].pb({t1,0,1});
	for(auto x:e[root]){
        if(del[x]) continue;
		d2=0;
		int t2=tot++;
        function<void(int,int,int)> dfs2=[&](int x,int fa,int dep){
            sz[x]=1;
			d1=max(d1,dep);
			d2=max(d2,dep);
			b[x].pb({t1,dep,1});
			b[x].pb({t2,dep,0});
		    for(auto v:e[x]){
                if(v==fa||del[v]) continue;
                dfs2(v,x,dep+1);
                sz[x]+=sz[v];
            }
        };
		dfs2(x,root,1);
		c[t2].resize(d2);
	}
	c[t1].resize(d1);
    for(auto x:e[root]){
        if(del[x]) continue;
        dfs(x,sz[x]);
    }
}

void modify(int x,int val){
	for(auto [id,dep,ty]:b[x]){
		c[id].modify(dep,val);
	}
}

int query(int x,int k){
	int ans=0;
	for(auto [id,dep,ty]:b[x]){
		if(ty) ans+=c[id].query(k-dep);
		else ans-=c[id].query(k-dep);
	}
	return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    scanf("%d%d",&n,&m);
	rep(i,1,1+n) scanf("%d",&w[i]);
    rep(i,1,n){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs(1,n);
	rep(i,1,1+n) modify(i,w[i]);
	int ans=0;
	while(m--){
		int ty;
		scanf("%d",&ty);
		if(ty){
			int x,y;
			scanf("%d%d",&x,&y);
			x^=ans,y^=ans;
			modify(x,y-w[x]);
			w[x]=y;
		}else{
			int x,k;
			scanf("%d%d",&x,&k);
			x^=ans,k^=ans;
			ans=query(x,k);
			printf("%d\n",ans);
		}
	}
	return 0;
}