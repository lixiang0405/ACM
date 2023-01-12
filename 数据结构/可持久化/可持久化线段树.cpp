/*如题，给定 n 个整数构成的序列 a，将对于指定的闭区间 
[l, r] 查询其区间内的第 k 小值。*/

struct Tree{
	int ln,rn,val;
}tre[N*30];

int tot=0,root[N],a[N];

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

int modify(int node,int l,int r,int x,int val){
	node=copy(node);	//更新就要新建节点 
	if(l==r){
		tre[node].val+=val;
	}else{
		int m=(l+r)>>1;
		if(x<=m)
			tre[node].ln=modify(tre[node].ln,l,m,x,val);	//访问左子树 
		else
			tre[node].rn=modify(tre[node].rn,m+1,r,x,val);	//访问右子树 
		tre[node].val=tre[tre[node].ln].val+tre[tre[node].rn].val;
	}
	return node;
}

int query(int L,int R,int l,int r,int k){
	if(l==r){
		return l;
	}else{
		int val=tre[tre[R].ln].val-tre[tre[L].ln].val;
		int m=(l+r)>>1;
		if(val>=k)
			return query(tre[L].ln,tre[R].ln,l,m,k);	//访问左子树 
		else
			return query(tre[L].rn,tre[R].rn,m+1,r,k-val);	//访问右子树 
	}
}

int n,q;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>q;
	VI vt;
	rep(i,1,n+1) cin>>a[i],vt.pb(a[i]);
	root[0]=build(1,n);
	sort(all(vt));
	vt.erase(unique(all(vt)),vt.end());
	rep(i,1,n+1){
		int id=lower_bound(all(vt),a[i])-vt.begin()+1;
		root[i]=modify(root[i-1],1,n,id,1);
	}
	rep(i,1,q+1){
		int l,r,k;
		cin>>l>>r>>k;
		cout<<vt[query(root[l-1],root[r],1,n,k)-1]<<'\n';
	}
	return 0;
} 