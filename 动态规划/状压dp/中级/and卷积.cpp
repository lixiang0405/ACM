/*
给两个长度为2n的数组f0,f1,…,f2n−1,g0,g1,…,g2n−1。

求h0,h1,…,h2n−1，满足
hi = (∑(j&k=i) fj ⋅ gk )mod 1e+7
*/

ll f[N+10],g[N+10];
int n;

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%u%u%u", &n, &A, &B, &C);
    for (int i = 0; i < (1 << n); i++)
        f[i] = rng61();
    for (int i = 0; i < (1 << n); i++)
        g[i] = rng61();
	for(int i=0;i<n;++i){
		for(int j=0;j<(1<<n);++j){
			if(!(j&(1<<i))) f[j]=(f[j]+f[j+(1<<i)]);
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<(1<<n);++j){
			if(!(j&(1<<i))) g[j]=(g[j]+g[j+(1<<i)]);
		}
	}
	for(int i=0;i<(1<<n);++i){
		f[i]%=mod;
		g[i]%=mod;
		f[i]=f[i]*g[i]%mod;
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<(1<<n);++j){
			if(!(j&(1<<i))) f[j]-=f[j+(1<<i)];
		}
	}
	for(int i=0;i<(1<<n);++i) {
		f[i]%=mod;
		if(f[i]<0) f[i]+=mod;
	}
	int ans=0;
	for(int i=0;i<(1<<n);++i) ans^=f[i];
	printf("%d",ans);
	return 0;
}