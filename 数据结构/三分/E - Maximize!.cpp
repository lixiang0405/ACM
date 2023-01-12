/*https://codeforces.com/problemset/problem/939/E

一开始你有一个空数组 a。
接下来有 Q(<=5e5) 次操作或询问。
操作（用 1 和 x 表示）是往 a 的末尾添加一个在 [1,1e9] 的数字 x，保证添加后 a 仍然是非降的。
询问（用 2 表示）是请你选择 a 中的一个子序列（不要求连续）b，最大化 max(b)-avg(b)，这里 avg(b) 为 b 的平均值。
对于每个询问，输出 max(b)-avg(b) 的最大值。（保留 8 位小数即可）*/

int q,cnt=0;
ll pre[N];

double f(int x){
    // 计算函数值，即f(x)
	return (double)(pre[cnt]-pre[cnt-1])-(double)(pre[cnt]-pre[cnt-1]+pre[x])/(x+1);
}

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d",&q);
    while(q--){
        int ty;
        scanf("%d",&ty);
        if(ty==1){
            int x;
            scanf("%d",&x);
            pre[cnt]=pre[++cnt-1]+x;
            //cout<<pre[cnt]<<endl;
        }else{
            if(cnt<=1){
                printf("%.8lf\n",0);
                continue;
            }
            double ans=0;
            int l=1,r=cnt;
            while(l!=r){
                int midl=l-(l-r)/2;
                int midr=(r+midl)/2;
                double f1=f(midl),f2=f(midr);
                ans=max({f1,f2,ans});
                if(f1<f2) l=midl;
                else r=midr; 
            }
            ans=max(ans,f(l));
            printf("%.8lf\n",ans);
        }
    }
    return 0;
}
