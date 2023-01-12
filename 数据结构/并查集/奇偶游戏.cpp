/*小 A 和小 B 在玩一个游戏。

首先，小 A 写了一个由 0 和 1 组成的序列 S，长度为 N。

然后，小 B 向小 A 提出了 M 个问题。

在每个问题中，小 B 指定两个数 l 和 r，小 A 回答 S[l∼r] 中有奇数个 1 还是偶数个 1。

机智的小 B 发现小 A 有可能在撒谎。

例如，小 A 曾经回答过 S[1∼3] 中有奇数个 1，S[4∼6] 中有偶数个 1，现在又回答 S[1∼6] 中有偶数个 1，显然这是自相矛盾的。

请你帮助小 B 检查这 M 个答案，并指出在至少多少个回答之后可以确定小 A 一定在撒谎。

即求出一个最小的 k，使得 01 序列 S 满足第 1∼k 个回答，但不满足第 1∼k+1 个回答。*/

int n,m,f[N],v[N];
vector<int> vt;
array<int,3> a[N];

int find(int u){
    if(u==f[u])
    return u;
    int p=f[u];
    find(p);
    v[u]^=v[p];
    f[u]=f[p];
    return f[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        string s;
        cin>>a[i][0]>>a[i][1]>>s;
        a[i][0]--;
        if(s=="even")
        a[i][2]=0;
        else
        a[i][2]=1;
        vt.push_back(a[i][1]);
        vt.push_back(a[i][0]);
    }
    stable_sort(vt.begin(),vt.end());
    vt.erase(unique(vt.begin(),vt.end()),vt.end());
    int sz=vt.size();
    for(int i=1;i<=sz;++i){
        f[i]=i;
        v[i]=0;
    }
    for(int i=1;i<=m;++i){
        auto &q=a[i];
        int x=lower_bound(vt.begin(),vt.end(),q[0])-vt.begin()+1,
        y=lower_bound(vt.begin(),vt.end(),q[1])-vt.begin()+1;
        if(q[2]==1){
            if(find(x)==find(y)){
                int ans=v[x]^v[y];
                if(ans==q[2]) continue;
                else{
                    cout<<i-1<<endl;
                    break;
                }
            }else{
                v[f[x]]=v[x]^v[y]^q[2];
                f[f[x]]=f[y];
            }
        }else{
            if(find(x)==find(y)){
                int ans=v[x]^v[y];
                if(ans==q[2]) continue;
                else{
                    cout<<i-1<<endl;
                    break;
                }
            }else{
                v[f[x]]=v[x]^v[y]^q[2];
                f[f[x]]=f[y];
            }
        }
        if(i==m)
        cout<<m;
    }
    if(m==0)
    cout<<0;
    return 0;
}

