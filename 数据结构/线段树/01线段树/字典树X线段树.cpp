/*给n个数字a1,a2,…,an。

你要回答m个询问，每次给定两个数x,k，询问a1 xor x,a2 xor x,…,an xor x中从小到大排序中第k小的元素。*/

struct Node{
    int s[2];
    int sz;
}seg[N*32];

int n,m;
int tot=0,root;

int main() {
	scanf("%d%d",&n,&m);
    root=++tot;
    for(int i=0;i<n;++i){
        int x;
        int p=root;
        scanf("%d",&x);
        for(int j=29;j>=0;--j){
            seg[p].sz++;
            int mask=1&(x>>j);
            if(seg[p].s[mask]==0) seg[p].s[mask]=++tot;
            p=seg[p].s[mask];
        }
        seg[p].sz++;
    }
    for(int i=0;i<m;++i){
        int x,k,ans=0;
        int p=root;
        scanf("%d%d",&x,&k);
        for(int j=29;j>=0;--j){
            int mask=1&(x>>j);
            if(seg[seg[p].s[mask]].sz>=k){
                p=seg[p].s[mask];
            }else{
                ans^=1<<j;
                k-=seg[seg[p].s[mask]].sz;
                p=seg[p].s[mask^1];
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
