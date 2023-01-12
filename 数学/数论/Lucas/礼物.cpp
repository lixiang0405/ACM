/*
一年一度的圣诞节快要来到了。每年的圣诞节小E都会收到许多礼物，

当然他也会送出许多礼物。不同的人物在小E心目中的重要性不同，

在小E心中分量越重的人，收到的礼物会越多。

小E从商店中购买了n件礼物，打算送给m个人，其中送给第i个人礼物数量为wi。

请你帮忙计算出送礼物的方案数（两个方案被认为是不同的，

当且仅当存在某个人在这两种方案中收到的礼物不同）。

由于方案数可能会很大，你只需要输出模P后的结果。

(w1,n)*(w2,n-w1)*(w3,n-w1-w2)......(wn,n-w1-w2-w3..-wn-1)
*/

int m,T,M,phipe,mod,n;
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
	scanf("%d",&mod);
	scanf("%d%d",&n,&T);
	m=M=mod;
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
		int x;
		scanf("%d",&x);
		a[i]=n,b[i]=x;
		n-=x;
	}
	if(n<0){
		printf("Impossible");
		return 0;
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
	ll res=1;
	for(int i=0;i<T;++i) res=res*ans[i]%M;
	printf("%lld",res);
    return 0;
}