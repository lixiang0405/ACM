/*
给你一个文本串 S 和 n 个模式串 T1∼Tn
请你分别求出每个模式串 Ti在 S 中出现的次数。
*/

struct node{
	node *son[M],*go[M],*fail;
	int cnt;
}pool[N],*q[N],*cur=pool,*root,*p[N],*c;

node* newnode(){
	return cur++;
}

int t=0;

void build(){
	q[t++]=root;
	rep(i,0,t){
		node *u=q[i];
		rep(j,0,M){
			if(u->son[j]){
				u->go[j]=u->son[j];
				if(u==root) u->go[j]->fail=root;
				else u->go[j]->fail=u->fail->go[j];
				q[t++]=u->son[j];
			}else{
				if(u==root) u->go[j]=root;
				else u->go[j]=u->fail->go[j];
			}
		}
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	root=newnode();
	rep(i,1,1+n){
		string s;
		cin>>s;
		c=root;
		for(auto &ch:s){
			if(!c->son[ch-'a']){
				c->son[ch-'a']=newnode();
			}
			c=c->son[ch-'a'];
		}
		p[i]=c;
	}
	build();
	string tmp;
	cin>>tmp;
	c=root;
	for(auto &ch:tmp){
		if(ch==0){
			c=root;
		}else c=c->go[ch-'a'];
		c->cnt++;
	}
	per(i,1,t) q[i]->fail->cnt+=q[i]->cnt;
	rep(i,1,1+n){
		cout<<(p[i]->cnt)<<'\n';
	}
	return 0;
}