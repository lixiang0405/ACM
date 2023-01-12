/*
回答T组询问，每次给一个素数p，输出它最小的原根g。
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

int t;
int primes[1010],cnt=0;

int solve(){
	int p,m;
	scanf("%d",&p);
	cnt=0;
	m=p-1;
	for(int i=2;i*i<=m;++i){
		if(m%i==0){
			primes[cnt++]=i;
			while(m%i==0) m/=i;
		}
	}
	for(int i=1;i<p;++i){
		bool flag=true;
		for(int j=0;j<cnt;++j)
			if((p-1)%primes[j]==0&&qp(i,(p-1)/primes[j],p)==1){
				flag=false;
				break;
			} 
		if(flag) return i;
	}
	return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&t);
    while(t--){
        printf("%d\n",solve());
    }
	return 0;
} 