/*
给你一棵树，边不带权，统计树上距离等于 k 的点对数。
对于 k=1,2,…,n−1 输出答案。
*/

// FFT_MAXN = 2^k 注意N>MAXN
// fft_init() to precalc FFT_MAXN-th roots

typedef long double db;
const int FFT_MAXN=262144;
const db pi=acosl(-1.);
struct cp{
	db a,b;
	cp operator+(const cp&y)const{return (cp){a+y.a,b+y.b};}
	cp operator-(const cp&y)const{return (cp){a-y.a,b-y.b};}
	cp operator*(const cp&y)const{return (cp){a*y.a-b*y.b,a*y.b+b*y.a};}
	cp operator!()const{return (cp){a,-b};};
}nw[FFT_MAXN+1];int bitrev[FFT_MAXN];
void dft(cp*a,int n,int flag=1){
	int d=0;while((1<<d)*n!=FFT_MAXN)d++;
	rep(i,0,n)if(i<(bitrev[i]>>d))swap(a[i],a[bitrev[i]>>d]);
	for (int l=2;l<=n;l<<=1){
		int del=FFT_MAXN/l*flag;
		for (int i=0;i<n;i+=l){
			cp *le=a+i,*ri=a+i+(l>>1),*w=flag==1?nw:nw+FFT_MAXN;
			rep(k,0,l>>1){
				cp ne=*ri**w;
				*ri=*le-ne,*le=*le+ne;
				le++,ri++,w+=del;
			}
		}
	}
	if(flag!=1)rep(i,0,n)a[i].a/=n,a[i].b/=n;
}
void fft_init(){
	int L=0;while((1<<L)!=FFT_MAXN)L++;
	bitrev[0]=0;rep(i,1,FFT_MAXN)bitrev[i]=bitrev[i>>1]>>1|((i&1)<<(L-1));
	nw[0]=nw[FFT_MAXN]=(cp){1,0};
	rep(i,0,FFT_MAXN+1)nw[i]=(cp){cosl(2*pi/FFT_MAXN*i),sinl(2*pi/FFT_MAXN*i)};	//very slow
}

void convo(db*a,int n,db*b,int m,db*c){
	static cp f[FFT_MAXN>>1],g[FFT_MAXN>>1],t[FFT_MAXN>>1];
	int N=2;while(N<=n+m)N<<=1;
	rep(i,0,N)
		if(i&1){
			f[i>>1].b=(i<=n)?a[i]:0.0;
			g[i>>1].b=(i<=m)?b[i]:0.0;
		}else{
			f[i>>1].a=(i<=n)?a[i]:0.0;
			g[i>>1].a=(i<=m)?b[i]:0.0;
		}
	dft(f,N>>1);dft(g,N>>1);
	int del=FFT_MAXN/(N>>1);
	cp qua=(cp){0,0.25},one=(cp){1,0},four=(cp){4,0},*w=nw;
	rep(i,0,N>>1){
		int j=i?(N>>1)-i:0;
		t[i]=(four*!(f[j]*g[j])-(!f[j]-f[i])*(!g[j]-g[i])*(one+*w))*qua;
		w+=del;
	}
	dft(t,N>>1,-1);
	rep(i,0,n+m+1)c[i]=(i&1)?t[i>>1].a:t[i>>1].b;
}

void mul(int *a,int *b,int n){// n<=N, 0<=a[i],b[i]<mod
	static cp f[N],g[N],t[N],r[N];
	int nn=2;while(nn<=n+n)nn<<=1;
	rep(i,0,nn){
		f[i]=(i<=n)?(cp){(db)(a[i]>>15),(db)(a[i]&32767)}:(cp){0,0};
		g[i]=(i<=n)?(cp){(db)(b[i]>>15),(db)(b[i]&32767)}:(cp){0,0};
	}
	swap(n,nn);
	dft(f,n,1);dft(g,n,1);
	rep(i,0,n){
		int j=i?n-i:0;
		t[i]=( (f[i]+!f[j])*(!g[j]-g[i]) + (!f[j]-f[i])*(g[i]+!g[j]) )*(cp){0,0.25};
		r[i]=(!f[j]-f[i])*(!g[j]-g[i])*(cp){-0.25,0} + (cp){0,0.25}*(f[i]+!f[j])*(g[i]+!g[j]);
	}
	dft(t,n,-1); dft(r,n,-1);
	rep(i,0,n)a[i]=( (ll(t[i].a+0.5)%mod<<15) + ll(r[i].a+0.5) + (ll(r[i].b+0.5)%mod<<30) )%mod;
}

vector<int> e[N];
int sz[N],del[N],maxs[N];
ll ans[N];
db f[N],h[N];
int root,maxx;

void dfs1(int u,int fa,int s){
    sz[u]=1;
    maxs[u]=0;
    for(auto v:e[u]){
        if(del[v]||v==fa) continue;
        dfs1(v,u,s);
        sz[u]+=sz[v];
        maxs[u]=max(maxs[u],sz[v]);
    }
    maxs[u]=max(maxs[u],s-sz[u]);
    if(maxs[u]<maxx){
        maxx=maxs[u];
        root=u;
    }
}

void dfs(int u,int s){
    maxx=s+1;
    dfs1(u,0,s);
    del[root]=1;
    VI vt1,vt2;
	auto calc=[&](VI &vt,int ty){
		int m=*max_element(all(vt));
		rep(i,0,1+m) f[i]=0;
		rep(i,0,2*m+1) h[i]=0;
		for(auto cur:vt) f[cur]++;
		convo(f,m,f,m,h);
		rep(i,0,2*m+1) ans[i]+=(ll)(h[i]+0.5)*ty;
	};
	vt1.pb(0);
    for(auto x:e[root]){
        if(del[x]) continue;
        vt2.clear();
        function<void(int,int,int)> dfs2=[&](int x,int fa,int val){
            sz[x]=1;
			vt2.pb(val);
			vt1.pb(val);
		    for(auto v:e[x]){
                if(v==fa||del[v]) continue;
                dfs2(v,x,val+1);
                sz[x]+=sz[v];
            }
        };
		dfs2(x,root,1);
     	calc(vt2,-1);
    }
	calc(vt1,1);
    for(auto x:e[root]){
        if(del[x]) continue;
        dfs(x,sz[x]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	fft_init();
    int n;
    scanf("%d",&n);
    rep(i,1,n){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs(1,n);
	rep(i,1,n){
		printf("%lld\n",ans[i]/2);
	}
	return 0;
}