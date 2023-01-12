/*
给你k个字符串P1...Pk和一个字符串s
可以选择最多c1个'a',c2个'b'.....,c26个'z'添加到s后面
问对于每个在0到k之间的x,是否存在一种添加方式使得刚好有x个pi字符串字典序严格小于s
*/

struct node{
	node *son[M];
	int cnt[M],end;
}pool[N],*cur=pool,*root,*c;

node* newnode(){
	return cur++;
}

int t,cnt[30],b[30],ans[N];
string p[N];

void dfs(node *x,int res){
	ans[res]=1;
	if(!x) return;
	int tot=0;
	rep(i,0,26){
		if(cnt[i]){
			cnt[i]--;
			dfs(x->son[i],res+tot+x->end);
			cnt[i]++;
		}
		tot+=x->cnt[i];
	}
}

void solve(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	root=newnode();
	rep(i,0,26) cin>>cnt[i];
	int k;
	cin>>k;
	rep(i,1,1+k){
		cin>>p[i];
		c=root;
		for(auto ch:p[i]){
			c->cnt[ch-'a']++;
			if(!c->son[ch-'a']) c->son[ch-'a']=newnode();
			c=c->son[ch-'a'];
		}
		c->end++;
	}
	c=root;
	int res=0;
	rep(i,0,SZ(s)){
		char ch=s[i];
		res+=c->end;
		rep(i,0,ch-'a') res+=c->cnt[i];
		c=c->son[ch-'a'];
		if(!c) break;
	}
	dfs(c,res);
	rep(i,0,1+k){
		cout<<(ans[i]?"Yes":"No")<<'\n';
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	t=1;
    while(t--){
        solve();
    }
	return 0;
}