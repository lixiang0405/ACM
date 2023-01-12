/*
给定一个数字n，求∑(i=1-n)(n mod i)。

答案可能很大，输出对260取模的结果。
*/

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ull n,ans=0;
	scanf("%llu",&n);
	// n%i=n-n/i*i
	for(ull l=1;l<=n;l++){
		ull d=n/l,r=n/d;
		ans+=n*(r-l+1)-d*(r-l+1)*(r+l)/2;
		// ans+=(n-l*d+n-r*d)*(r-l+1)/2
		l=r;
	}
	printf("%llu",ans%(1LL<<60));
	return 0;
} 