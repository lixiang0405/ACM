/*有一棵 n 个点的树，请求出经过每个点的长度最长的简单路径有多长。

定义一条路径的长度为这条路径上经过了多少条边。*/

int n,fa[N];
vector<int> e[N];
int dp[N],dp2[N],ans[N];

int dfs(int u){
	int cnt=0;
	for(auto v:e[u]){
		if(v==fa[u]) continue;
		fa[v]=u;
		cnt=max(dfs(v),cnt);
	}
	return (dp[u]=cnt)+1;
}

void dfs2(int u){
	int m=e[u].size(),fi,se,maxx=0;//找出儿子里面dp值前两大的id
	if(m==1) return;
	if(m==2){
		for(auto v:e[u]){
			if(v==fa[u]) continue;
			fi=se=v;
		}
	}else{
		for(auto v:e[u]){
			if(v==fa[u]) continue;
			maxx=max(dp[v],maxx);
			fi=se=v;
		}
		for(auto v:e[u]){
			if(v==fa[u]) continue;
			if(dp[v]!=maxx){
				fi=v,se=v;
			}
		}
		for(auto v:e[u]){
			if(v==fa[u]) continue;
			if(dp[fi]<dp[v]) fi=v;
		}
		for(auto v:e[u]){
			if(v==fa[u]||fi==v) continue;
			if(dp[se]<=dp[v]) se=v;
		}
	}
    for(int i=1;i<=m;++i){
		auto v=e[u][i-1];
		if(v==fa[u]) continue;
		if(v==fi){
			if(fi!=se)
			dp2[v]=dp[se]+2,ans[u]=max(ans[u],dp[se]+dp[fi]+2);
			else dp2[v]=1;
		}
		else dp2[v]=dp[u]+1,ans[u]=max(ans[u],dp[se]+dp[fi]+2);//上面算出答案的ans缺少由它两个儿子组成路径的情况
        if(u!=1) dp2[v]=max(dp2[u]+1,dp2[v]);
    }//dp2[v]表示以v点为根把树倒过来
    for(auto v:e[u]){
		if(v==fa[u]) continue;
        ans[v]=dp[v]+dp2[v];
        dfs2(v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		int u,v,w;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	e[1].push_back(0);
	fa[1]=0;
	dfs(1);
	dfs2(1);
	if(e[1].size()==2){
		ans[1]=dp[1];
	}else{
		int fi,se,maxx;
		for(auto v:e[1]){
			if(v==0) continue;
			maxx=max(dp[v],maxx);
			fi=se=v;
		}
		for(auto v:e[1]){
			if(v==0) continue;
			if(dp[v]!=maxx) fi=se=v; 
		}
		for(auto v:e[1]){
			if(v==0) continue;
			if(dp[fi]<dp[v]) fi=v;
		}
		for(auto v:e[1]){
			if(v==0||fi==v) continue;
			if(dp[se]<=dp[v]) se=v;
		}
		ans[1]=dp[fi]+dp[se]+2;
	}
	
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]);
    return 0;
}