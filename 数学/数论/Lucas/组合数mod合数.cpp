/*
给定一个q。回答T组询问，输出(nm) mod q的值。
对于所有数据，保证1≤T≤105,1≤m≤n≤1018,2≤q≤106。
*/

int m,T,M,phipe;
pair<int,int> x[110];
ll pr[110];
ll ans[N],a[N],b[N],fac[N*10],cntp,cnts;

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

ll calc(ll a,ll p,ll pe,ll w){
	ll val=1;
	while(a){
		cntp+=(a/p)*w;
		cnts+=(a/pe)*w;
		val=val*fac[a%pe]%pe;
		a/=p;
	}
	return val;
}

ll binom(ll a,ll b,int p,int pe){
	cntp=cnts=0;
	ll f1=calc(a,p,pe,1);
	ll f2=calc(b,p,pe,-1);
	ll f3=calc(a-b,p,pe,-1);
	ll v1=f1*qp(f2*f3%pe,phipe-1,pe)%pe;
	ll v2=qp(p,cntp,pe);
	ll v3=qp(fac[pe],cnts,pe);
	return v1*v2%pe*v3%pe;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&m,&T);
	M=m;
	int t=0;
	for(int i=2;i<=m;++i) 
		if(m%i==0){
			int p=i,pe=1;
			while(m%i==0) m/=i,pe*=i;
			x[t++]={p,pe};
		}
	for(int i=0;i<t;++i){//xi % mi=1   xi % M/mi=0解出一组xi
		int pe=x[i].second;
		int Mi=M/pe;
		for(int c=0;c<M;c+=Mi){
			if(c%pe==1){
				pr[i]=c;
				break;
			}
		}
	}
	for(int i=0;i<T;++i){
		scanf("%lld%lld",&a[i],&b[i]);
	}
	for(int i=0;i<t;++i){
		int p=x[i].first,pe=x[i].second;
		fac[0]=1;
		for(int j=1;j<=pe;++j){
			if(j%p==0) fac[j]=fac[j-1];
			else fac[j]=fac[j-1]*j%pe;
		}
		phipe=pe/p*(p-1);
		for(int j=0;j<T;++j){
			ans[j]=(ans[j]+binom(a[j],b[j],p,pe)*pr[i])%M;
		}
	}
	for(int i=0;i<T;++i) printf("%lld\n",ans[i]);
    return 0;
}