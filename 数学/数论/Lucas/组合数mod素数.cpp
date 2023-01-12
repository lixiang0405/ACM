/*
给定一个素数p。回答T组询问，输出(nm) mod p的值。
对于所有数据，保证1≤T≤105,1≤m≤n≤1018,2≤p≤106，其中p是素数。
*/

int t,d;

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
	return fac[n]*fnv[m]%d*fnv[n-m]%d;
}

void solve(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	ll ans=1;
	while(n||m){
		ans=ans*binom(n%d,m%d)%d;
		n/=d;
		m/=d;
	}
	printf("%lld\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&d,&t);
	int n=d-1;//不能超过mod的数
	fac[0]=1;
	for(int i=1;i<=n;++i){
		fac[i]=fac[i-1]*i%d;
	}
	fnv[n]=qp(fac[n],d-2,d);
	for(int i=n;i>=1;--i){
		fnv[i-1]=fnv[i]*i%d;
	}
	assert(fnv[0]==1);
	while(t--){
		solve();
	}
    return 0;
}