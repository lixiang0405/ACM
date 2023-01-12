/*
题意：

给定一个长度为n(n<=2e5)的数组a(1<=a<=1e9)。

给出q(q<=2e5)个询问(L,R)(1<=L<=R<=n)。

问，区间[L,R]中，最小的出现次数为奇数的数，如果没有出现次数为奇数的数，输出0。

询问强制在线。
*/

struct Tree{
	int ln,rn;
	ll val;
}tre[N*30];
 
int tot=0,root[N];
 
int copy(int node){
	++tot;
	tre[tot]=tre[node];//全部信息都传到新节点
	return tot;
}
 
int build(int l,int r){
	++tot;
	int node=tot;
	if(l==r){
		tre[node].val=0;
		return node;
	}
	int m=(l+r)>>1;
	tre[node].ln=build(l,m);
	tre[node].rn=build(m+1,r);
	return node;
}
 
int modify(int node,int l,int r,int x,ll val){
	node=copy(node);	//更新就要新建节点 
	if(l==r){
		tre[node].val^=val;
	}else{
		int m=(l+r)>>1;
		if(x<=m)
			tre[node].ln=modify(tre[node].ln,l,m,x,val);	//访问左子树 
		else
			tre[node].rn=modify(tre[node].rn,m+1,r,x,val);	//访问右子树 
		tre[node].val=tre[tre[node].ln].val^tre[tre[node].rn].val;
	}
	return node;
}
 
int query(int L,int R,int l,int r){
	if(l==r){
		int val=tre[R].val^tre[L].val;
		if(val)
			return l;
		else return -1;
	}else{
		int val=tre[tre[R].ln].val^tre[tre[L].ln].val;
		int m=(l+r)>>1;
		if(val)
			return query(tre[L].ln,tre[R].ln,l,m);	//访问左子树 
		else
			return query(tre[L].rn,tre[R].rn,m+1,r);	//访问右子树 
	}
}
 
int a[N];
  
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	VI vt;
	rep(i,1,1+n){
		cin>>a[i];
		vt.pb(a[i]);
	}
	sort(all(vt));
	vt.erase(unique(all(vt)),vt.end());
	int m=SZ(vt);
	root[0]=build(1,m);
	map<int,ll> mp;
	rep(i,0,SZ(vt)){
		mp[vt[i]]=rnd();
	}
	rep(i,1,1+n){
		int pos=lower_bound(all(vt),a[i])-vt.begin()+1;
		root[i]=modify(root[i-1],1,n,pos,mp[a[i]]);
	}
	int q,ans=0;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		l^=ans,r^=ans;
		int res=query(root[l-1],root[r],1,n);
		if(res==-1){
			cout<<0<<'\n';
			ans=0;
		}else{
			cout<<vt[res-1]<<'\n';
			ans=vt[res-1];
		}
	}
	return 0;
}
