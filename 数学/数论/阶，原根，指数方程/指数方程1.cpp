/*回答T组询问，每次给一个数a,b,m，
输出最小的非负整数x满足a^x ≡ b (mod m素数)。*/

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
const int N = 2e5+5, M = 6000+5;
const ll inf = 1LL << 60;
const int mod = 1e9+7;
const double esp = 1e-6;
 
template <typename T> void inline read(T& x) {
	int f = 1; x = 0; char s = getchar();
	while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
	while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
	x *= f;
}

struct Hash_table{
    static const int V=1000003;
    int fst[V],nxt[V],ptm[V];
    int ctm,T;
    int val[V];
    ll key[V];

    void init(){
        T=0;
        ctm++;
    }

    void insert(ll s,int v){
        int S=s%V;
        if(ptm[S]!=ctm) ptm[S]=ctm,fst[S]=-1;
        for(int j=fst[S];j!=-1;j=nxt[j])
            if(key[j]==s) return;
        nxt[T]=fst[S];
        fst[S]=T;
        key[T]=s;
        val[T]=v;
        T++;
    }

    int query(ll s){
        int S=s%V;
        if(ptm[S]!=ctm) return -1;
        for(int j=fst[S];j!=-1;j=nxt[j])
            if(key[j]==s) return val[j];
        return -1;
    }
}hs;

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

int t;
//(a^T)^q ≡ b*a^(r) (mod m)
void BSGS(){
	int a,b,m;
	scanf("%d%d%d",&a,&b,&m);
	hs.init();
	ll T=sqrt(m)+2;
	ll v=qp(a,T,m),d=1;
	for(int q=1;q<=T;++q){
		d=d*v%m;
		if(hs.query(d)==-1) hs.insert(d,q*T);
	}
	d=b;
	int ans=m+1;
	for(int r=1;r<=T;++r){
		d=d*a%m;
		if(hs.query(d)!=-1) ans=min(ans,hs.query(d)-r);
	}
	if(ans>=m){
		printf("-1\n");
	}else printf("%d\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&t);
    while(t--){
        BSGS();
    }
	return 0;
} 