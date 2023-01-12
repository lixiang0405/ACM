#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
mt19937 rnd(time(0));
typedef vector<int> VI;
typedef long long ll;
typedef __int128_t i128;//read printf
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef double db;
const int N = 2e5+5, M = 6000+5;
const ll inf = 1LL << 60;
const int mod = 1e9+7;
const double esp = 1e-9;
 
template <typename T> void inline read(T& x) {
	int f = 1; x = 0; char s = getchar();
	while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
	while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
	x *= f;
}

void solve(){
	
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	cin>>t;
    while(t--){
        solve();
    }
	return 0;
}