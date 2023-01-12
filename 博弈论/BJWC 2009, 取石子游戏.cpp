/*
小H和小Z正在玩一个取石子游戏。取石子游戏的规则是这样的，
每个人每次可以从一堆石子中取出若干个石子，每次取石子的个数有限制，
谁不能取石子时就会输掉游戏。 
小H先进行操作，他想问你他是否有必胜策略，如果有，第一步如何取石子。
*/
int a[N],b[N],sg[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	scanf("%d",&n);
	rep(i,1,1+n) scanf("%d",&a[i]);
	int m;
	scanf("%d",&m);
	rep(i,1,1+m) scanf("%d",&b[i]);
	rep(i,1,1001){
		set<int> s;
		rep(j,1,1+m){
			if(i>=b[j]) s.insert(sg[i-b[j]]);
		}
		while(s.count(sg[i])) sg[i]++;
	}
	int ans=0;
	rep(i,1,1+n){
		ans^=sg[a[i]];
	}
	if(ans){
		printf("YES\n");
		rep(i,1,1+n){
			rep(j,1,1+m){
				if(a[i]>=b[j]&&!(ans^sg[a[i]]^sg[a[i]-b[j]])){
					printf("%d %d\n",i,b[j]);
					return 0;
				}
			}
		}
	}else{
		printf("NO\n");
	}
	return 0;
} 