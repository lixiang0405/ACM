/*
给定素数p，回答T个询问。给定一个a，问最小的正数x满足a^x ≡ 1(mod p)。
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

int t,p,m;
int primes[1010],cnt=0;

void solve(){
	int a;
	scanf("%d",&a);
	int ans=p-1;
	for(int i=0;i<cnt;++i)
		while(ans%primes[i]==0&&qp(a,ans/primes[i],p)==1) 
			ans/=primes[i];
	printf("%d\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&p,&t);
	m=p-1;
	for(int i=2;i*i<=m;++i){
		if(m%i==0){
			primes[cnt++]=i;
			while(m%i==0) m/=i;
		}
	}
	if(m>1) primes[cnt++]=m;
    while(t--){
        solve();
    }
	return 0;
} 