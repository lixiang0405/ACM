/*
给你一个1∼n的排列p1,p2,…,pn。

让你找到一个1∼n的排列q，满足对于任意区间[l,r](1≤l≤r≤n)，满足pl,pl+1,…,pr中的最小值的位置，和ql,ql+1,…,qr的最小值的位置相同。

输出满足条件的字典序最小的q。
*/

int root,a[N],l[N],r[N],ans[N],stk[N];
int n,tot=0;

void dfs(int u){
	ans[u]=++tot;
	if(l[u]) dfs(l[u]);
	if(r[u]) dfs(r[u]);
}
/*
void build(){
    stack<int> sk;
    root=0;
    //for(int i=1;i<=n;++i) l[i]=r[i]=0;
    for(int i=1;i<=n;++i){
        int last=0;
        while(!sk.empty()&&a[sk.top()]>a[i]){
            last=sk.top();
            sk.pop();
        }
        if(!sk.empty()) r[sk.top()]=i;
        else root=i;
        l[i]=last;
        sk.push(i);
    }
	dfs(root);
}*/

void build(){
    int top=0;
    //for(int i=1;i<=n;++i) l[i]=r[i]=0;
    for(int i=1;i<=n;++i){
        int k=top;
        while(k>0&&a[stk[k-1]]>a[i]) --k;
        if(k) r[stk[k-1]]=i;
        if(k<top) l[i]=stk[k];
        stk[k++]=i;
        top=k;
    }
	dfs(stk[0]);
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	build();
	for(int i=1;i<=n;++i)
	printf("%d ",ans[i]);
    return 0;
}
