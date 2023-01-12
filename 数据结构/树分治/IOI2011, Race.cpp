/*
给一棵n个点的树，每条边有权。求一条简单路径，权值和等于k，且边的数量最小。
*/

inline ull splitmix64(ull x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}
constexpr int BIT_MASK(int t) { return t ? BIT_MASK(t >> 1) << 1 | 1 : 0; }
template <typename T, const int BIT, const int LIM>
struct hashTable {
#define idx(key) splitmix64(key) & BIT
    struct {
        int next;
        ull key;
        T val;
    } data[LIM];
    int first[BIT + 1], cnt = 0;
    int find(ull key) {
        for (int i = first[idx(key)]; i; i = data[i].next)
            if (data[i].key == key) return i;
        return 0;
    }
    T& at(int pos) { return data[pos].val; }
    T& operator[](ull key) {
        int pos = find(key);
        if (pos) return at(pos);
        ull K = idx(key);
        data[++cnt] = {first[K], key, T()};
        return at(first[K] = cnt);
    }
    void clear() {
        for (int& i = cnt; i; --i) first[idx(data[i].key)] = 0;
    }
    #undef idx
};
hashTable<int, BIT_MASK(N), BIT_MASK(N)> hs;

vector<pii> e[N];
int k,sz[N],del[N],maxs[N];
int root,maxx;
int ans;

void dfs1(int u,int fa,int s){
    sz[u]=1;
    maxs[u]=0;
    for(auto [v,w]:e[u]){
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
    vector<pii> vt;
    hs.clear();
    hs[0]=0;
    for(auto [x,w]:e[root]){
        if(del[x]) continue;
        vt.clear();
        function<void(int,int,int,int)> dfs2=[&](int x,int fa,int dep,int val){
            sz[x]=1;
            vt.pb({dep,val});
            for(auto [v,w]:e[x]){
                if(v==fa||del[v]) continue;
                dfs2(v,x,dep+1,val+w);
                sz[x]+=sz[v];
            }
        };
        dfs2(x,root,1,w);
        for(auto [dep,val]:vt){
            if(k-val>=0&&hs.find(k-val)) ans=min(ans,dep+hs[k-val]);
        }
        for(auto [dep,val]:vt){
            if(hs.find(val)) hs[val]=min(hs[val],dep);
            else hs[val]=dep;
        }
    }
    for(auto [x,w]:e[root]){
        if(del[x]) continue;
        dfs(x,sz[x]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d%d",&n,&k);
    ans=n+1;
    rep(i,1,n){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        e[u].pb({v,w});
        e[v].pb({u,w});
    }
    dfs(1,n);
    if(ans==n+1) ans=-1;
    printf("%d",ans);
	return 0;
}