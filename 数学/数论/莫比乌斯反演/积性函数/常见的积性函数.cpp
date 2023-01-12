/*
给一个数字n，求1∼n中的所有数x的d(x),σ(x),φ(x),μ(x)，分别表示因子个数，因子和，欧拉函数，莫比乌斯函数。

为了防止输出过大和防止打表，给定a,b，输出每个函数f，分别求出(a⋅x⋅f(x)+b) mod 2^32的异或和。对于莫比乌斯函数，按照无符号整型处理。
*/

int cnt = 0;
int pr[N],p[N],pe[N];//p[i]最小素数因子 pe[i]最小素数因子的多少次2^5=32
int n;
ui a,b,f[N];

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
	ui ans=0;
	f[1]=1;
	for(int i=2;i<=n;++i){
		if(pe[i]==i) upd(i);
		else f[i]=f[i/pe[i]]*f[pe[i]];
	}
	for(ui i=1;i<=n;++i) ans^=a*i*f[i]+b;
	printf("%u\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%u%u",&n,&a,&b);
	getp(n);
	//for(int i=1;i<=100;++i) cout<<p[i]<<" "<<pe[i]<<endl;
	F([&](int x){
		f[x]=f[x/p[x]]+1;
	});

	F([&](int x){
		f[x]=f[x/p[x]]+x;
	});

	F([&](int x){
		f[x]=x/p[x]*(p[x]-1);
	});

	F([&](int x){
		f[x]=x==p[x]?-1:0;
	});
    return 0;
} 