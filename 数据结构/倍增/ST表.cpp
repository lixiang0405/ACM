/*给n个数a1,a2,…,an，q个询问。

每个询问给定两个数l,r，求出al,al+1,…,ar中的最大值。*/

int q,n;
unsigned int ans,a[N],f[22][N];
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
int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d%u%u%u", &n, &q, &A, &B, &C);
    for (int i = 1; i <= n; i++) {
        a[i] = rng61();
		f[0][i]=a[i];
    }
	//2^20>=1000000
	for(int i=1;i<=20;++i){
		for(int j=1;j+(1<<i)-1<=n;++j){
			f[i][j]=max(f[i-1][j],f[i-1][j+(1<<(i-1))]);
		}
	}
    for (int i = 1; i <= q; i++) {
        unsigned int l = rng61() % n + 1, r = rng61() % n + 1;
        if (l > r) swap(l, r);
        //int len=__lg(r-l+1);
		//int len=log2(r-l+1);
		int len=31-__builtin_clz(r-l+1);
		ans^=max(f[len][l],f[len][r-(1<<len)+1]);
    }
	printf("%u",ans);
	return 0;
}
