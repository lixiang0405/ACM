/*
给一个长度为 n 的数组 a1,a2,...,an，
问有多少组满足条件的 b1,b2,b3,b4(1≤b1<b2<b3<b4≤n) 
满足ab1 xor ab2 xor ab3 xor ab4=0。
*/

int a[N],cnt[(1<<20)+10];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	scanf("%d",&n);
	rep(i,1,1+n) scanf("%d",&a[i]);
	ll ans=0;
	rep(b3,1,1+n){
		rep(b4,b3+1,1+n){
			ans+=cnt[a[b3]^a[b4]];
		}
		rep(b1,1,b3){
			cnt[a[b1]^a[b3]]++;
		}
	}
	cout<<ans<<'\n';
	return 0;
}