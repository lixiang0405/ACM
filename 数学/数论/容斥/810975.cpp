/*
题意:求长度为 n 的 01 串,有 m 个 1,最长 1 连续段长度恰好为 k 的方案数。
先容斥,转化成 ≤ k 的方案数。如果两个连续的 0 视为中间有长度为 0 的 1 连续段
,则相当于一共有 n − m + 1 个 1 连续段,每段长度 ≤ k,长度和为 m 的方案数。
形式化地,设 xi 为第 i 个 1 连续段的长度,
即求:0≤ xi ≤ k 且 sum xi = m的方案数。
这是一个经典问题,容斥枚举有多少个 xi 违反 ≤ k 的限制即可。
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

int n=1e5;
int m,k;

int calc(int num,int sum,int k){
	ll ans=0,f=1;
	rep(i,0,num+1){
		ans=(ans+f*binom(num,i)%mod*binom(sum-(ll)i*k-1,n-m)%mod+mod)%mod;
		f*=-1;
	}
	return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
	cout<<(calc(n-m+1,n+1,k+1)-calc(n-m+1,n+1,k)+mod)%mod<<'\n';
	return 0;
}