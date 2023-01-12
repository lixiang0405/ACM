/*动物王国中有三类动物 A,B,C，这三类动物的食物链构成了有趣的环形。

A 吃 B，B 吃 C，C 吃 A。

现有 N 个动物，以 1∼N 编号。

每个动物都是 A,B,C 中的一种，但是我们并不知道它到底是哪一种。

有人用两种说法对这 N 个动物所构成的食物链关系进行描述：

第一种说法是 1 X Y，表示 X 和 Y 是同类。

第二种说法是 2 X Y，表示 X 吃 Y。

此人对 N 个动物，用上述两种说法，一句接一句地说出 K 句话，这 K 句话有的是真的，有的是假的。

当一句话满足下列三条之一时，这句话就是假话，否则就是真话。

当前的话与前面的某些真的话冲突，就是假话；
当前的话中 X 或 Y 比 N 大，就是假话；
当前的话表示 X 吃 X，就是假话。
你的任务是根据给定的 N 和 K 句话，输出假话的总数。*/

int ans=0,f[N],v[N],n,k;

int find(int u){
    if(u==f[u])
    return u;
    int p=f[u];
    find(p);
    v[u]=(v[u]+v[p])%3;
    f[u]=f[p];
    return f[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        f[i]=i;
        v[i]=0;
    }
    for(int i=1;i<=k;++i){
        int ty,x,y;
        cin>>ty>>x>>y;
        if(x>n||y>n||x<=0||y<=0){
            ans++;
            continue;
        }
        int a=find(x),b=find(y);
        if(ty==1){
            if(a==b&&v[x]!=v[y]){
                ans++;
            }else if(a!=b){
                f[a]=b;
                v[a]=(-v[x]+v[y]+3)%3;
            }
        }else{
            if(a==b&&(v[x]-v[y]+3)%3!=1){
                ans++;
            }else if(a!=b){
                f[a]=b;
                v[a]=(-v[x]+v[y]+4)%3;
            }
        }
    }
    cout<<ans;
    return 0;
}

