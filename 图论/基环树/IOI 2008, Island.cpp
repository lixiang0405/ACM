/*
你准备浏览一个公园，该公园由 N 个岛屿组成，

当地管理部门从每个岛屿 i 出发向另外一个岛屿建了一座长度为 Li 的桥，

不过桥是可以双向行走的。同时，每对岛屿之间都有一艘专用的往来两岛之间的渡船。

相对于乘船而言，你更喜欢步行。你希望经过的桥的总长度尽可能长，但受到以下的限制：

可以自行挑选一个岛开始游览。任何一个岛都不能游览一次以上。

无论任何时间，你都可以由当前所在的岛 S 去另一个从未到过的岛 D。

从 S 到 D 有如下方法：

步行：仅当两个岛之间有一座桥时才有可能。对于这种情况，

桥的长度会累加到你步行的总距离中。

渡船：你可以选择这种方法，

仅当没有任何桥和以前使用过的渡船的组合可以由 S 走到 D 

(当检查是否可到达时，你应该考虑所有的路径，包括经过你曾游览过的那些岛)。

注意，你不必游览所有的岛，也可能无法走完所有的桥。

请你编写一个程序，给定 N 座桥以及它们的长度，按照上述的规则，

计算你可以走过的桥的长度之和的最大值。
*/

int fa[N],val[N],vis[N],isc[N];
ll dp[N],pre[N],suf[N],s[N*2],maxx;
VI e[N];

void dfs(int u){
    dp[u]=0;
    for(auto v:e[u]){
        if(isc[v]) continue;
        vis[v]=1;
        dfs(v);
        maxx=max(maxx,dp[u]+dp[v]+val[v]);
        dp[u]=max(dp[u],dp[v]+val[v]);
    }
}
  
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
    int n;
    cin>>n;
    rep(i,1,1+n){
        cin>>fa[i]>>val[i];
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
        maxx=0;
        for(auto cur:cyc){
            dfs(cur);
        }
        int m=SZ(cyc);
        rep(j,2,1+2*m) s[j]=s[j-1]+val[cyc[(j-2)%m]];//注意：第一项不能取val
        pre[0]=-inf;
        rep(j,1,1+m) pre[j]=max(pre[j-1],dp[cyc[j-1]]-s[j]);//dp[i]+dp[j]+s[i]-s[j]
        suf[m+1]=-inf;
        per(j,1,1+m) suf[j]=max(suf[j+1],dp[cyc[j-1]]-s[j]);
        rep(j,1,1+m){//由前1-i-1转移或者由后一段n-i转移
            maxx=max({maxx,pre[j-1]+s[j]+dp[cyc[j-1]],s[j+m]+dp[cyc[j-1]]+suf[j+1]});
        }
        //单调队列写法
        // deque<pair<int,ll>> q;
        // rep(j,2,1+2*m){
        //     while(!q.empty()&&j-q.front().fi>=m) q.pop_front();
        //     if(!q.empty())
        //         maxx=max(maxx,s[j]+dp[cyc[(j-1)%m]]+q.front().se);
        //     while(!q.empty()&&q.back().se<dp[cyc[(j-1)%m]]-s[j]) q.pop_back();
        //     q.push_back({j,dp[cyc[(j-1)%m]]-s[j]}); 
        // }
        ans+=maxx;
    }
    cout<<ans<<'\n';
    return 0;
} 
