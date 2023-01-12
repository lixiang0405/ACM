/*
求有多少个不同的数组A
1.∑{i=1到k}∑{j=1到i−1} ai⊕aj = n
2.长度为k
3.0=<ai<=m
*/
ll n,m,k;
 
map<ll,ll> dp[100][20];
 
ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}
 
ll fac[N],fnv[N];//fnv逆元
 
ll binom(int n,int m){
	if(n<0||m<0||n<m) return 0;
	return fac[n]*fnv[m]%mod*fnv[n-m]%mod;
}
 
ll dfs(int x,int limit,ll last){//取到第x位，k个数有limit个抵住上限，为了合成n还要limit
	//cout<<x<<" "<<limit<<" "<<last<<endl;
	if(x==-1){
		if(last==0){
			return 1;
		}
		else return 0;
	}
	if(81LL*((1LL<<(x+1))-1)<last) return 0;
	if(dp[x][limit].count(last)) return dp[x][limit][last];
	auto &ans=dp[x][limit][last];
	ans=0;
	if(m&(1LL<<x)){
		rep(i,0,k+1){//枚举有多少个1
			ll l=last-(ll)i*(k-i)*(1LL<<x);
			if(l<0) continue;
			rep(j,0,min(i,limit)+1){//枚举受限制的有多少个1
				ans=(ans+dfs(x-1,j,l)*binom(limit,j)%mod*binom(k-limit,i-j)%mod)%mod;
			}
		}
	}else{
		rep(i,0,k-limit+1){//枚举有多少个1
			ll l=last-(ll)i*(k-i)*(1LL<<x);
			if(l<0) continue;
			ans=(ans+binom(k-limit,i)*dfs(x-1,limit,l)%mod)%mod;
		}
	}
	return ans;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	n=20;
	fac[0]=1;
	for(int i=1;i<=n;++i){
		fac[i]=fac[i-1]*i%mod;
	}
	fnv[n]=qp(fac[n],mod-2,mod);
	for(int i=n;i>=1;--i){
		fnv[i-1]=fnv[i]*i%mod;
	}
	assert(fnv[0]==1);
	cin>>n>>m>>k;
	int x=63-__builtin_clzll(m);
	if(m==0)
		x=0;
	cout<<dfs(x,k,n)<<'\n';
	return 0;
}