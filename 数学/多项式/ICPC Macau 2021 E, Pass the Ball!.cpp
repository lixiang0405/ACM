/*
有n个孩子玩n个球。孩子和球的编号均为 1 到 n。
在游戏之前，给出 n 个整数 p1，p2,...,pn。
在每一轮比赛中，孩子i将把他拥有的球传给孩子pi。
保证没有孩子会把他的球传给自己，
这意味着pi≠i。此外，我们也知道，每回合结束后，每个孩子都会只握住一个球。
令bi为孩子i拥有的球。
在游戏开始时，孩子 i（1≤i≤n） 将携带球 i，这意味着 bi=i 最初。
系统会要求您处理 q 查询。对于每个查询，您都会得到一个整数 k，您需要在 k 轮后计算 P=∑{i=1——n} i⋅bi 的值。
*/

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

int n,q,p[N],vis[N];
ll h[N];
db f[N],g[N],t[N];
set<int> c;
vector<ll> ans[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	fft_init();
	scanf("%d%d",&n,&q);
    rep(i,1,1+n) scanf("%d",&p[i]);
 	rep(i,1,1+n){
        if(!vis[i]){
            int u=i;
            VI cyc;
            while(!vis[u]){
                vis[u]=1;
                cyc.pb(u);
                u=p[u];
            }
            int m=SZ(cyc);
            rep(i,0,m) h[i]=0,f[i]=cyc[i],g[i]=cyc[(m-i)%m];
            convo(f,m-1,g,m-1,t);
            rep(i,0,2*m-1) h[i%m]+=(ll)(t[i]+0.5);
            if(!c.count(m)){
                c.insert(m);
                ans[m].resize(m);
            }
            rep(i,0,m)
                ans[m][i]+=h[i];
        }
    }
    while(q--){
        int x;
        scanf("%d",&x);
        ll res=0;
        for(auto cur:c){
            res+=ans[cur][x%cur];
        }
        printf("%lld\n",res);
    }
    return 0;
}