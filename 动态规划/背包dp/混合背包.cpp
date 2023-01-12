/*
有n种物品要放到一个袋子里，袋子的总容量为m。

物品一共有3类，第i种物品属于第ai类，它的体积为vi，把它放进袋子里会获得wi的收益。

如果它属于第1类物品，每种只能用一次。

如果它属于第2类物品，每种可以用无限多次。

如果它属于第3类物品，每种可以用li次。

问如何选择物品，使得在物品的总体积不超过m的情况下，获得最大的收益？请求出最大收益。
*/

int n,m,dp[N],l[N],v[N],w[N],id[N];
int L,r,c[N][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
		scanf("%d",&id[i]);
		if(id[i]==3){
			scanf("%d%d%d",&v[i],&w[i],&l[i]);
		}else{
			scanf("%d%d",&v[i],&w[i]);
		}
	}
	for(int i=1;i<=n;++i){
		if(id[i]==1){
			for(int j=m;j>=v[i];--j){
				if(j>=v[i]) dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
			}
		}else if(id[i]==2){
			for(int j=1;j<=m;++j){
				if(j>=v[i]) dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
			}
		}else{
			for(int j=0;j<v[i];++j){
				L=0,r=-1;
				for(int k=j,x=1;k<=m;k+=v[i],x++){
					int a=dp[k]-x*w[i],b=x+l[i];
					while(L<=r&&c[r][0]<=a) r--;
					while(L<=r&&c[L][1]<x) L++;
					c[++r][0]=a,c[r][1]=b;
					dp[k]=c[L][0]+w[i]*x;
				}
			}
		}
	}
	printf("%d",dp[m]);
    return 0;
}