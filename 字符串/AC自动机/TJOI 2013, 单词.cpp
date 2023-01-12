/*
某人读论文，一篇论文是由许多单词组成，
可以理解成是若干个单词加空格相连。
但他发现一个单词会在论文中出现很多次，
现在想知道每个单词分别在论文中作为子串出现多少次。
*/

struct node{
	node *son[M],*go[M],*fail;
	int cnt;
}pool[N],*q[N],*cur=pool,*root,*p[210],*c;

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
	string tmp;
	root=newnode();
	rep(i,1,1+n){
		string s;
		cin>>s;
		tmp+=s;
		c=root;
		for(auto &ch:s){
			if(!c->son[ch-'a']){
				c->son[ch-'a']=newnode();
			}
			c=c->son[ch-'a'];
		}
		p[i]=c;
		tmp.push_back(0);
	}
	build();
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