int l[N],r[N],id[N],sz[N],hs[N],tot;
vector<int> e[N];

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

    };
    auto del=[&](int x){

    };
    for(auto v:e[u]){
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