/*
给你一棵树，边带权，统计树上距离不超过 k 的点对数。
*/

vector<pii> e[N];
int k,sz[N],del[N],maxs[N];
int root,maxx;
ll ans=0;

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
    VI vt1,vt2;
    del[root]=1;
    auto calc=[&](VI &vt){
        ll res=0;
        sort(all(vt));
        int n=SZ(vt);
        int r=n-1;
        rep(l,0,n){
            while(r>=0&&vt[l]+vt[r]>k) r--;
            if(l<r) res+=r-l;
        }
        return res;
    };
    vt1.pb(0);
    for(auto [x,w]:e[root]){
        if(del[x]) continue;
        vt2.clear();
        function<void(int,int,int)> dfs2=[&](int x,int fa,int dep){
            sz[x]=1;
            vt1.pb(dep);
            vt2.pb(dep);
            for(auto [v,w]:e[x]){
                if(v==fa||del[v]) continue;
                dfs2(v,x,dep+w);
                sz[x]+=sz[v];
            }
        };
        dfs2(x,root,w);
        ans-=calc(vt2);
    }
    ans+=calc(vt1);
    for(auto [x,w]:e[root]){
        if(del[x]) continue;
        dfs(x,sz[x]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d",&n);
    rep(i,1,n){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        e[u].pb({v,w});
        e[v].pb({u,w});
    }
    scanf("%d",&k);
    dfs(1,n);
    printf("%lld",ans);
	return 0;
}