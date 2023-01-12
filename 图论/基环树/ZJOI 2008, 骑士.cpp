/*
骑士团是肯定具有打败邪恶势力的能力的，但是骑士们互相之间往往有一些矛盾。

每个骑士都有且仅有一个自己最厌恶的骑士（当然不是他自己），

他是绝对不会与自己最厌恶的人一同出征的。

战火绵延，人民生灵涂炭，组织起一个骑士军团加入战斗刻不容缓！

国王交给了你一个艰巨的任务，从所有的骑士中选出一个骑士军团，

使得军团内没有矛盾的两人（不存在一个骑士与他最痛恨的人一同被选入骑士军团的情况），

并且，使得这支骑士军团最具有战斗力。

为了描述战斗力，我们将骑士按照 1 至 n 编号，

给每名骑士一个战斗力的估计，一个军团的战斗力为所有骑士的战斗力总和。
*/

int fa[N],val[N],vis[N],isc[N];
ll dp[N][2],f[N][2];
VI e[N];

void dfs(int u){
    dp[u][1]=val[u];
    for(auto v:e[u]){
        if(isc[v]) continue;
        vis[v]=1;
        dfs(v);
        dp[u][1]+=dp[v][0];
        dp[u][0]+=max(dp[v][0],dp[v][1]);
    }
}
  
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
    int n;
    cin>>n;
    rep(i,1,1+n){
        cin>>val[i]>>fa[i];
        e[fa[i]].pb(i);
    }
    ll ans=0;
    rep(i,1,1+n) if(!vis[i]){
        int x=i;
        while(!vis[x]){
            vis[x]=1;
            x=fa[x];
        }
        int u=x;
        VI cyc;
        while(1){
            cyc.pb(x);
            isc[x]=1;
            x=fa[x];
            if(x==u) break;
        }
        for(auto cur:cyc){
            dfs(cur);
        }
        int m=SZ(cyc);
        ll res=0;
        rep(i,0,2){
            if(i){
                f[1][0]=-(1<<29);
                f[1][1]=dp[cyc[0]][1];
            }else{
                f[1][0]=dp[cyc[0]][0];
                f[1][1]=-(1<<29);
            }
            rep(j,2,m+1){
                f[j][0]=max(f[j-1][0],f[j-1][1])+dp[cyc[j-1]][0];
                f[j][1]=f[j-1][0]+dp[cyc[j-1]][1];
            }
            if(i) res=max(res,f[m][0]);
            else res=max(f[m][0],f[m][1]);
        }
        ans+=res;
    }
    cout<<ans<<'\n';
    return 0;
} 
