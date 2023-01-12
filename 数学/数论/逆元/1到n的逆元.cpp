/*
给一个素数 p，求1∼n关于p的逆元。

由于输出可能很大，只需要求这些逆元的异或和即可。
*/

const int N = 1e7+5;
ll inv[N];
int n,p; 

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	scanf("%d%d",&p,&n);
	inv[1]=1;
	int ans=1;
	for(int i=2;i<=n;++i){
		inv[i]=(p-p/i)*inv[p%i]%p;
		ans^=inv[i];
	}
	printf("%d",ans);
	return 0;
} 