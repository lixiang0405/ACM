/*
阿狸喜欢收藏各种稀奇古怪的东西，最近他淘到一台老式的打字机。打字机上只有 28 个按键，
分别印有 26 个小写英文字母和 B、P 两个字母。经阿狸研究发现，这个打字机是这样工作的：
输入小写字母，打字机的一个凹槽中会加入这个字母(这个字母加在凹槽的最后)。
按一下印有 B 的按键，打字机凹槽中最后一个字母会消失。
按一下印有 P 的按键，打字机会在纸上打印出凹槽中现有的所有字母并换行，但凹槽中的字母不会消失。
例如，阿狸输入 aPaPBbP，纸上被打印的字符如下：

a
aa
ab

我们把纸上打印出来的字符串从 1 开始顺序编号，一直到 n。打字机有一个非常有趣的功能，
在打字机中暗藏一个带数字的小键盘，在小键盘上输入两个数 (x,y)（其中 1≤x,y≤n），
打字机会显示第 x 个打印的字符串在第 y 个打印的字符串中出现了多少次。
阿狸发现了这个功能以后很兴奋，他想写个程序完成同样的功能，你能帮助他么？
*/
struct node{
	node *son[M],*go[M],*fail,*fa;
	int l,r;//dfs序
	vector<node*> fs;//fail 树的儿子
	vector<pii> que;
}pool[N],*q[N],*root,*c,*cur=pool,*p[N];

node* newnode(){
	return cur++;
}

int t=0,ans[N];

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
	rep(i,1,t) q[i]->fail->fs.pb(q[i]);
	int tot=0;
	function<void(node*)> dfs=[&](node *u){
		u->l=++tot;
		for(auto &v:u->fs){
			dfs(v);
		}
		u->r=tot;
	};
	dfs(root);
}

#define lowbit(x) x&(-x)
template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){
        n=s;
        for(int i=1;i<=n;++i) c[i]=0;
    }

    T query(int x){
        assert(x<=n);
        T s=0;
        for(;x;x-=lowbit(x)){
            s+=c[x];
        }
        return s;
    }

    void modify(int x,T s){
        assert(x!=0);
        for(;x<=n;x+=lowbit(x)){
            c[x]+=s;
        }
    }
 
    //树状数组上二分 查询最大的T(0≤T≤n)满足∑(i=1-T) ai≤s。
    int ask(T s){
        int pos=n;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos-(1<<i)<=n&&c[pos-(1<<i)]<=s){
                pos-=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<int> C;

void dfs(node *u){
	C.modify(u->l,1);
	for(auto [x,id]:u->que){
		ans[id]=C.query(p[x]->r)-C.query(p[x]->l-1);
	}
	rep(i,0,M){
		if(u->son[i]) dfs(u->son[i]);
	}
	C.modify(u->l,-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	root=newnode();
	c=root;
	string s;
	cin>>s;
	int n=0;
	for(auto &ch:s){
		if(ch=='B'){
			c=c->fa;
		}else if(ch=='P'){
			p[++n]=c;
		}
		else{
			if(!c->son[ch-'a'])
				c->son[ch-'a']=newnode();
			c->son[ch-'a']->fa=c;
			c=c->son[ch-'a'];
		}
	}
	build();
	int m;
	cin>>m;
	rep(i,1,1+m){
		int x,y;
		cin>>x>>y;
		p[y]->que.pb({x,i});//对于y字符串的每一个字符,如果它的fail能跳到x的结尾处,说明它的后缀包含x字符串
	}
	C.resize(t);
	dfs(root);
	rep(i,1,1+m) cout<<ans[i]<<'\n';
	return 0;
}