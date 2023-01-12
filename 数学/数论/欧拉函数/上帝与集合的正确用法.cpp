/*
给定一个数字p，求
2^(2^(2^(2....)))mod p
*/

int t,p;

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}
// 2^x % p=2^(x%phip+phip) % p x->2^2^2^2^2^2...
// =2^((2^y)%phip+phip) % p
int calc(int u){
	if(u==1) return 0;
	int res=u,p=u;//注意u会被更改
	for(ll i=2;i<=u/i;++i){
		if(u%i==0){
			while(u%i==0) u/=i;
			res=res/i*(i-1);
		}
	}
	if(u>1) res=res/u*(u-1);
	return qp(2,calc(res)+res,p);//calc(res) 为%res之后的数
}

void solve(){
	scanf("%d",&p);
	printf("%d\n",calc(p));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&t);
   	while(t--){
		solve();
	}
	return 0;
}