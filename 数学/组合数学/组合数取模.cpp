/*
回答T组询问，输出Cnm mod 109 + 7的值。
*/

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

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n=1e7;
	fac[0]=1;
	for(int i=1;i<=n;++i){
		fac[i]=fac[i-1]*i%mod;
	}
	fnv[n]=qp(fac[n],mod-2,mod);
	for(int i=n;i>=1;--i){
		fnv[i-1]=fnv[i]*i%mod;
	}
	assert(fnv[0]==1);
	int t;
	scanf("%d",&t);
	while(t--){
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%lld\n",binom(a,b));
	}
	return 0;
} 