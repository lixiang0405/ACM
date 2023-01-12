/*
给定一个函数f(1),f(2),…,f(n)，已知f(n)=∑(d|n) g(d)，求g(1),g(2),…,g(n)。
*/

int cnt = 0;
int pr[N],p[N],pe[N];//p[i]最小素数因子 p[i]最小素数因子的多少次2^5=32
int n;
ui a,b,f[N],u[N],g[N];

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

void F(function<void(int)> upd){
	u[1]=1;
	for(int i=2;i<=n;++i){
		if(pe[i]==i) upd(i);
		else u[i]=u[i/pe[i]]*u[pe[i]];
	}
}

unsigned int A,B,C;
inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%u%u%u", &n, &A, &B, &C);
    for (int i = 1; i <= n; i++)
        f[i] = rng61();
	getp(n);
	//for(int i=1;i<=100;++i) cout<<p[i]<<" "<<pe[i]<<endl;
	F([&](int x){
		u[x]=x==p[x]?-1:0;
	});
	// g(n)=∑(u(d1)*f(d2)) d1*d2=n
	for(int d1=1;d1<=n;++d1)
		for(int d2=1;d2*d1<=n;++d2)
			g[d1*d2]+=u[d1]*f[d2];
	ui ans=0; 
	for(int i=1;i<=n;++i) ans^=g[i];
	printf("%u",ans);
    return 0;
} 