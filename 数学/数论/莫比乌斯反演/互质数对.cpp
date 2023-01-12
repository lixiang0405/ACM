/*
T组询问，每次给两个数n,m，求有多少对(i,j)满足1≤ i ≤n,1≤ j ≤m并且i,j互质。
*/

int cnt = 0;
int pr[N],p[N],pe[N];//p[i]最小素数因子 pe[i]最小素数因子的多少次2^5=32
int u[N];
ll sum[N];

void getp(int x) {
	p[1]=1;
	for (int i = 2; i <= x ; ++i) {
		if (!p[i]) pr[cnt++] = i, pe[i] = i, p[i] = i;
		for (int j = 0; j < cnt && pr[j] * i <= x; ++j) {
			p[i * pr[j]] = pr[j];
			if(p[i] == pr[j]){
				pe[i * pr[j]] = pe[i] * pr[j];
				break;
			}else{
				pe[i * pr[j]] = pr[j];
			}
		}
	}
}

void F(int n,function<void(int)> upd){
	u[1]=1;
	for(int i=2;i<=n;++i){
		if(pe[i]==i) upd(i);
		else u[i]=u[i/pe[i]]*u[pe[i]];
	}
}
//e(n)=[n=1] e=1*u sum(e((i,j))) = sum(u((i,j))) (i,j)|n =sum_{1<=d<=n} u(d)*sum_{1<=i<=n,1<=j<=m}(1) =sum_{1<=d<=n} u(d)*n/d*m/d  n/d和m/d在l-r区间内不变 d在l-r
void solve(){
	int n,m;
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	ll ans=0;
	for(int l=1;l<=n;++l){
		int d1=n/l,d2=m/l;
		int r=min(n/d1,m/d2);//d1和d2再l到r之间都不会变
		ans+=(sum[r]-sum[l-1])*d1*d2;
		l=r;
	}
	printf("%lld\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	scanf("%d",&t);
	getp((int)1e7);
	F((int)1e7,[&](int x){
		u[x]=x==p[x]?-1:0;
	});
	for(int i=1;i<=(int)1e7;++i) sum[i]=sum[i-1]+u[i];
	while(t--){
		solve();
	}
    return 0;
} 