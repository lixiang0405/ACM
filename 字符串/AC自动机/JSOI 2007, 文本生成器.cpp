/*
也就是说，生成的文章中每个字符都是完全随机的。
如果一篇文章中至少包含使用者们了解的一个单词，那么我们说这篇文章是可读的
（我们称文章 s 包含单词 t，当且仅当单词 t 是文章 s 的子串）。
ZYX 需要指出 GW 文本生成器 v6 生成的所有文本中，可读文本的数量。你能帮助他吗？
答案对 104+7 取模。
*/

struct node{
	node *son[M],*go[M],*fail;
	int mark;
}pool[N],*q[N],*root,*c,*cur=pool;

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

int dp[110][N][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	root=newnode();
	rep(i,1,1+n){
		string s;
		cin>>s;
		c=root;
		for(auto &ch:s){
			if(!c->son[ch-'A']){
				c->son[ch-'A']=newnode();
			}
			c=c->son[ch-'A'];
		}
		c->mark=1;
	}
	build();
	rep(i,1,t) q[i]->mark|=q[i]->fail->mark;//注意root没有fail
	dp[0][0][0]=1;//dp[i][j][k] i:走i步 j:到点j k:是否经过单词的结尾
	rep(i,0,m){
		rep(j,0,t){
			rep(k,0,2){
				if(dp[i][j][k]){
					node *u=root+j;
					rep(p,0,M){
						dp[i+1][u->go[p]-root][k|u->go[p]->mark]=(dp[i+1][u->go[p]-root][k|u->go[p]->mark]+dp[i][j][k])%mod;
					}
				}
			}
		}
	}
	int ans=0;
	rep(i,0,t){
		ans=(ans+dp[m][i][1])%mod;
	}
	cout<<ans<<'\n';
	// dp[0][0]=1; dp[i][j] i:走i步 j:到点j 文章完全不可读的方案
	// rep(i,0,m){
	// 	rep(j,0,t){
	// 		if(dp[i][j]){
	// 			node *u=root+j;
	// 			rep(p,0,M){
	// 				if(u->go[p]->mark) continue;
	// 				dp[i+1][u->go[p]-root]=(dp[i+1][u->go[p]-root]+dp[i][j])%mod;
	// 			}
	// 		}
	// 	}
	// }
	// int ans=0;
	// rep(i,0,t){
	// 	ans=(ans+dp[m][i])%mod;
	// }
	// cout<<(qp(26,m,mod)-ans+mod)%mod<<'\n';
	return 0;
}