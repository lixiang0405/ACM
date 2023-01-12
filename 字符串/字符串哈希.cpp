typedef unsigned long long ull;
struct str_hash {
    ull base = 131;
    ull p[N];
    char s[N];
    gp_hash_table<ull, ull>hs;
    int len;

    void init(string &str) {
        len = str.length();
        hs.clear();
        for (int i = 1; i <= len; i++)
            s[i] = str[i - 1];
        p[0] = 1;
        for (int i = 1; i <= len; i++){
            hs[i] = hs[i - 1] * base + s[i];
            p[i] = p[i - 1] * base;
        }
    }

    void add(string &str) {
        for (char &c : str) {
            int i = ++len;
            hs[i] = hs[i - 1] * base + c;
            p[i] = p[i - 1] * base;
        }
    }
    
    ull hash(ull l, ull r){
        return hs[r] - hs[l - 1] * p[r - l + 1];
    }

    ull pre(int i) {
        return hash(1, i);
    }

    ull suf(int x) {
        return hash(len - x + 1, len);
    }
}cur;