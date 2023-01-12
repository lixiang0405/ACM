/*
∑i=(1-n)∑j=(i+1-n)[a[i]⊕a[j]=a[lca(i,j)]](i⊕j).
*/

int l[N],r[N],id[N],sz[N],hs[N],tot,a[N];
vector<int> e[N];
ll ans=0;
int cnt[(1<<20)+10][18][2];

void dfs(int u,int f){
    l[u]=++tot;
    id[tot]=u;
    sz[u]=1;
    hs[u]=-1;
    for(auto v:e[u]){
        if(v==f) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(hs[u]==-1||sz[v]>sz[hs[u]])
        hs[u]=v;
    }
    r[u]=tot;
}

void dsu(int u,int f,bool keep){
    for(auto v:e[u]){
        if(v!=f&&v!=hs[u])
        dsu(v,u,false);
    }
    if(hs[u]!=-1){
        dsu(hs[u],u,true);
    }
    auto add=[&](int x){
        rep(j,0,18){
            cnt[a[x]][j][(x>>j)&1]++;
        }
    };
    auto del=[&](int x){
        rep(j,0,18){
            cnt[a[x]][j][(x>>j)&1]--;
        }
    };
    auto query=[&](int x){
        rep(j,0,18){
            ans+=(ll)cnt[a[x]^a[u]][j][((x>>j)&1)^1]<<j;
        }
    };
    for(auto v:e[u]){
        if(v!=f&&v!=hs[u]){
            for(int i=l[v];i<=r[v];++i)
            query(id[i]);
        }
        if(v!=f&&v!=hs[u]){
            for(int i=l[v];i<=r[v];++i)
            add(id[i]);
        }
    }
    add(u);
    if(!keep){
        for(int i=l[u];i<=r[u];++i)
        del(id[i]);
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d",&n);
    rep(i,1,n+1) scanf("%d",&a[i]);
    rep(i,0,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs(1,0);
    dsu(1,0,false);
    printf("%lld",ans);
    return 0;
} 