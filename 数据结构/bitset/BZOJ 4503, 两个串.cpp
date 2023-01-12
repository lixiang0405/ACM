/*
兔子们在玩两个串的游戏。给定两个字符串 S 和 T ，
兔子们想知道 T 在 S 中出现了几次，分别在哪些位置出现。
注意 T 中可能有 ? 字符，这个字符可以匹配任何字符。

两行两个字符串，分别代表 S,T(|S|≤105,|T|≤|S|)。S 中只包含小写字母，T 中只包含小写字母和?。
*/

bitset<N> g[26],f;
char s[N],t[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%s%s",s,t);
    int n=strlen(s),m=strlen(t);
    rep(i,0,n-m+1) f[i]=1;
    rep(i,0,n) g[s[i]-'a'][i]=1;
    rep(i,0,m){
        if(t[i]=='?') continue;
        //f[j]&g[t[j]-'a][j+i]
        f&=g[t[i]-'a']>>i;
    }
    printf("%d\n",f.count());
    rep(i,0,n-m+1){
        if(f[i]) printf("%d\n",i);
    }
    return 0;
}