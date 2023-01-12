//给一个 n 个点 m 条边的图，每条边都是无向，求这个图的生成树个数，对 M 取模。
int mod; 
ll g[N][N];

int calc(int n){
	ll ans=1;
	rep(i,1,1+n) rep(j,1,1+n) g[i][j]%=mod;
	rep(i,1,1+n){
		rep(j,i+1,1+n){
			//消掉g[j][i]
			int x=i,y=j;
			while(g[x][i]){
				int t=g[y][i]/g[x][i];
				rep(k,i,1+n) 
					g[y][k]=(g[y][k]-t*g[x][k])%mod;
				swap(x,y);
			}
			//g[x][i]=0
			if(x==i){
				rep(k,i,1+n) swap(g[x][k],g[y][k]);
				ans=-ans;
			}
		}
		ans=ans*g[i][i]%mod;
	}
	if(ans<0) ans+=mod;
	return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
	int n,m;
	scanf("%d%d%d",&n,&m,&mod);
	rep(i,1,1+m){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u][u]++;
		g[v][v]++;
		g[u][v]--;
		g[v][u]--;
	}
	printf("%d",calc(n-1));
	return 0;
} 