/**
 * link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/submission/183391060
 */

#include<bits/stdc++.h>
using namespace std;

#define int         long long
#define double      long double
#define pb          push_back
#define FAST        ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
 
const int MOD = 1e9+7;
const int INF = LLONG_MAX;
const int NINF = LLONG_MIN;

struct item {
    int m, c;
};

struct segtree {

    int size;
    vector<item> values;

    // code change starts here

    item NEUTRAL_ELEMENT = {INF, 1};

    item merge(item a, item b) {
        if(a.m < b.m) return a;
        if(b.m < a.m) return b;
        return {a.m, a.c + b.c};
    }

    item single(int v) {
        return {v, 1};
    }

    // code change ends here

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        values.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
       if(rx - lx == 1) {
          if(lx < (int)a.size()) {
             values[x] = single(a[lx]);
          }
         return;
       }
       int m = (lx + rx) / 2;
       build(a, 2 * x + 1, lx, m);
       build(a, 2 * x + 2, m, rx);

       values[x] = merge(values[2 * x + 1],values[2 * x + 2]);
    }

    void build(vector<int>& a) {
       build(a, 0, 0, size); 
    }

    void set(int i, int v, int x, int lx, int rx) {
       if(rx - lx == 1) {
          values[x] = single(v);
          return;
       }
       int m = (lx + rx) / 2;
       if(i < m) set(i, v, 2 * x + 1, lx, m);
       else set(i, v, 2 * x + 2, m, rx);
       
       values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx) {
        if(lx >= r || rx <= l) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];
        int m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    item calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int32_t main() {
    FAST

    int n, m; cin >> n >> m;
    vector<int> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
    }

    segtree st;
    st.init(n);
    st.build(v);

    while(m--) {
        int op; cin >> op;
        if(op == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else if(op == 2) {
            int l, r;
            cin >> l >> r;
            item res = st.calc(l, r);
            cout << res.m << " " << res.c << "\n";
        }
    }

    return 0;
}
