typedef double db;
const db EPS = 1e-9;
  
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }
  
inline int cmp(db a, db b){ return sign(a-b); }
  
struct P {
    db x, y ,z;
    P() {}
    P(db _x, db _y,db _z) : x(_x), y(_y), z(_z) {}
    P operator+(P p) { return {x + p.x, y + p.y, z + p.z}; }
    P operator-(P p) { return {x - p.x, y - p.y, z - p.z}; }
    P operator*(db d) { return {x * d, y * d, z * d}; }
    P operator/(db d) { return {x / d, y / d, z / d}; }
    bool operator<(P p) const { 
        int c = cmp(x, p.x);
        if (c) return c == -1;
        else{
            c = cmp(y, p.y);
            if(c) return c == -1;
            else return cmp(z, p.z) == -1;
        }
    }
 
    bool operator==(P o) const{
        return cmp(x,o.x) == 0 && cmp(y,o.y) == 0 && cmp(z,o.z) == 0;
    }
 
    db dot(P p) { return x * p.x + y * p.y + p.z * z; }//点积
    db det(P p) { return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x).abs(); }//叉积
    P DET(P p) { return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }//叉积

    db distTo(P p) { return (*this-p).abs(); }//两点之间的距离
    void read() { cin>>x>>y>>z; }
    void write() {cout<<"("<<x<<","<<y<<","<<z<<")"<<endl;}
    db abs() { return sqrt(abs2());}
    db abs2() { return x * x + y * y + z * z; }
    P unit() { return *this/abs(); }//方向向量
    double rd(){ return (rand()%2) ? EPS : -EPS; }
    void shake(){ x += rd(), y += rd(), z += rd(); }
};
 
struct S{
    P a, b, c, d;
    int v[3];
    S() {}
    S(P a_, P b_, P c_) : a(a_), b(b_), c(c_) { 
        d = (b-a).DET(c-a); 
    }

    S(int a_, int b_ ,int c_, const vector<P> &p) {
        v[0] = a_, v[1] = b_, v[2] = c_; 
        a = p[a_], b = p[b_], c = p[c_];
        d = (b-a).DET(c-a); 
    }
    
    bool operator==(S o) const{
        P n1 = d, n2 = o.d;
        return cmp(atan2(n1.y, n1.x), atan2(n2.y, n2.x)) == 0 && cmp(atan2(n1.z, n1.x), atan2(n2.z, n2.x)) == 0;
    }
};

db dist(P v, P a, P b){ return (a-b).det(v-a)/(a-b).abs(); }//v to ab

db dist(P v, S p){ return (v-p.a).dot(p.d)/(p.d.abs()); }//v to abc

bool isabove(P v, S p){ return sign((v - p.a).dot(p.d)) == 1; }

db VThree(P a, P b, P c, P d){
    P n = (b-a).DET(c-d);
    return n.abs()/2*d.dot(n)/n.abs()/3;
}

db VThree(P a, S x){
    P b = x.a, c = x.b, d = x.c;
    P n = (b-a).DET(c-d);
    return n.abs()/2*d.dot(n)/n.abs()/3;
}

vector<S> ConvexHulls(vector<P> pts){
    int totp = SZ(pts);
    vector<S> facets(4*totp), res(4*totp), del(4*totp);
    vector<VI> vise(totp, VI(totp));
    int s[3];
    s[0] = 0, s[1] = 1, s[2] = 2;
    int totf = 0;
    facets[totf++] = S(s[0], s[1], s[2], pts);
    facets[totf++] = S(s[0], s[2], s[1], pts);
    for(int i = 0; i < totp; ++i){
        int totr = 0, totd = 0;
        for(int j = 0; j < totf; ++j){
            if(!isabove(pts[i], facets[j]))
                res[totr++] = facets[j];         
            else{
                del[totd++] =facets[j];
                for(int k =0; k < 3; ++k)
                    vise[facets[j].v[k]][facets[j].v[(k+1)%3]] =i+1;
            }
        }
        for(int j =0; j < totd; ++j){
            S f =del[j];
            for(int k =0; k < 3; ++k)
                if(vise[f.v[(k+1)%3]][f.v[k]] != i+1)
                    res[totr++] =S(f.v[k], f.v[(k+1)%3], i, pts);
        }
        totf =totr;
        for(int j =0; j < totr; ++j) facets[j] = res[j];
    }
    facets.resize(totf);
    return facets;
}

db Stot(vector<P> p){//表面积
    vector<S> tmp = ConvexHulls(p);
    db ans = 0;
    for(auto cur:tmp){
        ans += cur.d.abs()/2;
    }
    return ans;
}

db Vtot(vector<P> p){//体积
    vector<S> tmp = ConvexHulls(p);
    db ans = 0;
    for(auto cur:tmp){
        ans += -dist(P(0, 0, 0), cur)*cur.d.abs()/6/*V_棱锥 =h*s/3*/;    
    }
    return ans;
}

int sdotcnt(vector<P> p){//求凸包表面个数
    vector<S> tmp = ConvexHulls(p);
    int totf = SZ(tmp);
    int cnt = 0;
    for(int i = 0; i < totf; ++i){
    ++cnt;
    for(int j = i+1; j < totf; ++j)
        if(tmp[i] == tmp[j]){
            /*数组右侧有相同面就去掉贡献*/
            /*这样同样的一组面只有最右边的有贡献*/
            --cnt;
            break;
        }
    }
}

int pdotcnt(vector<P> p){//求凸包顶点个数
    set<P> st;
    vector<S> tmp = ConvexHulls(p);
    for(auto cur:tmp) st.insert(cur.a),st.insert(cur.b),st.insert(cur.c);
    return SZ(st);
}

P getG(vector<P> p){//求凸包重心
    vector<S> tmp = ConvexHulls(p);
    P G(0, 0, 0);
    db sumV =0;
    for(auto cur:tmp){
        P ng =(P(0, 0, 0) + cur.a + cur.b + cur.c) / 4;
        db nv = -dist(P(0, 0, 0), cur) * cur.d.abs() / 6;
        sumV +=nv;
        G =G+ng*nv;
    }
    return G/sumV;
}