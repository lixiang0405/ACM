/*有一个包含N行和N列的网格。
每个网格有一个数aij,从(1,1)出发走到(n,n)的所有路径里
aij异或和等于0的路径个数
2≤N≤20
*/

int g[N][N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	rep(i,1,1+n){
		rep(j,1,1+n) cin>>g[i][j];
	}
	map<int,map<int,ll>> mp,pm;
	mp[n+1][g[1][1]]=1;
	rep(i,1,1+n) rep(j,1,1+n){
		if(i+j-1<=n){
			if(i>1){
				for(auto [x,y]:mp[(i-1)*n+j]){
					mp[i*n+j][x^g[i][j]]+=y;
				}
			}
			if(j>1){
				for(auto [x,y]:mp[i*n+j-1]){
					mp[i*n+j][x^g[i][j]]+=y;
				}
			}
		}
	}
	pm[n*n+n][g[n][n]]=1;
	ll ans=0;
	per(i,1,1+n) per(j,1,1+n){
		if(i+j-1>=n){
			if(i!=n){
				for(auto [x,y]:pm[(i+1)*n+j]){
					pm[i*n+j][x^g[i][j]]+=y;
				}
			}
			if(j!=n){
				for(auto [x,y]:pm[i*n+j+1]){
					pm[i*n+j][x^g[i][j]]+=y;
				}
			}
		}
		if(i+j-1==n){
			for(auto [x,y]:pm[i*n+j]){
				ans+=y*mp[i*n+j][x^g[i][j]];
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}