double f(double x){
    // 计算函数值，即f(x)
}
 
double trisection_search(double l, double r){
    // 三分搜索，找到最优解（求函数最大值下的自变量值）
    double midl, midr;
    while (r-l > 1e-7){
        midl = (l + r) / 2;
        midr = (midl + r) / 2;
        // 如果是求最小值的话这里判<=即可
        if(f(midl) >= f(midr)) r = midr;
        else l = midl;
    }
    return l;
}


//整数点
ll ans=1e18;
while(l!=r){
    int midl=l-(l-r)/2;
    int midr=(r+midl)/2;
    ll f1=calc(midl),f2=calc(midr);
    ans=min({f1,f2,ans});
    if(f1>f2) l=midl;
    else r=midr; 
}
ans=min(ans,calc(l));