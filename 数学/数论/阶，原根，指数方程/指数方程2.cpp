//回答T组询问，每次给一个数a,b,m，输出最小的非负整数x满足a^x ≡ b(mod m合数)。

struct Hash_table{
    static const int V=1000003;
    int fst[V],nxt[V],ptm[V];
    int ctm,T;
    int val[V];
    ll key[V];

    void init(){
        T=0;
        ctm++;
    }

    void insert(ll s,int v){
        int S=s%V;
        if(ptm[S]!=ctm) ptm[S]=ctm,fst[S]=-1;
        for(int j=fst[S];j!=-1;j=nxt[j])
            if(key[j]==s) return;
        nxt[T]=fst[S];
        fst[S]=T;
        key[T]=s;
        val[T]=v;
        T++;
    }

    int query(ll s){
        int S=s%V;
        if(ptm[S]!=ctm) return -1;
        for(int j=fst[S];j!=-1;j=nxt[j])
            if(key[j]==s) return val[j];
        return -1;
    }
}hs;

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

//(a^T)^q ≡ b*a^(r) (mod m)
int BSGS(int a,int b,int m){
	hs.init();
	ll T=sqrt(m)+2;
	ll v=qp(a,T,m),d=1;
	for(int q=1;q<=T;++q){
		d=d*v%m;
		if(hs.query(d)==-1) hs.insert(d,q*T);
	}
	d=b;
	int ans=m+1;
	for(int r=1;r<=T;++r){
		d=d*a%m;
		if(hs.query(d)!=-1) ans=min(ans,hs.query(d)-r);
	}
	if(ans>=m){
		return -1;
	}else return ans;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
} 
//v*?=d(mod m)
//v?+bm=d
ll get(ll a,ll b,ll c){
	ll x,y;
	int d=exgcd(a,b,x,y);
	if(c%d!=0){
		return -1;
	}
	c/=d;
	a/=d;
	b/=d;
	// ax+by=c
	ll tmp=x*(c%b)%b; //c%b怕爆long long
	if(tmp<0) tmp+=b;
	y=(c-a*tmp)/b;
	// if(y<0){
	// 	return -1;
	// }
	return tmp;
}

ll gcd(ll x,ll y){
    return y==0?x:gcd(y,x%y);
}

int t;

void solve(){
	int a,b,m;
	scanf("%d%d%d",&a,&b,&m);
	ll v=1;
	for(int i=0;i<30;++i){
		if(v==b){
			printf("%d\n",i);
			return;
		}
		v=v*a%m;
	}
	//v*a^(x-30)=b(mod m)
	ll g=gcd(v,m);
	if(b%g){
		printf("-1\n");
		return;
	}
	b/=g,m/=g;
	b=get(v/g,m,b);
	int ans=BSGS(a,b,m);
	if(ans==-1){
		printf("-1\n");
		return;
	}else{
		printf("%d\n",ans+30);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
    return 0;
} 