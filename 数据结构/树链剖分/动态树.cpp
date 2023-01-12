/*
别忘了这是一棵动态树，每时每刻都是动态的。
小明要求你在这棵树上维护两种事件。

0 u delta，这棵树长出了一些果子, 
即u的子树中的每个节点都会长出delta个果子.

1 k u1 v1 ... uk vk，小明希望你求出几条树枝上的果子数.
 一条树枝其实就是一个从某个节点到根的路径的一段. 
 每次小明会选定一些树枝, 
 让你求出在这些树枝上的节点的果子数的和。
 注意, 树枝之间可能会重合, 
 这时重合的部分的节点的果子只要算一次。
*/

template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){n=s;}

    T query(int x){
        assert(x<=n);
        T s=0;
        for(;x;x-=lowbit(x)){
            s+=c[x];
        }
        return s;
    }

    void modify(int x,T s){
        assert(x!=0);
        for(;x<=n;x+=lowbit(x)){
            c[x]+=s;
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

BIT<ui> c,d;

//令所有的ai(l≤i≤r)加上d。
void modify(int l,int r,ui f){
    c.modify(l,f);
    c.modify(r+1,-f);
    d.modify(l,f*l);
    d.modify(r+1,-f*(r+1));
}

//查询(∑(i=1-x)ai)
ui query(int l,int r){
    l--;
    return c.query(r)*(r+1)-d.query(r)-c.query(l)*(l+1)+d.query(l);
}

template<class T>
class Count{
public:
    set<pair<T,T>> st;
    T cnt;
    Count() {
        cnt=0;
        st.clear();
    }
    
    void add(T l, T r) {
        if(l>r) return;
        auto it=st.lower_bound({l,0});
        if(it!=st.begin()&&(*prev(it)).second>=l){
            it--;
        }
        T ll=l,rr=r;
        while(it!=st.end()){
            if(it->first>r) break;
            cnt-=it->second-it->first+1;
            ll=min(it->first,ll);
            rr=max(r,it->second);
            st.erase(it++);
        }
        cnt+=rr-ll+1;
        st.insert({ll,rr});
    }

    T count() {
        return cnt;
    }
};

Count<int> cnt;
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

void ask(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			cnt.add(l[top[x]],l[x]);
			x=fa[top[x]];
		}else{
            cnt.add(l[top[y]],l[y]);
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
        cnt.add(l[y],l[x]);
	}else{
        cnt.add(l[x],l[y]);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d",&n);
    c.resize(n);
    d.resize(n);
    rep(i,0,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    int q;
    scanf("%d",&q);
    while(q--){
        int ty;
        scanf("%d",&ty);
        if(ty){
            cnt=Count<int>();
            int k;
            scanf("%d",&k);
            while(k--){
                int u,v;
                scanf("%d%d",&u,&v);
                ask(u,v);
            }
            ui ans=0;
            for(auto [l,r]:cnt.st){
                ans+=query(l,r);
            }
            printf("%u\n",ans%(1LL<<31));
        }else{
            int u,d;
            scanf("%d%d",&u,&d);
            modify(l[u],r[u],d);
        }
    }
    return 0;
} 