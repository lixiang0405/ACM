/*
101010011111 是0必须取0，是1可以取0或1
给一个长度为2n的数组f0,f1,…,f2n−1。
求g0,g1,…,g2n−1，满足
gi=∑（i&j=j）fj
*/

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

ll g[N],f[N],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%u%u%u", &n, &A, &B, &C);
    for (int i = 0; i < (1 << n); i++)
        g[i] = rng61();
	/*枚举子集合O(3^n)
	for(int i=0;i<(1<<n);++i){
		int j=i;
		while(1){
			g[i]+=f[j];
			if(j==0) break;
			j=(j-1)&i;
		}
	}*/
	//高维前缀和O(n*2^n) g[1100]=f[1][1][0][0]求子集和就是求 第一维前缀和f[?][?][?][0]
	//,第二维前缀和f[?][?][0][0],第三维前缀和f[?][1][0][0]=f[?][0][0][0]+f[?][1][0][0]
	//第四维前缀和f[1][1][0][0]=f[0][1][0][0]+f[1][1][0][0]->前三维的前缀和
	ll ans=0;
	for(int i=0;i<n;++i){
		for(int j=0;j<(1<<n);++j){
			if(j&(1<<i)) g[j]+=g[j-(1<<i)];
		}
	}
	for(int i=0;i<(1<<n);++i){
		ans^=g[i];
	}
	printf("%lld",ans);
    return 0;
}