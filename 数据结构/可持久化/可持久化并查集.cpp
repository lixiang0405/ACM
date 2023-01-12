/*
给定 n 个集合，第 i 个集合内初始状态下只有一个数，为 i。
有 m 次操作。操作分为 3 种：
1 a b 合并 a,b 所在集合；
2 k 回到第 k 次操作（执行三种操作中的任意一种都记为一次操作）之后的状态；
3 a b 询问 a,b 是否属于同一集合，如果是则输出 1，否则输出 0。
*/

struct Tree{
	int id,ln,rn,fa,dep;
}tre[N*30];

int tot=0,root[N],a[N];
int n,m;

int copy(int node){
	++tot;
	tre[tot]=tre[node];//全部信息都传到新节点
	tre[tot].id=tot;
	return tot;
}

int build(int l,int r){
	++tot;
	int node=tot;
	tre[node].id=node;
	if(l==r){
		tre[node].fa=l;
		return node;
	}
	int m=(l+r)>>1;
	tre[node].ln=build(l,m);
	tre[node].rn=build(m+1,r);
	return node;
}

int merge(int node,int l,int r,int x,int f){
	node=copy(node);	
	if(l==r){
		tre[node].fa=f;
	}else{
		int m=(l+r)>>1;
		if(x<=m)
			tre[node].ln=merge(tre[node].ln,l,m,x,f);	//访问左子树 
		else
			tre[node].rn=merge(tre[node].rn,m+1,r,x,f);	//访问右子树 
	}
	return node;
}

int query(int node,int l,int r,int x){
	if(l==r){
		return tre[node].id;
	}else{
		int m=(l+r)>>1;
		if(x<=m)
			return query(tre[node].ln,l,m,x);	//访问左子树 
		else
			return query(tre[node].rn,m+1,r,x);	//访问右子树 
	}
}

int find(int node,int x){
	int f=query(node,1,n,x);
	if(tre[f].fa==x) return f;
	else return find(node,tre[f].fa);
}

void update(int node,int l,int r,int x){
	if(l==r) tre[node].dep++;
	else{
		int m=(l+r)>>1;
		if(x<=m) update(tre[node].ln,l,m,x);
		else update(tre[node].rn,m+1,r,x);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>m;
	root[0]=build(1,n);
	rep(i,1,m+1){
		int ty;
		cin>>ty;
		if(ty==1){
			int a,b;
			cin>>a>>b;
			root[i]=root[i-1];
			a=find(root[i],a),b=find(root[i],b);
			if(tre[a].fa!=tre[b].fa){
				if(tre[a].dep>tre[b].dep)
					swap(a,b);
				root[i]=merge(root[i],1,n,tre[a].fa,tre[b].fa);
				if(tre[a].dep==tre[b].dep) update(root[i],1,n,tre[b].fa);
			}
		}else if(ty==2){
			int k;
			cin>>k;
			root[i]=root[k];
		}else{
			int a,b;
			cin>>a>>b;
			root[i]=root[i-1];
			cout<<(tre[find(root[i],a)].fa==tre[find(root[i],b)].fa)<<'\n';
		}
	}
	return 0;
} 