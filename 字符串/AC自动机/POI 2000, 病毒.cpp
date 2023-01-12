/*
二进制病毒审查委员会最近发现了如下的规律：某些确定的二进制串是病毒的代码。
如果某段代码中不存在任何一段病毒代码，那么我们就称这段代码是安全的。
现在委员会已经找出了所有的病毒代码段，
试问，是否存在一个无限长的安全的二进制代码。
示例：
例如如果 {011,11,00000} 为病毒代码段，
那么一个可能的无限长安全代码就是 010101…。
如果 {01,11,000000} 为病毒代码段，那么就不存在一个无限长的安全代码。
现在给出所有的病毒代码段，判断是否存在无限长的安全代码。
*/

struct node{
	node *son[M],*go[M],*fail;
	int mark,vis,ins;
}pool[N],*q[N],*root,*c,*cur=pool;

node* newnode(){
	return cur++;
}

int t=0;

bool dfs(node *u){
	u->vis=1;
	u->ins=1;
	rep(i,0,M){
		if(u->go[i]->mark) continue;
		if(!u->go[i]->vis){
			if(dfs(u->go[i])) return true;
		}else{
			if(u->go[i]->ins) return true;
		}
	}
	u->ins=0;
	return false;
}

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
			if(!c->son[ch-'0']){
				c->son[ch-'0']=newnode();
			}
			c=c->son[ch-'0'];
		}
		c->mark=1;
	}
	build();
	rep(i,1,t) q[i]->mark|=q[i]->fail->mark;//注意root没有fail
	cout<<(dfs(root)?"TAK":"NIE")<<'\n';
	return 0;
}