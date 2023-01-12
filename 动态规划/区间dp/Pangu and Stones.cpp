/*在中国神话中，盘古是第一个生物，是天地的创造者。
他从一个鸡蛋中醒来，把鸡蛋分成两部分：天空和大地。
起初，大地没有山，满地都是石头。
有N堆石头，编号从1到N。
盘古想把它们合二为一，建造一座大山。
如果有几堆石子的总和是S，盘古需要S秒才能把它们堆成一堆，新堆里会有S石子。
可惜，每次盘古只能将接连的一堆堆合为一堆。
并且他合并的桩数不应该小于L或大于R。
盘古想尽快完成这件事。
你能帮助他吗？
如果没有解决方案，您应该回答 0。
*/

int t,n,L,R,a[N],dp[N][N][N],tot[N];

void solve(){
	for(int i=1;i<=n;++i) scanf("%d",a+i),tot[i]=tot[i-1]+a[i];	
	for(int l=1;l<=n;++l){
		for(int r=l;r<=n;++r){
			for(int k=1;k<=n;++k) dp[l][r][k]=inf;
		}
	}
	for(int d=0;d<n;++d){
		for(int l=1;l+d<=n;++l){
			int r=l+d;
			if(d==0){
				dp[l][r][1]=0;
			}else{
				for(int k=2;k<=n;++k){
					for(int m=l;m<r;++m){
						dp[l][r][k]=min(dp[l][m][1]+dp[m+1][r][k-1],dp[l][r][k]);
					}
					if(k>=L&&k<=R)
					dp[l][r][1]=min(dp[l][r][1],dp[l][r][k]+tot[r]-tot[l-1]);
				}
			}
		}
	}
	if(dp[1][n][1]==inf){
		printf("%d\n",0);
	}else{
		printf("%d\n",dp[1][n][1]);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	while(scanf("%d%d%d",&n,&L,&R)!=EOF){
		solve();
	}
    return 0;
}