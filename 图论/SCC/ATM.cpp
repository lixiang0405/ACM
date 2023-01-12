/*
Siruseri城中的道路都是单向的。不同的道路由路口连接。

按照法律的规定，在每个路口都设立了一个 Siruseri 银行的 ATM 取款机。

令人奇怪的是，Siruseri 的酒吧也都设在路口，虽然并不是每个路口都设有酒吧。

Banditji 计划实施 Siruseri 有史以来最惊天动地的 ATM 抢劫。

他将从市中心出发，沿着单向道路行驶，抢劫所有他途径的 ATM 机，最终他将在一个酒吧庆祝他的胜利。

使用高超的黑客技术，他获知了每个 ATM 机中可以掠取的现金数额。

他希望你帮助他计算从市中心出发最后到达某个酒吧时最多能抢劫的现金总数。

他可以经过同一路口或道路任意多次。但只要他抢劫过某个 ATM 机后，该 ATM 机里面就不会再有钱了。

问最多能抢劫的现金总数。
*/

const int N = 5e5+5;

int n,m,cnt=0,tot=0;
int dfn[N],low[N],bel[N],ins[N],bar[N],val[N];
ll dp[N];
stack<int> sk;
vector<int> e[N];

void dfs(int u){
	dfn[u]=low[u]=++tot;
	sk.push(u);
	ins[u]=1;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else 
			if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		dp[cnt]=-inf;
		bool hbar=false;
		ll hval=0;
		while(1){
			int x=sk.top();
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			for(auto y:e[x]){
				//从其他连通块转移过来
				if(bel[y]!=cnt&&bel[y]!=0){
					//注意，if完之后一定执行下一个if
					if(dp[bel[y]]>dp[cnt]) dp[cnt]=dp[bel[y]];
				}
			}
			hval+=val[x];
			hbar|=bar[x];
			if(x==u) break;
		}
		if(hbar) dp[cnt]=max(dp[cnt],0LL);
		dp[cnt]+=hval;
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	for(int i=1;i<=n;++i) scanf("%d",&val[i]);
	int s,p;
	scanf("%d%d",&s,&p);
	for(int i=1;i<=p;++i){
		int x;
		scanf("%d",&x);
		bar[x]=1;
	}
	dfs(s);
	printf("%d",dp[bel[s]]);
    return 0;
}