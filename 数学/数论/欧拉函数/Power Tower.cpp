/*
有n个数a1,a2,…,an，q组询问。每次给一段区间[l,r]，你要计算al^(al+1^(al+2^(....^ar)))mod m。
*/
int n,m,a[N],t,p[N];

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

ll phi(ll u){
	ll res=u;
	for(ll i=2;i<=u/i;++i){
		if(u%i==0){
			while(u%i==0) u/=i;
			res=res/i*(i-1);
		}
	}
	if(u>1) res=res/u*(u-1);
	return res;
}
// 返回 al^(...) % p[x]
int solve(int l,int r,int x){
	//return (a[l]^f%p[x]+p[x]) -> (b%φ(m)+φ(m))  a^(b%φ(m)+φ(m)) %m
	if(l==r) return a[l];
	if(p[x]==1) return 1;
	int f=solve(l+1,r,x+1);
	int ans=qp(a[l],f,p[x]);
	bool flag=false;
	//判断ans是否真的大于p[x],大于则不变，小于则 +p[x] 
	if(a[l]!=1){
		if(f>=30) flag=true;
		else if(pow(a[l],f)>=1e9) flag=true;
		else{
			if(qp(a[l],f,mod)>=p[x]) flag=true;
		}
	}
	if(flag) ans+=p[x];
	return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	p[t++]=m;
	while(p[t-1]!=1){
		p[t++]=phi(p[t-1]);
	}
   	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	int q;
	scanf("%d",&q);
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",solve(l,r,0)%m);
	}
	return 0;
}