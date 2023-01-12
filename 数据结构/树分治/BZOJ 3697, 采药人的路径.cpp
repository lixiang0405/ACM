/*
采药人的药田是一个树状结构，每条路径上都种植着同种药材。
采药人以自己对药材独到的见解，对每种药材进行了分类。
大致分为两类，一种是阴性的，一种是阳性的。
采药人每天都要进行采药活动。
他选择的路径是很有讲究的，他认为阴阳平衡是很重要的，
所以他走的一定是两种药材数目相等的路径。采药工作是很辛苦的，
所以他希望他选出的路径中有一个可以作为休息站的节点（不包括起点和终点），
满足起点到休息站和休息站到终点的路径也是阴阳平衡的。
他想知道他一共可以选择多少种不同的路径。
*/

vector<pii> e[N];
int sz[N],del[N],maxs[N],cnt[N],f[N][2];
int root,maxx;
ll ans;

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
    cnt[s]=1;
    for(auto [x,w]:e[root]){
        if(del[x]) continue;
        vt.clear();
        function<void(int,int,int)> dfs2=[&](int x,int fa,int val){
            sz[x]=1;
            if(!val&&cnt[s]>1) ans++;
            cnt[s+val]++;
            vt.pb({s+val,cnt[s+val]!=1});
            for(auto [v,w]:e[x]){
                if(v==fa||del[v]) continue;
                dfs2(v,x,val+w);
                sz[x]+=sz[v];
            }
            cnt[s+val]--;
        };
        dfs2(x,root,w);
        for(auto [val,is]:vt){
            if(is) ans+=f[2*s-val][0]+f[2*s-val][1];
            else ans+=f[2*s-val][1];
        }
        for(auto [val,is]:vt){
            f[val][is]++;
        }
    }
    cnt[s]=0;
    rep(i,0,2*s+1) f[i][0]=f[i][1]=0;
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
    ans=0;
    rep(i,1,n){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        if(!w) w--;
        e[u].pb({v,w});
        e[v].pb({u,w});
    }
    dfs(1,n);
    printf("%lld",ans);
	return 0;
}