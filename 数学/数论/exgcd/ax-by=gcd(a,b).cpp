/*
输入T，一共T组数据，每组两个数a,b，输出ax−by=gcd(a,b)的最小非负整数解(x,y)。
*/

int t;

int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
} 

void solve(){
	int a,b,x,y;
	scanf("%d%d",&a,&b);
	int d=exgcd(a,b,x,y);
	y=-y;
	while(x<0||y<0) x+=b/d,y+=a/d;
	while(x>=b/d&&y>=a/d) x-=b/d,y-=a/d;
//	if(x<0||y<0) x+=b/d,y+=a/d;
	printf("%d %d\n",x,y);
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	scanf("%d",&t);
	while(t--){
		solve();
	}
	return 0;
} 