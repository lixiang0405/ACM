/*
1.在某个历史版本上修改某一个位置上的值

2.访问某个历史版本上的某一位置的值

此外，每进行一次操作，就会生成一个新的版本。版本编号即为当前操作的编号
（对于操作2，即为生成一个完全一样的版本，不作任何改动）
（从1开始编号，版本0表示初始状态数组）
*/

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
		tre[node].val=a[l];
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
		tre[node].val=val;
	}else{
		int m=(l+r)>>1;
		if(x<=m)
			tre[node].ln=modify(tre[node].ln,l,m,x,val);	//访问左子树 
		else
			tre[node].rn=modify(tre[node].rn,m+1,r,x,val);	//访问右子树 
	}
	return node;
}

int query(int node,int l,int r,int x){
	if(l==r){
		return tre[node].val;
	}else{
		int m=(l+r)>>1;
		if(x<=m)
			return query(tre[node].ln,l,m,x);	//访问左子树 
		else
			return query(tre[node].rn,m+1,r,x);	//访问右子树 
	}
}

int n,q;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>q;
	rep(i,1,n+1) cin>>a[i];
	root[0]=build(1,n);
	rep(i,1,q+1){
		int v,ty;
		cin>>v>>ty;
		if(ty==1){
			int x,val;
			cin>>x>>val;
			root[i]=modify(root[v],1,n,x,val);
		}else{
			int x;
			cin>>x;
			cout<<query(root[v],1,n,x)<<"\n";
			root[i]=root[v];
		}
	}
	return 0;
} 