/*你要维护n个序列p1,p2,…,pn，一开始都是空的。接下来需要支持q个操作：

1 x y，往序列px末尾插入一个数y，每个序列的下标都是从0开始的。

2 z，对于所有非空的序列pi，求出pi,zmod|pi|的和，其中|pi|表示序列pi中数字个数。*/

vector<int> p[N],large;
ll sum[M+5][M+5]; 
int n,q;
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&q);
	for(int i=0;i<q;++i){
		int ty,x;
		scanf("%d%d",&ty,&x);
		if(ty==1){
			int m=p[x].size(),y;
			scanf("%d",&y);
			if(m<=M){
				for(int j=0;j<m;++j){
					sum[m][j]-=p[x][j];
				}
			}
			m++;
			p[x].push_back(y);
			if(m<=M){
				for(int j=0;j<m;++j){
					sum[m][j]+=p[x][j];
				}
			}else if(m==M+1){
				large.push_back(x);
			}
		}else{
			ll ans=0;
			for(int j=1;j<=M;++j){
				ans+=sum[j][x%j];
			}
			for(auto &cur:large){
				ans+=p[cur][x%(int)p[cur].size()];
			}
			printf("%lld\n",ans);
		}
	}
    return 0;
}
