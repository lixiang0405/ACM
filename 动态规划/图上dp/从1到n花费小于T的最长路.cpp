/*
最近，伊琳娜来到了贝兰最著名的城市之一——贝拉托夫市。
城内有n个景点，从1到n编号，有的由单向道路相连。
Berlatov 的道路的设计方式使得表演场所之间没有循环路线。
伊琳娜最初站在showplace 1，她的旅程的终点​​是showplace n。
自然，伊琳娜想在旅途中尽可能多地参观表演场所。
但是，Irina 在 Berlatov 的停留时间是有限的，她在此停留的时间不能超过 T 个时间单位。
帮助 Irina 确定她在不超过 T 的时间内从 showplace 1 到 showplace n 的旅程中可以参观多少个 showplace。 保证从 showplace 1 到 showplace n 至少有一条路线，这样 Irina 将花费不超过 T
通过它的时间单位。
*/

int n,m,T;
int dp[N][N],pre[N][N];
array<int,3> e[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d%d",&n,&m,&T);
	for(int i=1;i<=n;++i){
		for(int j=0;j<=n;++j) 
			dp[i][j]=T+1;
	}
	dp[1][0]=0;
	for(int i=1;i<=m;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[i]={u,v,w};
	}
	//从1出发走到i步的最小时间
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			auto [u,v,w]=e[j];
			if(dp[v][i]>dp[u][i-1]+w){
				dp[v][i]=dp[u][i-1]+w;
				pre[v][i]=u;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i)
		if(dp[n][i]<=T) ans=i;
 	printf("%d\n",ans+1);
	int x=n;
	vector<int> path;
	while(1){
		path.push_back(x);
		x=pre[x][ans];
		ans--;
		if(x==1) break;
	}
	path.push_back(1);
	reverse(path.begin(),path.end());
	for(auto cur:path) printf("%d ",cur);
	return 0;
}