/*
大会的规则如下：每位参赛的选手可以得到 n 种材料，

选手可以自由选择用满式或是汉式料理将材料当成菜肴。

大会的评审制度是：共有 m 位评审员分别把关。

每一位评审员对于满汉全席有各自独特的见解，

但基本见解是，要有两样菜色作为满汉全席的标志。

如某评审认为，如果没有汉式东坡肉跟满式的涮羊肉锅，

就不能算是满汉全席。但避免过于有主见的审核，

大会规定一个评审员除非是在认为必备的两样菜色都没有做出来的状况下，

才能淘汰一位选手，否则不能淘汰一位选手。

换句话说，只要参赛者能在这两种材料的做法中，

其中一个符合评审的喜好即可通过该评审的审查。

如材料有猪肉，羊肉和牛肉时，有四位评审员的喜好如下表：

评审一   评审二   评审三   评审四 
满式牛肉 满式猪肉 汉式牛肉 汉式牛肉 
汉式猪肉 满式羊肉 汉式猪肉 满式羊肉

如参赛者甲做出满式猪肉，满式羊肉和满式牛肉料理，

他将无法满足评审三的要求，无法通过评审。而參赛者乙做出汉式猪肉，

满式羊肉和满式牛肉料理，就可以满足所有评审的要求。但大会后来发现，

在这样的制度下如果材料选择跟派出的评审员没有特别安排好的话，

所有的参赛者最多只能通过部分评审员的审查而不是全部，

所以可能会发生没有人通过考核的情形。

如有四个评审员喜好如下表时，则不论参赛者采取什么样的做法，

都不可能通过所有评审的考核：

评审一   评审二   评审三   评审四 
满式羊肉 满式猪肉 汉式羊肉 汉式羊肉 
汉式猪肉 满式羊肉 汉式猪肉 满式猪肉

所以大会希望有人能写一个程序来判断，所选出的 m 位评审，
会不会发生没有人能通过考核的窘境，以便协会组织合适的评审团。
*/

int t;

int cnt=0,tot=0;
int dfn[N],low[N],bel[N],sz[N],ins[N];
stack<int> sk;
vector<int> e[N];
 
void dfs(int u){
	dfn[u]=low[u]=++tot;
	sk.push(u);
	ins[u]=1;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else 
			if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		while(1){
			int x=sk.top();
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			sz[cnt]++;
			if(x==u) break;
		}
	}
}

void solve(){
    int n,m;
    cin>>n>>m;
    rep(i,0,2*n) e[i].clear(),dfn[i]=0;
    cnt=tot=0;
    rep(i,0,m){
        string x,y;
        cin>>x>>y;
        //h:2*i+1,m:2*i
        int u=(x[0]=='h'),v=(y[0]=='h');
        x.erase(x.begin());
        y.erase(y.begin());
        u+=2*(stoi(x)-1);
        v+=2*(stoi(y)-1);
        e[u^1].pb(v);
        e[v^1].pb(u); 
    }
    rep(i,0,2*n) if(!dfn[i]) dfs(i);
    rep(i,0,n){
        //如果问选或者不选:选拓扑序靠后的,bel[2*i]<bel[2*i+1] 选2*i:先出栈拓扑序靠后
        if(bel[i*2]==bel[i*2+1]){
            cout<<"BAD\n";
            return;
        }
    }
    cout<<"GOOD\n";
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
} 
