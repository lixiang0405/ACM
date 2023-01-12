/*https://codeforces.com/problemset/problem/689/D

给你两个数组 a b，长度均为 n(n<=2e5)，元素范围 [-1e9,1e9]。
求所有满足 max(a[l..r]) = min(b[l..r]) 的区间 [l,r] 的个数。*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define lowbit(x) x&(-x)
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int N = 2e5+100, M = 1e4;
const int inf = 1 << 29;
const int mod = 998244353;
const double esp = 1e-6;
 
template <typename T> void inline read(T& x) {
	int f = 1; x = 0; char s = getchar();
	while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
	while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
	x *= f;
}
 
int a[N],b[N],f1[22][N],f2[22][N];
int n;
ll ans=0;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		f1[0][i]=a[i];
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
		f2[0][i]=b[i];
	}
	for(int i=1;i<=21;++i){
		for(int j=1;j+(1<<i)-1<=n;++j){
			f1[i][j]=max(f1[i-1][j],f1[i-1][j+(1<<(i-1))]);
		}
	}
	for(int i=1;i<=21;++i){
		for(int j=1;j+(1<<i)-1<=n;++j){
			f2[i][j]=min(f2[i-1][j],f2[i-1][j+(1<<(i-1))]);
		}
	}
	for(int i=1;i<=n;++i){
		int l=i,r=n+1;
		while(l<r){
			int m=l-(l-r)/2;
			int len=31-__builtin_clz(m-i+1);
			if(max(f1[len][i],f1[len][m-(1<<len)+1])>=min(f2[len][i],f2[len][m-(1<<len)+1])){
				r=m;
			}else{
				l=m+1;
			}
		}
		int a=l;
		l=i-1,r=n;
		while(l<r){
			int m=r-(r-l)/2;
			int len=31-__builtin_clz(m-i+1);
			if(max(f1[len][i],f1[len][m-(1<<len)+1])<=min(f2[len][i],f2[len][m-(1<<len)+1])){
				l=m;
			}else{
				r=m-1;
			}
		}
		//cout<<i<<" "<<a<<" "<<l<<endl;
		if(l>=a)
		ans+=l-a+1;
	}
	cout<<ans;
    return 0;
}