/*给你一个序列a1,a2,…,an，一开始都是0。

你需要支持q个操作：

1 x y d，对数组中所有下标i≡y(modx)的位置加上d。

2 x，单点询问ax的值。*/

ll val[N],tag[M+5][M+5];
int n,q;
int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&q);
	//int m=(int)sqrt(n);
	for(int i=0;i<q;++i){
		int ty,x;
		scanf("%d%d",&ty,&x);
		if(ty==1){
			int y;
			ll d;
			scanf("%d%lld",&y,&d);
			if(x<=M){
				tag[x][y]+=d;
			}else{
				for(int j=y;j<=n;j+=x){
					val[j]+=d;
				}
			}
		}else{
			ll ans=val[x];
			for(int j=1;j<=M;++j){
				ans+=tag[j][x%j];
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
