#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;

struct Tree{
	int l,r;
	int lmax,rmax,ans,sum;
}tre[4*N];

int n,m,a[N];

void pushup(Tree &a,Tree &b,Tree &c){
	a.lmax=max(b.lmax,b.sum+c.lmax);
	a.rmax=max(c.rmax,c.sum+b.rmax);
	a.sum=b.sum+c.sum;
	a.ans=max({b.ans,c.ans,b.rmax+c.lmax});
}

inline void pushup(int k){
	pushup(tre[k],tre[k<<1],tre[k<<1|1]);
}

inline void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,x,a[x],a[x],a[x],a[x]};
	}else{
		int m=(x+y)>>1;
		tre[k]={x,y};
		build(k<<1,x,m);
		build(k<<1|1,m+1,y);
		pushup(k);
	}
}

inline void update(int k,int x,int t){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==r){
		tre[k]={l,l,t,t,t,t};
	}else{
		if(x<=m) update(k<<1,x,t);
		else update(k<<1|1,x,t);
		pushup(k);
	}
}

inline Tree query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==x&&r==y){
		return tre[k];
	}else{
		if(y<=m) return query(k<<1,x,y);
		else if(x>m) return query(k<<1|1,x,y);
		else{
			auto a=query(k<<1,x,m),b=query(k<<1|1,m+1,y);
			Tree c;
			pushup(c,a,b);
			return c;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a==1){
			if(b>c)
			swap(b,c);
			auto x=query(1,b,c);
			printf("%d\n",x.ans);
		}else{
			update(1,b,c);
		}
	}
	return 0;
}