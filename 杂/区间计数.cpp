template<class T>
class Count{
public:
    set<pair<T,T>> st;
    T cnt;
    Count() {
        cnt=0;
		st.clear();
    }
    
    void add(T l, T r) {
        if(l>r) return;
        auto it=st.lower_bound({l,0});
        if(it!=st.begin()&&(*prev(it)).second>=l){
            it--;
        }
        T ll=l,rr=r;
        while(it!=st.end()){
            if(it->first>r) break;
            cnt-=it->second-it->first+1;
            ll=min(it->first,ll);
            rr=max(r,it->second);
            st.erase(it++);
        }
        cnt+=rr-ll+1;
        st.insert({ll,rr});
    }

	bool find(T d){
		auto it=st.upper_bound({d,0});
		if(it==st.begin()) return false;
		it--;
		if(it->fi<=d&&it->se>=d) return true;
		else return false;
	}
	
    T count() {
        return cnt;
    }
};


template<class T>
class Count {
    T ans = 0;
    set<pair<T,T>> st;
public:
    Count() {
    }
    
    void add(T left, T right) {
        T L = left, R = right;
        // 这里 (R1, L1) >= (R2, L2)，若 R1 > R2 或 R1 = R2 且 L1 >= L2
        auto it = st.lower_bound(pii(left - 1, -2e9));
        while (it != st.end()) {
            if (it->second > right + 1) break;
            L = min(L, it->second);
            R = max(R, it->first);
            ans -= it->first - it->second + 1;
            st.erase(it++);
        }
        ans += R - L + 1;
        st.insert(pii(R, L));
    }
    
    T count() {
        return ans;
    }
};