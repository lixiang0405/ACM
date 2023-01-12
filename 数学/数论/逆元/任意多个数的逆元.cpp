/*给一个素数 p，求a1,a2,…,an关于p的逆元。

由于输出可能很大，只需要求这些逆元的异或和即可。*/

unsigned int A, B, C;
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

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

const int N=1e7+10;
int p,n;
ll s[N],t[N],a[N];

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	scanf("%d%d%u%u%u", &p, &n, &A, &B, &C);
    for (int i = 1; i <= n; i++)
        a[i] = rng61()%p;
	int ans=0;
	s[0]=1;
	for(int i=1;i<=n;++i){
		if(!a[i]){
			a[i]=1;
			ans^=1;
		}
		s[i]=s[i-1]*a[i]%p;
	}
	ll x,y;
	exgcd(s[n],p,x,y);
	if(x<0) x+=p;
	t[n]=x;
	//t[n]=qp(s[n],p-2,p);
	for(int i=n;i>=1;--i) t[i-1]=t[i]*a[i]%p;
	for(int i=1;i<=n;++i){
		ll res=s[i-1]*t[i]%p;
		ans^=res;
	}
	printf("%d",ans);
	return 0;
} 